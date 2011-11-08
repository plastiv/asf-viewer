#ifndef ASFVIEWER_H
#define ASFVIEWER_H

#include <QtGui/QMainWindow>
#include "ui_asfviewer.h"

class AsfViewer : public QMainWindow
{
	Q_OBJECT

public:
	AsfViewer(QWidget *parent = 0, Qt::WFlags flags = 0);
	~AsfViewer();

private:
	Ui::AsfViewerClass ui;
};

#endif // ASFVIEWER_H
