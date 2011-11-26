#include "AsfLibraryWrapper.h"

QVector<QImage*>* AsfFile::getFramesFromAsfFile()
{
	const size_t rowCount = atoi(asfFile->getPropertyByName("ROWS").c_str());
	const size_t colCount = atoi(asfFile->getPropertyByName("COLS").c_str());
	const size_t pixelCount = rowCount*colCount;

	// Build greyscale color table
	QVector<QRgb> grayscale;
	for (int i = 0; i < 256; ++i) {
		grayscale.append(qRgb(i, i, i));
	}

	QVector<QImage*>* frames = new QVector<QImage*>();

	for (Asf::FrameIterator it = asfFile->begin();
		it != asfFile->end(); ++it) {
		QByteArray data;
		data.resize(pixelCount);
		size_t index = 0;

		for (Asf::RowIterator p = it->begin();
			p != it->end(); ++p) {
			for (int i = 0; i < colCount; ++i) {
				data[index] = (*p)[i];
				++index;
			}
		}

		const uchar* point = (uchar*)data.constData();
		QImage image(point, colCount, rowCount, colCount, QImage::Format_Indexed8);
		image.setColorTable(grayscale);
		QImage* scaled = new QImage(image.scaledToHeight(400));

		frames->push_back(scaled);
	}

	return frames;
}

AsfFile::AsfFile(const QString& fileName) :asfFile(), frames(),rows_(),cols_(),count_()
{
	QByteArray byteArray = fileName.toUtf8();
	const char* strFileName = byteArray.constData();

	if (fileName.contains(".gz"))
		asfFile = Asf::createFromGzipFile(strFileName);
	else
		asfFile = Asf::createFromFile(strFileName);

	cols_ = QString::fromStdString(asfFile->getPropertyByName("COLS"));
	rows_ = QString::fromStdString(asfFile->getPropertyByName("ROWS"));
	count_ = QString::fromStdString(asfFile->getPropertyByName("END_FRAME")); // TODO : not exactly count, but still work

	frames = *getFramesFromAsfFile();
}

void AsfFile::saveToFile(const QString& fileName)
{
	// TODO Make two projects in one!)


	//QByteArray byteArray = fileName.toUtf8();
	//const char* strFileName = byteArray.constData();

	//if (fileName.contains(".gz"))
	//	Asf::writeToGzipFile(strFileName, asfFile);
	//else
	//	asfFile = Asf::createFromFile(strFileName);

	//cols_ = QString::fromStdString(asfFile->getPropertyByName("COLS"));
	//rows_ = QString::fromStdString(asfFile->getPropertyByName("ROWS"));
	//count_ = QString::fromStdString(asfFile->getPropertyByName("END_FRAME")); // TODO : not exactly count, but still work

	//frames = *getFramesFromAsfFile();
}

void AsfFile::clear()
{
	if (!frames.empty()) {
		for (QVector<QImage*>::iterator it = frames.begin();
			it != frames.end(); ++it)
			delete *it;
		frames.clear();
	}
}

AsfFile::~AsfFile()
{
	clear();
}
