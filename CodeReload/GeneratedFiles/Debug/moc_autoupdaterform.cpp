/****************************************************************************
** Meta object code from reading C++ file 'autoupdaterform.h'
**
** Created: Sat Dec 10 09:10:48 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../autoupdaterform.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'autoupdaterform.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AutoUpdaterForm[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x0a,
      34,   16,   16,   16, 0x0a,
      50,   16,   16,   16, 0x0a,
      74,   16,   16,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_AutoUpdaterForm[] = {
    "AutoUpdaterForm\0\0onRefreshClick()\0"
    "onSelectClick()\0onImportPatternsClick()\0"
    "onScanClick()\0"
};

const QMetaObject AutoUpdaterForm::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_AutoUpdaterForm,
      qt_meta_data_AutoUpdaterForm, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AutoUpdaterForm::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AutoUpdaterForm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AutoUpdaterForm::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AutoUpdaterForm))
        return static_cast<void*>(const_cast< AutoUpdaterForm*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int AutoUpdaterForm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: onRefreshClick(); break;
        case 1: onSelectClick(); break;
        case 2: onImportPatternsClick(); break;
        case 3: onScanClick(); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
