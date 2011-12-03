/****************************************************************************
** Meta object code from reading C++ file 'AsfViewer.h'
**
** Created: Sat Dec 3 12:26:28 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "StdAfx.h"
#include "..\..\AsfViewer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AsfViewer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AsfViewer[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x08,
      18,   10,   10,   10, 0x08,
      30,   10,   10,   10, 0x08,
      41,   10,   10,   10, 0x08,
      50,   10,   10,   10, 0x08,
      60,   10,   10,   10, 0x08,
      73,   10,   10,   10, 0x08,
      87,   10,   10,   10, 0x08,
      95,   10,   10,   10, 0x08,
     115,   10,   10,   10, 0x08,
     132,   10,   10,   10, 0x08,
     148,   10,   10,   10, 0x08,
     164,   10,   10,   10, 0x08,
     180,   10,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_AsfViewer[] = {
    "AsfViewer\0\0open()\0closeFile()\0saveFile()\0"
    "zoomIn()\0zoomOut()\0normalSize()\0"
    "fitToWindow()\0about()\0numberEditChanged()\0"
    "goToFirstFrame()\0goToPrevFrame()\0"
    "goToNextFrame()\0goToLastFrame()\0"
    "autoPlayFrames()\0"
};

const QMetaObject AsfViewer::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_AsfViewer,
      qt_meta_data_AsfViewer, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AsfViewer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AsfViewer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AsfViewer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AsfViewer))
        return static_cast<void*>(const_cast< AsfViewer*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int AsfViewer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: open(); break;
        case 1: closeFile(); break;
        case 2: saveFile(); break;
        case 3: zoomIn(); break;
        case 4: zoomOut(); break;
        case 5: normalSize(); break;
        case 6: fitToWindow(); break;
        case 7: about(); break;
        case 8: numberEditChanged(); break;
        case 9: goToFirstFrame(); break;
        case 10: goToPrevFrame(); break;
        case 11: goToNextFrame(); break;
        case 12: goToLastFrame(); break;
        case 13: autoPlayFrames(); break;
        default: ;
        }
        _id -= 14;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
