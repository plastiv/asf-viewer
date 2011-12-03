#ifndef ASFVIEWER_H
#define ASFVIEWER_H

#include "AsfLibraryWrapper.h"
#include "ReadWriteThread.h"

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
#include <QtGui/QStatusBar>
#include <QtGui/QMenu>
#include <QtGui/QAction>
#include <QtGui/QMenuBar>

#include <QEvent>
#include <QTimer>

class AsfViewer : public QMainWindow
{
	Q_OBJECT

public:
	AsfViewer(QWidget *parent = 0, Qt::WFlags flags = 0);
	~AsfViewer() {}

private slots:
	void open();
	void closeFile();
	void saveFile();
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
	void createCentralWidget();
	void createStatusBar();
	void updateActions();
	void updateButtonsRow();
	void updateAllUi();
	void updateCurrentFrame();
	void scaleImage(double factor);
	void adjustScrollBar(QScrollBar *scrollBar, double factor);
	void goToFrame(const int frameNumber);
	void customEvent (QEvent *event);

	double scaleFactor;
	QVector<QImage*>::const_iterator currentFrame;
	int currentFrameNumber;
	QAsfFile* asfFile; // keep data in pool, all usage throw iterator
	bool isFileOpen;
	OpenFileThread openFileThread;

	QLabel *imageLabel;
	QScrollArea *scrollArea;
	QPushButton *nextFrameBtn;
	QPushButton *prevFrameBtn;
	QPushButton *firstFrameBtn;
	QPushButton *lastFrameBtn;
	QLineEdit *frameNumEdt;

	QTimer *timer;
	QLabel *lblFrameCount;
	QLabel *lblRows;
	QLabel *lblCols;

	QAction *openAct;
	QAction *saveAct;
	QAction *closeAct;
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
