/********************************************************************************
** Form generated from reading UI file 'asfviewer.ui'
**
** Created: Mon Nov 21 15:32:35 2011
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
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AsfViewerClass
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *AsfViewerClass)
    {
        if (AsfViewerClass->objectName().isEmpty())
            AsfViewerClass->setObjectName(QString::fromUtf8("AsfViewerClass"));
        AsfViewerClass->resize(489, 376);
        centralWidget = new QWidget(AsfViewerClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        verticalLayout_2->addWidget(label);

        AsfViewerClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(AsfViewerClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 489, 26));
        AsfViewerClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(AsfViewerClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        AsfViewerClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(AsfViewerClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        AsfViewerClass->setStatusBar(statusBar);

        retranslateUi(AsfViewerClass);

        QMetaObject::connectSlotsByName(AsfViewerClass);
    } // setupUi

    void retranslateUi(QMainWindow *AsfViewerClass)
    {
        AsfViewerClass->setWindowTitle(QApplication::translate("AsfViewerClass", "AsfViewer", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("AsfViewerClass", "TextLabel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class AsfViewerClass: public Ui_AsfViewerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ASFVIEWER_H
