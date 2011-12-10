#ifndef AUTOUPDATERFORM_H
#define AUTOUPDATERFORM_H

#include <windows.h>
#include <tlhelp32.h>
#include <psapi.h>

#include <QtGui/QMainWindow>
#include <QtGui/QFileDialog>
#include <QtXml>
#include "ui_autoupdaterform.h"

#include "AddressLocator.h"

class AutoUpdaterForm : public QMainWindow
{
	Q_OBJECT

public:
	AutoUpdaterForm(QWidget *parent = 0, Qt::WFlags flags = (Qt::WFlags)(Qt::WindowStaysOnTopHint | Qt::Tool));
	~AutoUpdaterForm();

protected:
	virtual void closeEvent(QCloseEvent *event);

public slots:
	void onRefreshClick();
	void onSelectClick();
	void onImportPatternsClick();
	void onScanClick();

private:
	DWORD scanProcessID;
	HANDLE scanProcessHandle;
	Ui::AutoUpdaterForm ui;

	static void AddressFoundCallback(char* name, DWORD address, DWORD param);
	static void ScanProgressCallback(DWORD readBytes, DWORD totalBytes, DWORD param);
};

#endif // AUTOUPDATERFORM_H
