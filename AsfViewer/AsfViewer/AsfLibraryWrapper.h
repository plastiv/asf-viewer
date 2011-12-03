#pragma once
#include "AsfFile.h"
#include "AsfFileUtilities.h"
#include <QtGui/QImage>
#include <QtGui/QPixmap>

#include <QVector>
#include <QByteArray>
#include <QString>

// Separate library realization from GUI (also Qt from STL)

class QAsfFile{
	// include here only interested for GUI fields from AsfFile
	// TODO : build QImage frame by frame, cause it cost a lot of memory
public:
	QAsfFile(const QString& fileName);
	void saveToFile(const QString& fileName);

	QVector<QImage*>::const_iterator begin() const { return frames.begin(); }
	QVector<QImage*>::const_iterator end() const { return frames.end(); }
	int size() const {return frames.size();}
	void clear();

	QString rows() {return QString::number(rows_); }
	QString cols() {return QString::number(cols_); }
	QString count() {return QString::number(count_); }
	~QAsfFile() { clear(); }
private:
	QVector<QImage*> frames;
	std::tr1::shared_ptr<Asf::AsfFile> asfFile;
	int rows_;
	int cols_;
	int count_;

	void getFramesFromAsfFile();
};
