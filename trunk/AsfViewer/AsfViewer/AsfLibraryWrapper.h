#include "AsfLibrary/AsfFile.h"
#include "AsfLibrary/AsfFileUtilities.h"
#include <QtGui/QImage>
#include <QtGui/QPixmap>

#include <QVector>
#include <QByteArray>
#include <QString>

// Separate library realization from GUI (also Qt from STL)

class AsfFile{
	// include here only interested for GUI fields from AsfFile
public:
	AsfFile(const QString& fileName);
	void saveToFile(const QString& fileName);

	QVector<QImage*>::const_iterator begin() const { return frames.begin(); }
	QVector<QImage*>::const_iterator end() const { return frames.end(); }
	int size() const {return frames.size();}
	void clear();

	const QString rows() {return rows_; }
	const QString cols() {return cols_; }
	const QString count() {return count_; }
	~AsfFile();
private:
	QVector<QImage*> frames;
	std::tr1::shared_ptr<Asf::AsfFile> asfFile;
	QString rows_;
	QString cols_;
	QString count_;

	QVector<QImage*>* getFramesFromAsfFile();
};
