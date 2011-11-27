#include "stdafx.h"
#include "asfviewer.h"

AsfViewer::AsfViewer(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	// build ui and controls
	createActions();
	createMenus();
	createCentralWidget();
	createStatusBar();

	isFileOpen = false; // flag is using for enabling/disabling buttons
	timer = new QTimer(this); // change frames automatically
	connect(timer, SIGNAL(timeout()), this, SLOT(goToNextFrame()));

	setWindowTitle(tr("Asf Viewer"));
	resize(400, 400);

	statusBar()->showMessage( tr("Open file"), 5000 );
}

void AsfViewer::open()
{
	QString filterAsf = "Asf file (*.asf)";
	QString filterGzip = "GZip file (*.gz)";

	QString fileName = QFileDialog::getOpenFileName(this,
		tr("Open File"), QDir::currentPath(), filterAsf + ";;" + filterGzip);

	if (!fileName.isEmpty()) {
		// file selected
		timer->stop();

		if (isFileOpen) {
			// delete previous file
			asfFile->clear();
			delete asfFile;
		}

		try {
			asfFile = new AsfFile(fileName); // open file
		}
		catch (std::exception& e) {
			QMessageBox::information(this, tr("Asf Viewer"),
				tr("Cannot open file: \n%1\n\n Error message:\n %2").arg(fileName).arg(e.what()));
			return;
		}
		catch (...) {
			QMessageBox::information(this, tr("Asf Viewer"),
				tr("Cannot open file: \n%1\n\n Unknown error").arg(fileName));
			return;
		}

		isFileOpen = true;

		goToFirstFrame();
		updateAllUi();

		fitToWindowAct->trigger(); // force image to fit window
		scaleFactor = 1.0; // reset Zoom to 100%
		statusBar()->showMessage(tr("Opened '%1'").arg(fileName), 2000);
	}
}

void AsfViewer::saveFile()
{
	QString fileName = QFileDialog::getSaveFileName(
		this,
		tr("Select output file name and type"), QDir::currentPath(), "*.asf ;; *.gz");

	if (!fileName.isEmpty() && isFileOpen) {
		// file selected
		timer->stop();

		try {
			asfFile->saveToFile(fileName); // save file
		}
		catch (std::exception& e) {
			QMessageBox::information(this, tr("Asf Viewer"),
				tr("Cannot save file: \n%1\n\n Error message:\n %2").arg(fileName).arg(e.what()));
			return;
		}
		catch (...) {
			QMessageBox::information(this, tr("Asf Viewer"),
				tr("Cannot save file: \n%1\n\n Unknown error").arg(fileName));
			return;
		}

		statusBar()->showMessage(tr("Saved '%1'").arg(fileName), 2000);
	}
}

void AsfViewer::closeFile()
{
	timer->stop(); // in case autoplay is active

	asfFile->clear(); // delete opened file
	delete asfFile;
	isFileOpen = false;

	updateAllUi();
	statusBar()->showMessage( tr("File closed"), 5000 );
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

void AsfViewer::about()
{
	QMessageBox::about(this, tr("About Asf Viewer"),
		tr("<p>The <b>Asf Viewer</b> read .asf files, that are simple "
		"containers for a gray scaled frames (kind of video file). </p><p>"
		"Made by Sergii Pechenizkyi for Codeminders test task.</p>"));
}

void AsfViewer::autoPlayFrames()
{
	timer->start(50); // close to 24 frames per second
}

void AsfViewer::createActions()
{
	openAct = new QAction(tr("&Open..."), this);
	openAct->setShortcut(tr("Ctrl+O"));
	connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

	saveAct = new QAction(tr("&Save as..."), this);
	saveAct->setShortcut(tr("Ctrl+S"));
	saveAct->setEnabled(false);
	connect(saveAct, SIGNAL(triggered()), this, SLOT(saveFile()));

	closeAct = new QAction(tr("&Close..."), this);
	closeAct->setEnabled(false);
	connect(closeAct, SIGNAL(triggered()), this, SLOT(closeFile()));

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
	fileMenu->addAction(saveAct);
	fileMenu->addAction(closeAct);
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

void AsfViewer::createCentralWidget()
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
}

void AsfViewer::createStatusBar()
{
	QStatusBar *statusBar = this->statusBar();

	lblFrameCount = new QLabel( tr("  FRAMES TOTAL  ") );
	lblFrameCount->setMinimumSize( lblFrameCount->sizeHint() );
	lblFrameCount->setAlignment( Qt::AlignCenter );
	lblFrameCount->setText( tr("COUNT %1").arg(0) );
	lblFrameCount->setToolTip( tr("Count of frames in one file.") );
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
}

void AsfViewer::goToFirstFrame()
{
	currentFrame = asfFile->begin();
	updateCurrentFrame();
	currentFrameNumber = 1;
	updateButtonsRow();
}

void AsfViewer::goToPrevFrame()
{
	--currentFrame;
	updateCurrentFrame();
	--currentFrameNumber;
	updateButtonsRow();
}

void AsfViewer::goToNextFrame()
{
	++currentFrame;
	updateCurrentFrame();
	++currentFrameNumber;
	updateButtonsRow();
}

void AsfViewer::goToLastFrame()
{
	currentFrame = asfFile->end() - 1;
	updateCurrentFrame();
	currentFrameNumber = asfFile->size();
	updateButtonsRow();
}

void AsfViewer::goToFrame(const int frameNumber)
{
	if (frameNumber > 0 && frameNumber < asfFile->size() + 1)
	{
		if (frameNumber == 1)
			goToFirstFrame();
		else if (frameNumber == asfFile->size())
			goToLastFrame();
		else
		{
			currentFrame = asfFile->begin() + frameNumber - 1;
			updateCurrentFrame();
			currentFrameNumber = frameNumber;
			updateButtonsRow();
		}
	}
	else
		statusBar()->showMessage(tr("Out of range [1,%1]").arg(asfFile->size()), 5000);

}

void AsfViewer::numberEditChanged()
{
	QString inputStr = frameNumEdt->text();
	int frameNum = inputStr.toInt();
	goToFrame(frameNum);
}

void AsfViewer::updateActions()
{
	if (isFileOpen)
	{
		fitToWindowAct->setEnabled(true);
		zoomInAct->setEnabled(!fitToWindowAct->isChecked());
		zoomOutAct->setEnabled(!fitToWindowAct->isChecked());
		normalSizeAct->setEnabled(!fitToWindowAct->isChecked());
		autoPlayAct->setEnabled(true);
		closeAct->setEnabled(true);
		saveAct->setEnabled(true);
	}
	else
	{
		zoomInAct->setEnabled(false);
		zoomOutAct->setEnabled(false);
		normalSizeAct->setEnabled(false);
		fitToWindowAct->setEnabled(false);
		fitToWindowAct->setChecked(false);
		autoPlayAct->setEnabled(false);
		closeAct->setEnabled(false);
		saveAct->setEnabled(false);
	}
}

void AsfViewer::updateAllUi()
{
	updateActions();
	if (isFileOpen)
	{
		lblFrameCount->setText( tr("COUNT %1").arg(asfFile->count()) );
		lblRows->setText( tr("ROWS %1").arg(asfFile->rows()) );
		lblCols->setText( tr("COLS %1").arg(asfFile->cols()) );
		frameNumEdt->setEnabled(true);
	}
	else{
		lblFrameCount->setText( tr("COUNT %1").arg(0) );
		lblRows->setText( tr("ROWS %1").arg(0) );
		lblCols->setText( tr("COLS %1").arg(0) );
		
		imageLabel->clear();

		firstFrameBtn->setEnabled(false);
		prevFrameBtn->setEnabled(false);
		nextFrameBtn->setEnabled(false);
		lastFrameBtn->setEnabled(false);
		frameNumEdt->clear();
		frameNumEdt->setEnabled(false);
	}
}

void AsfViewer::updateButtonsRow()
{
	if (currentFrameNumber == 1) {
		firstFrameBtn->setEnabled(false);
		prevFrameBtn->setEnabled(false);
		lastFrameBtn->setEnabled(true);
		nextFrameBtn->setEnabled(true);
	}
	else if (currentFrameNumber == asfFile->size()){
		firstFrameBtn->setEnabled(true);
		prevFrameBtn->setEnabled(true);
		lastFrameBtn->setEnabled(false);
		nextFrameBtn->setEnabled(false);
		timer->stop();
	}
	else
	{
		firstFrameBtn->setEnabled(true);
		prevFrameBtn->setEnabled(true);
		lastFrameBtn->setEnabled(true);
		nextFrameBtn->setEnabled(true);
	}

	frameNumEdt->setText(QString::number(currentFrameNumber));

}

void AsfViewer::updateCurrentFrame()
{
	imageLabel->setPixmap(QPixmap::fromImage(**currentFrame));
}

AsfViewer::~AsfViewer()
{

}
