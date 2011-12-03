#include "stdafx.h"
#include "ReadWriteThread.h"

void OpenFileThread::run()
{
	QApplication::postEvent(targetWidget, new QEvent((QEvent::Type)FileActionStart));

	try {
		asfFile_ = new QAsfFile(fileName); // open file
	}
	catch (std::exception& e) {
		ErrorEvent *errorEvent = new ErrorEvent();
		errorEvent->message = e.what();
		QApplication::postEvent(targetWidget, errorEvent);
		return;
	}
	catch (...) {
		ErrorEvent *errorEvent = new ErrorEvent();
		errorEvent->message = "Unknown error";
		QApplication::postEvent(targetWidget, errorEvent);
		return;
	}

	QApplication::postEvent(targetWidget,
		new QEvent((QEvent::Type)AllFileActionsDone));
}



