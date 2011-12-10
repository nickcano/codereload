#include "autoupdaterform.h"

AutoUpdaterForm::AutoUpdaterForm(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	ui.importPatterns->move(ui.processSelect->pos());
	ui.importPatterns->setVisible(false);

	ui.processScan->move(ui.processRefresh->pos());
	ui.processScan->setVisible(false);

	ui.addressTable->move(ui.processList->x(), ui.addressTable->y());
	ui.addressTable->setVisible(false);

	ui.processIconLabel->move(ui.processList->x(), ui.processLabel->y());
	ui.processIconLabel->setVisible(false);

	ui.processLabel->move(ui.processList->x() + 45, ui.processLabel->y());
	ui.processLabel->setVisible(false);

	ui.patternsLabel->move(ui.processList->x() + 45, ui.patternsLabel->y());
	ui.patternsLabel->setVisible(false);

	ui.scanProgress->setVisible(false);

	QObject::connect(ui.processRefresh, SIGNAL(clicked()), this, SLOT(onRefreshClick()));
	QObject::connect(ui.processSelect, SIGNAL(clicked()), this, SLOT(onSelectClick()));
	QObject::connect(ui.importPatterns, SIGNAL(clicked()), this, SLOT(onImportPatternsClick()));
	QObject::connect(ui.processScan, SIGNAL(clicked()), this, SLOT(onScanClick()));

	onRefreshClick();
}

AutoUpdaterForm::~AutoUpdaterForm()
{

}

void AutoUpdaterForm::closeEvent(QCloseEvent *event)
{
	AddressLocator::ClearPatterns();
	CloseHandle(scanProcessHandle);
	QApplication::quit();
}

void AutoUpdaterForm::onRefreshClick()
{
	ui.processList->clear();

	HANDLE hSnap;
	SHFILEINFO processFileInfo;
	PROCESSENTRY32 processInfo;
	processInfo.dwSize = sizeof(PROCESSENTRY32);

	try
	{
		hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		if (!hSnap)
			throw std::exception("Could not create process snapshot");

		if (!Process32First(hSnap, &processInfo))
			throw std::exception("Enumerating processes failed");

		do
		{
			HANDLE processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processInfo.th32ProcessID);
			if (processHandle)
			{
				QListWidgetItem* item = new QListWidgetItem(QString::fromWCharArray(processInfo.szExeFile), ui.processList);

				TCHAR filename[MAX_PATH];
				if (GetModuleFileNameEx(processHandle, NULL, filename, sizeof(filename)))
				{
					SHGetFileInfo(filename, -1, &processFileInfo, sizeof(processFileInfo), SHGFI_ICON);
					if (processFileInfo.hIcon)
					{
						item->setIcon(QPixmap::fromWinHICON(processFileInfo.hIcon));
						DestroyIcon(processFileInfo.hIcon);
					}
				}

				if (item->icon().isNull())
				{
					HICON icon = LoadIcon(NULL, IDI_APPLICATION);
					item->setIcon(QPixmap::fromWinHICON(icon));
					DestroyIcon(icon);
				}
				
				item->setData(1234, QVariant((int)processInfo.th32ProcessID));

				CloseHandle(processHandle);
			}
		}
		while (Process32Next(hSnap, &processInfo));

		CloseHandle(hSnap);
	}
	catch (std::exception e)
	{
		if (hSnap)
			CloseHandle(hSnap);
		throw;
	}
}

void AutoUpdaterForm::onSelectClick()
{
	if (ui.processList->currentItem())
	{
		scanProcessID = (DWORD)ui.processList->currentItem()->data(1234).toInt();
		scanProcessHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, scanProcessID);

		if (scanProcessHandle)
		{
			ui.processSelect->setVisible(false);
			ui.importPatterns->setVisible(true);

			ui.processRefresh->setVisible(false);
			ui.processScan->setVisible(true);

			ui.processList->setVisible(false);
			ui.addressTable->setVisible(true);

			
			ui.processIconLabel->setPixmap(ui.processList->currentItem()->icon().pixmap(32, 32));
			ui.processIconLabel->setVisible(true);

			ui.processLabel->setText(ui.processList->currentItem()->text());
			ui.processLabel->setVisible(true);

			ui.patternsLabel->setVisible(true);
		}
		else
		{
			//failed
		}
	}
}

void AutoUpdaterForm::onImportPatternsClick()
{
	QString filename = QFileDialog::getOpenFileName(this, tr("Import Address Pattern"), QDir::currentPath(),
		tr("Address Pattern XML File (*.apxml)"),
		0, QFileDialog::DontUseNativeDialog);

	if (!filename.isNull())
	{
		QFile xmlFile(filename);
		QDomDocument doc(filename);
		doc.setContent(&xmlFile);

		QDomElement addressElement = doc.documentElement();
		addressElement = addressElement.firstChild().toElement();

		while (!addressElement.isNull())
		{
			QDomNode node = addressElement.firstChild();

			QString title, pattern;
			BYTE type;
			while (!node.isNull())
			{
				if (node.nodeName() == "title")
				{
					title = node.attributes().namedItem("value").nodeValue();
				}
				else if (node.nodeName() == "type")
				{
					if (node.attributes().namedItem("value").nodeValue() == "data")
						type = 0;
					else
						type = 1;
				}
				else if (node.nodeName() == "pattern")
				{
					pattern = node.attributes().namedItem("value").nodeValue();
				}
				node = node.nextSibling();
			}

			AddressLocator::CreatePattern(	(char*)title.toStdString().c_str(),
											(char*)pattern.toStdString().c_str(),
											type);

			addressElement = addressElement.nextSiblingElement();
		}

		if (AddressLocator::GetPatternCount() > 0)
		{
			QString text = " patterns loaded";
			text.prepend(QString::number(AddressLocator::GetPatternCount()));
			ui.patternsLabel->setText(text);

			ui.processScan->setEnabled(true);
			ui.importPatterns->setEnabled(false);
		}
		else
		{
			ui.patternsLabel->setText(QString("Failed to load .apxml file! No patterns present!"));
		}
	}
}

void AutoUpdaterForm::onScanClick()
{
	ui.processScan->setVisible(false);
	ui.importPatterns->setVisible(false);
	ui.scanProgress->setVisible(true);
	ui.addressTable->clear();
	ui.addressTable->setRowCount(0);
	ui.addressTable->setHorizontalHeaderItem(0, new QTableWidgetItem(QString("Title")));
	ui.addressTable->setHorizontalHeaderItem(1, new QTableWidgetItem(QString("Address")));

	AddressLocator::LocateAddresses(scanProcessHandle, (DWORD)&ScanProgressCallback, (DWORD)&AddressFoundCallback, (DWORD)this);
}

void AutoUpdaterForm::AddressFoundCallback(char* name, DWORD address, DWORD param)
{
	AutoUpdaterForm* form = (AutoUpdaterForm*)param;

	int row = form->ui.addressTable->rowCount();
	form->ui.addressTable->insertRow(row);
	form->ui.addressTable->setItem(row, 0, new QTableWidgetItem(QString(name)));

	char addressText[32];
	sprintf(addressText, "0x%x", address);

	form->ui.addressTable->setItem(row, 1, new QTableWidgetItem(QString(addressText)));
	return;
}

void AutoUpdaterForm::ScanProgressCallback(DWORD readBytes, DWORD totalBytes, DWORD param)
{
	AutoUpdaterForm* form = (AutoUpdaterForm*)param;
	if (totalBytes > 0)
	{
		form->ui.scanProgress->setMaximum(totalBytes);
		form->ui.scanProgress->setValue(readBytes);
	}
	else
	{
		form->ui.processScan->setVisible(true);
		form->ui.importPatterns->setVisible(true);
		form->ui.scanProgress->setVisible(false);
	}

	QApplication::processEvents();
	//form->repaint();
}
