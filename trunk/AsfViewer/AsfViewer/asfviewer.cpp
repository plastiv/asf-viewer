#include "asfviewer.h"
#include "AsfLibrary/AsfFile.h"
#include "AsfLibrary/AsfFileUtilities.h"
#include "AsfLibraryWrapper.h"

//uchar imagio [20][20];
//for (int i = 0; i < 20; i++)
//	for (int j = 0; j < 20; j++)
//		imagio[i][j] = qrand() % 256;
//QVector<QRgb> colorTable;
//for (int i = 0; i < 256; i++)
//	colorTable.push_back(QColor(i, i, i).rgb());
//QImage image((uchar*)imagio, 20, 20, 20, QImage::Format_Indexed8); // was incorrect
//image.setColorTable(colorTable);
//
//
//QImage myImage("123.jpg");
//
//ui.setupUi(this);
//ui.label->setScaledContents(true);
//ui.label->setPixmap(QPixmap::fromImage(image));
//ui.label->resize(500,500);

AsfViewer::AsfViewer(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	imageLabel = new QLabel;
	imageLabel->setBackgroundRole(QPalette::Base);
	imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	imageLabel->setScaledContents(true);

	scrollArea = new QScrollArea;
	scrollArea->setBackgroundRole(QPalette::Dark);
	scrollArea->setWidget(imageLabel);

	firstFrameBtn = new QPushButton(tr("First"));
	firstFrameBtn->setEnabled(false);
	connect(firstFrameBtn, SIGNAL(clicked()), this, SLOT(goToFirstFrame()));
	prevFrameBtn = new QPushButton(tr("Prev"));
	prevFrameBtn->setEnabled(false);
	connect(prevFrameBtn, SIGNAL(clicked()), this, SLOT(goToPrevFrame()));
	nextFrameBtn = new QPushButton(tr("Next"));
	nextFrameBtn->setEnabled(false);
	connect(nextFrameBtn, SIGNAL(clicked()), this, SLOT(goToNextFrame()));
	lastFrameBtn = new QPushButton(tr("Last"));
	lastFrameBtn->setEnabled(false);
	connect(lastFrameBtn, SIGNAL(clicked()), this, SLOT(goToLastFrame()));

	QVBoxLayout * mainLayout = new QVBoxLayout();
	mainLayout->addWidget(scrollArea);

	frameNumEdt = new QLineEdit;
	frameNumEdt->setEnabled(false);
	frameNumEdt->setAlignment(Qt::AlignHCenter);
	connect(frameNumEdt, SIGNAL(editingFinished()), this, SLOT(numberEditChanged()));

	QHBoxLayout * buttonLayout = new QHBoxLayout();
	buttonLayout->addWidget(firstFrameBtn);
	buttonLayout->addWidget(prevFrameBtn);
	buttonLayout->addWidget(frameNumEdt);
	buttonLayout->addWidget(nextFrameBtn);
	buttonLayout->addWidget(lastFrameBtn);
	mainLayout->addLayout(buttonLayout);

	QWidget * centWidget = new QWidget;
	centWidget->setLayout(mainLayout);

	setCentralWidget(centWidget);

	createActions();
	createMenus();

	//statusBar()->showMessage("Open file", 10000);
	setWindowTitle(tr("Asf Viewer"));
	resize(500, 400);

	// FIXME: trash temp code to end
	///////////////////////////////////////////////
	QStatusBar *statusBar = this->statusBar();

	lblFrameCount = new QLabel( tr("  FRAMES TOTAL  ") );
	lblFrameCount->setMinimumSize( lblFrameCount->sizeHint() );
	lblFrameCount->setAlignment( Qt::AlignCenter );
	lblFrameCount->setText( tr("COUNT %1").arg(0) );
	lblFrameCount->setToolTip( tr("Count of pixel columns in one frame.") );
	statusBar->addPermanentWidget( lblFrameCount );

	lblRows = new QLabel( tr("  ROWS COUNT ") );
	lblRows->setMinimumSize( lblRows->sizeHint() );
	lblRows->setAlignment( Qt::AlignCenter );
	lblRows->setText( tr("ROWS %1").arg(0) );
	lblRows->setToolTip( tr("Count of pixel rows in one frame.") );
	statusBar->addPermanentWidget( lblRows );

	lblCols = new QLabel( tr("  FRAME COLS  ") );
	lblCols->setMinimumSize( lblCols->sizeHint() );
	lblCols->setAlignment( Qt::AlignCenter );
	lblCols->setText( tr("COLS %1").arg(0) );
	lblCols->setToolTip( tr("Count of pixel columns in one frame.") );
	statusBar->addPermanentWidget( lblCols );

	statusBar->showMessage( tr("Open file"), 5000 );

	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(goToNextFrame()));

}

void AsfViewer::open()
{
	QString fileName = QFileDialog::getOpenFileName(this,
		tr("Open File"), QDir::currentPath(),"*.asf *.gz");
	if (!fileName.isEmpty()) {
		if (!asfFile.empty())
		{
			asfFile.clear();
		}
		AsfProperty myProperty;
		if (fileName.contains(".gz"))
			asfFile = *getFramesFromGZipFile(fileName, myProperty);
		else
			asfFile = *getFramesFromFile(fileName, myProperty);

		lblFrameCount->setText( tr("COUNT %1").arg(myProperty.count) );
		lblRows->setText( tr("ROWS %1").arg(myProperty.rows) );
		lblCols->setText( tr("COLS %1").arg(myProperty.cols) );
		statusBar()->showMessage(tr("Opened '%1'").arg(fileName), 2000);
		/*if (image.isNull()) {
			QMessageBox::information(this, tr("Asf Viewer"),
				tr("Cannot load %1.").arg(fileName));
			return;
		}*/

		goToFirstFrame();
		scaleFactor = 1.0;

		frameNumEdt->setEnabled(true);
		fitToWindowAct->setEnabled(true);
		autoPlayAct->setEnabled(true);
		fitToWindowAct->trigger();
		updateActions();
		
		if (!fitToWindowAct->isChecked())
			imageLabel->adjustSize();

	}
}

void AsfViewer::zoomIn()
{
	scaleImage(1.25);
}

void AsfViewer::zoomOut()
{
	scaleImage(0.8);
}

void AsfViewer::normalSize()
{
	imageLabel->adjustSize();
	scaleFactor = 1.0;
}

void AsfViewer::fitToWindow()
{
	bool fitToWindow = fitToWindowAct->isChecked();
	scrollArea->setWidgetResizable(fitToWindow);
	if (!fitToWindow) {
		normalSize();
	}
	updateActions();
}

void AsfViewer::about()
{
	QMessageBox::about(this, tr("About Asf Viewer"),
		tr("<p>The <b>Asf Viewer</b> read .asf files, that are simple "
		"containers for a gray scaled frames (kind of video file). </p><p>"
		"Made by Sergii Pechenizkyi for Codeminders test task.</p>"));
}

void AsfViewer::createActions()
{
	openAct = new QAction(tr("&Open..."), this);
	openAct->setShortcut(tr("Ctrl+O"));
	connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

	exitAct = new QAction(tr("E&xit"), this);
	exitAct->setShortcut(tr("Ctrl+Q"));
	connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

	zoomInAct = new QAction(tr("Zoom &In (25%)"), this);
	zoomInAct->setShortcut(tr("Ctrl++"));
	zoomInAct->setEnabled(false);
	connect(zoomInAct, SIGNAL(triggered()), this, SLOT(zoomIn()));

	zoomOutAct = new QAction(tr("Zoom &Out (25%)"), this);
	zoomOutAct->setShortcut(tr("Ctrl+-"));
	zoomOutAct->setEnabled(false);
	connect(zoomOutAct, SIGNAL(triggered()), this, SLOT(zoomOut()));

	normalSizeAct = new QAction(tr("&Normal Size"), this);
	normalSizeAct->setShortcut(tr("Ctrl+0"));
	normalSizeAct->setEnabled(false);
	connect(normalSizeAct, SIGNAL(triggered()), this, SLOT(normalSize()));

	fitToWindowAct = new QAction(tr("&Fit to Window"), this);
	fitToWindowAct->setEnabled(false);
	fitToWindowAct->setCheckable(true);
	fitToWindowAct->setShortcut(tr("Ctrl+F"));
	connect(fitToWindowAct, SIGNAL(triggered()), this, SLOT(fitToWindow()));

	autoPlayAct = new QAction(tr("Auto &Play"), this);
	autoPlayAct->setShortcut(tr("Ctrl+P"));
	autoPlayAct->setEnabled(false);
	connect(autoPlayAct, SIGNAL(triggered()), this, SLOT(autoPlayFrames()));

	aboutAct = new QAction(tr("&About"), this);
	connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

}

void AsfViewer::createMenus()
{
	fileMenu = new QMenu(tr("&File"), this);
	fileMenu->addAction(openAct);
	fileMenu->addSeparator();
	fileMenu->addAction(exitAct);

	viewMenu = new QMenu(tr("&View"), this);
	viewMenu->addAction(zoomInAct);
	viewMenu->addAction(zoomOutAct);
	viewMenu->addAction(normalSizeAct);
	viewMenu->addSeparator();
	viewMenu->addAction(fitToWindowAct);
	viewMenu->addAction(autoPlayAct);

	helpMenu = new QMenu(tr("&Help"), this);
	helpMenu->addAction(aboutAct);

	menuBar()->addMenu(fileMenu);
	menuBar()->addMenu(viewMenu);
	menuBar()->addMenu(helpMenu);
}

void AsfViewer::updateActions()
{
	zoomInAct->setEnabled(!fitToWindowAct->isChecked());
	zoomOutAct->setEnabled(!fitToWindowAct->isChecked());
	normalSizeAct->setEnabled(!fitToWindowAct->isChecked());
}

void AsfViewer::scaleImage(double factor)
{
	Q_ASSERT(imageLabel->pixmap());
	scaleFactor *= factor;
	imageLabel->resize(scaleFactor * imageLabel->pixmap()->size());

	adjustScrollBar(scrollArea->horizontalScrollBar(), factor);
	adjustScrollBar(scrollArea->verticalScrollBar(), factor);

	zoomInAct->setEnabled(scaleFactor < 3.0);
	zoomOutAct->setEnabled(scaleFactor > 0.333);
}

void AsfViewer::adjustScrollBar(QScrollBar *scrollBar, double factor)
{
	scrollBar->setValue(int(factor * scrollBar->value()
		+ ((factor - 1) * scrollBar->pageStep()/2)));
}

AsfViewer::~AsfViewer()
{

}

void AsfViewer::goToFirstFrame()
{
	firstFrameBtn->setEnabled(false);
	prevFrameBtn->setEnabled(false);

	lastFrameBtn->setEnabled(true);
	nextFrameBtn->setEnabled(true);

	currentFrame = asfFile.begin();
	updateCurrentFrame();
	currentFrameNumber = 1;
	updateCurrentFrameNumber();
}

void AsfViewer::goToPrevFrame()
{
	if (!lastFrameBtn->isEnabled())
		lastFrameBtn->setEnabled(true);

	if (!nextFrameBtn->isEnabled())
		nextFrameBtn->setEnabled(true);

	--currentFrame;
	if(currentFrame == asfFile.begin()) {
		prevFrameBtn->setEnabled(false);
		firstFrameBtn->setEnabled(false);
	}

	updateCurrentFrame();
	--currentFrameNumber;
	updateCurrentFrameNumber();
}

void AsfViewer::goToNextFrame()
{
	if (!firstFrameBtn->isEnabled())
		firstFrameBtn->setEnabled(true);
	
	if (!prevFrameBtn->isEnabled())
		prevFrameBtn->setEnabled(true);

	++currentFrame;
	if(currentFrame+1 == asfFile.end()) {
		timer->stop();
		nextFrameBtn->setEnabled(false);
		lastFrameBtn->setEnabled(false);
	}

	updateCurrentFrame();
	++currentFrameNumber;
	updateCurrentFrameNumber();
}

void AsfViewer::goToLastFrame()
{
	firstFrameBtn->setEnabled(true);
	prevFrameBtn->setEnabled(true);

	lastFrameBtn->setEnabled(false);
	nextFrameBtn->setEnabled(false);

	currentFrame = asfFile.end() - 1;
	updateCurrentFrame();
	currentFrameNumber = asfFile.size();
	updateCurrentFrameNumber();
}

void AsfViewer::goToFrame(const int frameNumber)
{
	if (frameNumber > 0 && frameNumber < asfFile.size() + 1)
	{
		if (frameNumber == 1)
			goToFirstFrame();
		else if (frameNumber == asfFile.size())
			goToLastFrame();
		else
		{
			firstFrameBtn->setEnabled(true);
			prevFrameBtn->setEnabled(true);
			lastFrameBtn->setEnabled(true);
			nextFrameBtn->setEnabled(true);

			currentFrame = asfFile.begin() + frameNumber - 1;
			updateCurrentFrame();
			currentFrameNumber = frameNumber;
			updateCurrentFrameNumber();
		}
	}
	else
		statusBar()->showMessage(tr("Out of range [1,%1]").arg(asfFile.size()), 5000);

}

void AsfViewer::updateCurrentFrame()
{
	imageLabel->setPixmap(QPixmap::fromImage(**currentFrame));
}

void AsfViewer::updateCurrentFrameNumber()
{
	frameNumEdt->setText(QString::number(currentFrameNumber));
}

void AsfViewer::numberEditChanged()
{
	QString inputStr = frameNumEdt->text();
	int frameNum = inputStr.toInt();
	goToFrame(frameNum);
}

void AsfViewer::autoPlayFrames()
{
     timer->start(50); // close to 24 frames per second
}
