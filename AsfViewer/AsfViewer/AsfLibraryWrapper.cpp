#include "stdafx.h"
#include "AsfLibraryWrapper.h"

void QAsfFile::getFramesFromAsfFile()
{
	// Build greyscale color table
	QVector<QRgb> grayscale;
	grayscale.reserve(255); // 255 colors
	for (int i = 0; i < 256; ++i) {
		grayscale.append(qRgb(i, i, i));
	}

	frames = *(new QVector<QImage*>());
	frames.reserve(count_);

	for (Asf::FramePtrIterator it = asfFile->begin();
		it != asfFile->end(); ++it) {
			// for each frame 
			// copy its pixels to QByteArray
			QByteArray data;
			data.resize(rows_*cols_);
			size_t index = 0;

			for (Asf::RowPtrIterator p = (*it)->begin();
				p != (*it)->end(); ++p) {
					for (int i = 0; i < cols_; ++i) {
						data[index] = (**p)[i];
						++index;
					}
			}

			// build QImage from QByteData where each number show color number from ColorTable
			const uchar* point = (uchar*)data.constData();
			QImage image(point, cols_, rows_, cols_, QImage::Format_Indexed8);
			image.setColorTable(grayscale);

			// Scale image to bigger one
			QImage* scaled = new QImage(image.scaledToHeight(400)); // by default fast conversion

			frames.push_back(scaled);
	}
}

QAsfFile::QAsfFile(const QString& fileName) :asfFile(), frames(),rows_(0),cols_(0),count_(0)
{
	QByteArray byteArray = fileName.toUtf8();
	const char* strFileName = byteArray.constData(); // safe conversion

	if (fileName.contains(".gz"))
		asfFile = Asf::createFromGzipFile(strFileName);
	else
		asfFile = Asf::createFromFile(strFileName);

	cols_ = QString::fromStdString(asfFile->getPropertyByName("COLS")).toInt();
	rows_ = QString::fromStdString(asfFile->getPropertyByName("ROWS")).toInt();
	int startFrame = QString::fromStdString(asfFile->getPropertyByName("START_FRAME")).toInt();
	int endFrame = QString::fromStdString(asfFile->getPropertyByName("END_FRAME")).toInt();
	count_ = endFrame - startFrame + 1;

	getFramesFromAsfFile();
}

void QAsfFile::saveToFile(const QString& fileName)
	// write data to file
	// in read only mode useful only for conversion from .asf to .gz and back
{
	QByteArray byteArray = fileName.toUtf8();
	const char* strFileName = byteArray.constData();

	if (fileName.contains(".gz"))
		Asf::writeToGzipFile(strFileName, asfFile);
	else
		Asf::writeToFile(strFileName, asfFile);
}

void QAsfFile::clear()
	// clean memory
{
	if (!frames.empty()) {
		for (QVector<QImage*>::iterator it = frames.begin();
			it != frames.end(); ++it)
			delete *it;
		frames.clear();
	}
}
