#include "autoupdaterform.h"
#include <QtGui/QApplication>
#include <QtGui/QPlastiqueStyle>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	a.setStyle(new QPlastiqueStyle);
	AutoUpdaterForm w;
	w.show();
	return a.exec();
}
