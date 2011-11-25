#ifndef ASFVIEWER_H
#define ASFVIEWER_H

#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QPixmap>
#include <QtGui/QImage>
#include <QtGui/QWidget>
#include <QtGui/QFileDialog>
#include <QtGui/QMessageBox>
#include <QtGui/QScrollArea>
#include <QtGui/QScrollBar>
#include <QtGui/QLineEdit>
#include <QtGui/QProgressBar>
#include "ui_asfviewer.h"

#include <QMainWindow>
#include <QTimer>

class QAction;
class QLabel;
class QMenu;
class QScrollArea;
class QScrollBar;

class AsfViewer : public QMainWindow
{
	Q_OBJECT

public:
	AsfViewer(QWidget *parent = 0, Qt::WFlags flags = 0);
	~AsfViewer();

private slots:
	void open();
	void zoomIn();
	void zoomOut();
	void normalSize();
	void fitToWindow();
	void about();
	void numberEditChanged();
	void goToFirstFrame();
	void goToPrevFrame();
	void goToNextFrame();
	void goToLastFrame();
	void autoPlayFrames();
private:
	void createActions();
	void createMenus();
	void updateActions();
	void scaleImage(double factor);
	void adjustScrollBar(QScrollBar *scrollBar, double factor);
	void updateCurrentFrame();
	void updateCurrentFrameNumber();
	void goToFrame(const int frameNumber);


	QLabel *imageLabel;
	QScrollArea *scrollArea;
	QPushButton *nextFrameBtn;
	QPushButton *prevFrameBtn;
	QPushButton *firstFrameBtn;
	QPushButton *lastFrameBtn;
	QLineEdit *frameNumEdt;

	double scaleFactor;
	QVector<QImage*>::const_iterator currentFrame;
	int currentFrameNumber;
	QVector<QImage*> asfFile; // keep data in pool, all usage throw iterators
	QTimer *timer;
	QLabel *lblFrameCount;
	QLabel *lblRows;
	QLabel *lblCols;

	QAction *openAct;
	QAction *exitAct;
	QAction *zoomInAct;
	QAction *zoomOutAct;
	QAction *normalSizeAct;
	QAction *fitToWindowAct;
	QAction *autoPlayAct;
	QAction *aboutAct;

	QMenu *fileMenu;
	QMenu *viewMenu;
	QMenu *helpMenu;
};

#endif // ASFVIEWER_H
