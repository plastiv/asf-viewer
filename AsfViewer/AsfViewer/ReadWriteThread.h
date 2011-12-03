#pragma once
#include "AsfLibraryWrapper.h"
#include <QThread>
#include <QString>
#include <QEvent>

// Qt's built-in events have values below 1000. Higher values can be used for custom events.
enum { FileActionStart = 2001, AllFileActionsDone = 2002, FileActionError = 2003 };

class OpenFileThread : public QThread
{
public:
	OpenFileThread(void) {}
	void run();
	void setTargetWidget(QWidget *widget) { targetWidget = widget; }
	void setFileName(const QString& newfileName) { fileName = newfileName; }
	QAsfFile* asfFile() const { return asfFile_;}
	~OpenFileThread(void) {}
private:
	QWidget *targetWidget;
	QString fileName;
	QAsfFile* asfFile_;
};

class ErrorEvent : public QEvent 
{
public:
	ErrorEvent() : QEvent((QEvent::Type)FileActionError) {}
	QString message;
};




