#include "stdafx.h"
#include "AsfViewer.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	AsfViewer w;
	w.show();
	return a.exec();
}
