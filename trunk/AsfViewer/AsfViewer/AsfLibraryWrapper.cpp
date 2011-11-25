#include "AsfLibraryWrapper.h"

QVector<QImage*>* getFramesFromAsfFile(const std::tr1::shared_ptr<Asf::AsfFile> asfFile)
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
		it != asfFile->end(); ++it)
	{
		QByteArray data;
		data.resize(pixelCount);
		size_t index = 0;

		for (Asf::RowIterator p = it->begin(); 
			p != it->end(); ++p)
		{
			for (int i = 0; i < colCount; ++i)
			{
				data[index] = (*p)[i];
				++index;
			}
		}

		const uchar * point = (uchar *)data.constData();
		QImage image(point, colCount, rowCount, colCount, QImage::Format_Indexed8);
		image.setColorTable(grayscale);
		QImage* scaled = new QImage(image.scaledToHeight(400));

		frames->push_back(scaled);
	}

	return frames;
}

QVector<QImage*>* getFramesFromFile( const QString& fileName, AsfProperty& asfProperty )
{
	std::tr1::shared_ptr<Asf::AsfFile> asfFile = Asf::createFromFile(fileName.toStdString().c_str());

	asfProperty.cols = QString::fromStdString(asfFile->getPropertyByName("COLS"));
	asfProperty.rows = QString::fromStdString(asfFile->getPropertyByName("ROWS"));
	asfProperty.count = QString::fromStdString(asfFile->getPropertyByName("END_FRAME")); // TODO : not exactly count, but still work

	return getFramesFromAsfFile(asfFile);
}

QVector<QImage*>* getFramesFromGZipFile( const QString& fileName, AsfProperty& asfProperty )
{
	QByteArray byteArray = fileName.toUtf8();
	const char* cString = byteArray.constData();
	std::tr1::shared_ptr<Asf::AsfFile> asfFile = Asf::createFromGzipFile(cString);

	asfProperty.cols = QString::fromStdString(asfFile->getPropertyByName("COLS"));
	asfProperty.rows = QString::fromStdString(asfFile->getPropertyByName("ROWS"));
	asfProperty.count = QString::fromStdString(asfFile->getPropertyByName("END_FRAME")); // TODO : not exactly count, but still work

	return getFramesFromAsfFile(asfFile);
}
