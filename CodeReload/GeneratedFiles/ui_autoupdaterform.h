/********************************************************************************
** Form generated from reading UI file 'autoupdaterform.ui'
**
** Created: Sat Dec 10 09:12:59 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUTOUPDATERFORM_H
#define UI_AUTOUPDATERFORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QTableWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AutoUpdaterForm
{
public:
    QAction *actionPattern_File;
    QAction *actionSelected_Addresses_h;
    QAction *actionSelected_Addresses_vb;
    QAction *actionSelected_Addresses_cs;
    QWidget *centralWidget;
    QTableWidget *addressTable;
    QPushButton *importPatterns;
    QPushButton *processScan;
    QPushButton *processSelect;
    QPushButton *processRefresh;
    QListWidget *processList;
    QProgressBar *scanProgress;
    QLabel *processLabel;
    QLabel *patternsLabel;
    QLabel *processIconLabel;

    void setupUi(QMainWindow *AutoUpdaterForm)
    {
        if (AutoUpdaterForm->objectName().isEmpty())
            AutoUpdaterForm->setObjectName(QString::fromUtf8("AutoUpdaterForm"));
        AutoUpdaterForm->resize(241, 241);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(AutoUpdaterForm->sizePolicy().hasHeightForWidth());
        AutoUpdaterForm->setSizePolicy(sizePolicy);
        AutoUpdaterForm->setMinimumSize(QSize(241, 241));
        AutoUpdaterForm->setMaximumSize(QSize(241, 241));
        AutoUpdaterForm->setStyleSheet(QString::fromUtf8("QProgressBar {\n"
"	border: 1px solid black;\n"
"	text-align: top;\n"
"	padding: 1px;\n"
"	border-bottom-right-radius: 7px;\n"
"	border-bottom-left-radius: 7px;\n"
"	border-top-left-radius: 7px;\n"
"	border-top-right-radius: 7px;\n"
"	background: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1,\n"
"		stop: 0 #fff,\n"
"		stop: 0.4999 #eee,\n"
"		stop: 0.5 #ddd,\n"
"		stop: 1 #eee );\n"
"	width: 15px;\n"
"}\n"
"QProgressBar::chunk {\n"
"	background: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1,\n"
"	stop: 0 #78d,\n"
"	stop: 0.4999 #46a,\n"
"	stop: 0.5 #45a,\n"
"	stop: 1 #238 );\n"
"	border-bottom-right-radius: 7px;\n"
"	border-bottom-left-radius: 7px;\n"
"	border-top-left-radius: 7px;\n"
"	border-top-right-radius: 7px;\n"
"	border: 1px solid black;\n"
"}"));
        actionPattern_File = new QAction(AutoUpdaterForm);
        actionPattern_File->setObjectName(QString::fromUtf8("actionPattern_File"));
        actionPattern_File->setIconVisibleInMenu(true);
        actionSelected_Addresses_h = new QAction(AutoUpdaterForm);
        actionSelected_Addresses_h->setObjectName(QString::fromUtf8("actionSelected_Addresses_h"));
        actionSelected_Addresses_h->setIconVisibleInMenu(true);
        actionSelected_Addresses_vb = new QAction(AutoUpdaterForm);
        actionSelected_Addresses_vb->setObjectName(QString::fromUtf8("actionSelected_Addresses_vb"));
        actionSelected_Addresses_vb->setIconVisibleInMenu(true);
        actionSelected_Addresses_cs = new QAction(AutoUpdaterForm);
        actionSelected_Addresses_cs->setObjectName(QString::fromUtf8("actionSelected_Addresses_cs"));
        actionSelected_Addresses_cs->setIconVisibleInMenu(true);
        centralWidget = new QWidget(AutoUpdaterForm);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        addressTable = new QTableWidget(centralWidget);
        if (addressTable->columnCount() < 2)
            addressTable->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        addressTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        addressTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        addressTable->setObjectName(QString::fromUtf8("addressTable"));
        addressTable->setGeometry(QRect(330, 51, 221, 151));
        addressTable->setColumnCount(2);
        addressTable->horizontalHeader()->setDefaultSectionSize(120);
        addressTable->horizontalHeader()->setHighlightSections(true);
        addressTable->horizontalHeader()->setStretchLastSection(true);
        addressTable->verticalHeader()->setVisible(false);
        addressTable->verticalHeader()->setCascadingSectionResizes(false);
        addressTable->verticalHeader()->setDefaultSectionSize(20);
        addressTable->verticalHeader()->setProperty("showSortIndicator", QVariant(false));
        addressTable->verticalHeader()->setStretchLastSection(false);
        importPatterns = new QPushButton(centralWidget);
        importPatterns->setObjectName(QString::fromUtf8("importPatterns"));
        importPatterns->setGeometry(QRect(330, 210, 121, 23));
        processScan = new QPushButton(centralWidget);
        processScan->setObjectName(QString::fromUtf8("processScan"));
        processScan->setEnabled(false);
        processScan->setGeometry(QRect(460, 210, 91, 23));
        processSelect = new QPushButton(centralWidget);
        processSelect->setObjectName(QString::fromUtf8("processSelect"));
        processSelect->setGeometry(QRect(10, 210, 121, 23));
        processRefresh = new QPushButton(centralWidget);
        processRefresh->setObjectName(QString::fromUtf8("processRefresh"));
        processRefresh->setGeometry(QRect(140, 210, 91, 23));
        processList = new QListWidget(centralWidget);
        processList->setObjectName(QString::fromUtf8("processList"));
        processList->setGeometry(QRect(10, 10, 221, 192));
        processList->setIconSize(QSize(16, 16));
        scanProgress = new QProgressBar(centralWidget);
        scanProgress->setObjectName(QString::fromUtf8("scanProgress"));
        scanProgress->setGeometry(QRect(10, 210, 221, 23));
        scanProgress->setValue(70);
        scanProgress->setTextVisible(false);
        processLabel = new QLabel(centralWidget);
        processLabel->setObjectName(QString::fromUtf8("processLabel"));
        processLabel->setGeometry(QRect(370, 10, 181, 20));
        patternsLabel = new QLabel(centralWidget);
        patternsLabel->setObjectName(QString::fromUtf8("patternsLabel"));
        patternsLabel->setGeometry(QRect(370, 30, 181, 20));
        processIconLabel = new QLabel(centralWidget);
        processIconLabel->setObjectName(QString::fromUtf8("processIconLabel"));
        processIconLabel->setGeometry(QRect(330, 10, 32, 40));
        AutoUpdaterForm->setCentralWidget(centralWidget);

        retranslateUi(AutoUpdaterForm);

        QMetaObject::connectSlotsByName(AutoUpdaterForm);
    } // setupUi

    void retranslateUi(QMainWindow *AutoUpdaterForm)
    {
        AutoUpdaterForm->setWindowTitle(QApplication::translate("AutoUpdaterForm", "CodeReload", 0, QApplication::UnicodeUTF8));
        actionPattern_File->setText(QApplication::translate("AutoUpdaterForm", "Pattern File", 0, QApplication::UnicodeUTF8));
        actionSelected_Addresses_h->setText(QApplication::translate("AutoUpdaterForm", "Addresses (.h)", 0, QApplication::UnicodeUTF8));
        actionSelected_Addresses_vb->setText(QApplication::translate("AutoUpdaterForm", "Addresses (.vb)", 0, QApplication::UnicodeUTF8));
        actionSelected_Addresses_cs->setText(QApplication::translate("AutoUpdaterForm", "Addresses (.cs)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = addressTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("AutoUpdaterForm", "Title", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = addressTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("AutoUpdaterForm", "Address", 0, QApplication::UnicodeUTF8));
        importPatterns->setText(QApplication::translate("AutoUpdaterForm", "Import Patterns File", 0, QApplication::UnicodeUTF8));
        processScan->setText(QApplication::translate("AutoUpdaterForm", "Scan", 0, QApplication::UnicodeUTF8));
        processSelect->setText(QApplication::translate("AutoUpdaterForm", "Select Process", 0, QApplication::UnicodeUTF8));
        processRefresh->setText(QApplication::translate("AutoUpdaterForm", "Refresh", 0, QApplication::UnicodeUTF8));
        processLabel->setText(QString());
        patternsLabel->setText(QApplication::translate("AutoUpdaterForm", "0 patterns loaded", 0, QApplication::UnicodeUTF8));
        processIconLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class AutoUpdaterForm: public Ui_AutoUpdaterForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTOUPDATERFORM_H
