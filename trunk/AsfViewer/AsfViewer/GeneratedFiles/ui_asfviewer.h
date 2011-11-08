/********************************************************************************
** Form generated from reading UI file 'asfviewer.ui'
**
** Created: Tue Nov 8 15:01:03 2011
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ASFVIEWER_H
#define UI_ASFVIEWER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AsfViewerClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *AsfViewerClass)
    {
        if (AsfViewerClass->objectName().isEmpty())
            AsfViewerClass->setObjectName(QString::fromUtf8("AsfViewerClass"));
        AsfViewerClass->resize(600, 400);
        menuBar = new QMenuBar(AsfViewerClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        AsfViewerClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(AsfViewerClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        AsfViewerClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(AsfViewerClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        AsfViewerClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(AsfViewerClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        AsfViewerClass->setStatusBar(statusBar);

        retranslateUi(AsfViewerClass);

        QMetaObject::connectSlotsByName(AsfViewerClass);
    } // setupUi

    void retranslateUi(QMainWindow *AsfViewerClass)
    {
        AsfViewerClass->setWindowTitle(QApplication::translate("AsfViewerClass", "AsfViewer", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class AsfViewerClass: public Ui_AsfViewerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ASFVIEWER_H
