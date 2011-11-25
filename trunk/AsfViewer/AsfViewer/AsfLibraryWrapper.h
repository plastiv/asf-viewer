#include "AsfLibrary/AsfFile.h"
#include "AsfLibrary/AsfFileUtilities.h"
#include <QtGui/QImage>
#include <QtGui/QPixmap>

#include <QVector>
#include <QByteArray>
#include <QString>

// Separate library realization from GUI (also Qt from STL)

struct AsfProperty{
	QString rows;
	QString cols;
	QString count;
};

QVector<QImage*>* getFramesFromFile( const QString& fileName, AsfProperty& asfProperty );
QVector<QImage*>* getFramesFromGZipFile( const QString& fileName, AsfProperty& asfProperty );

