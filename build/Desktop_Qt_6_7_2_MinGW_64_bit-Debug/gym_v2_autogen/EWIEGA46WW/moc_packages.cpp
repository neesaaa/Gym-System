/****************************************************************************
** Meta object code from reading C++ file 'packages.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../packages.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'packages.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSpackagesENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSpackagesENDCLASS = QtMocHelpers::stringData(
    "packages",
    "pack_closed",
    "",
    "added",
    "pack_save",
    "pack_edit",
    "pack_search",
    "pack_delete",
    "clearData",
    "pt_save",
    "pt_search",
    "pt_edit",
    "pt_delete",
    "clearData_pt",
    "updateIcon"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSpackagesENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   92,    2, 0x06,    1 /* Public */,
       3,    0,   93,    2, 0x06,    2 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       4,    0,   94,    2, 0x08,    3 /* Private */,
       5,    0,   95,    2, 0x08,    4 /* Private */,
       6,    0,   96,    2, 0x08,    5 /* Private */,
       7,    0,   97,    2, 0x08,    6 /* Private */,
       8,    0,   98,    2, 0x08,    7 /* Private */,
       9,    0,   99,    2, 0x08,    8 /* Private */,
      10,    0,  100,    2, 0x08,    9 /* Private */,
      11,    0,  101,    2, 0x08,   10 /* Private */,
      12,    0,  102,    2, 0x08,   11 /* Private */,
      13,    0,  103,    2, 0x08,   12 /* Private */,
      14,    0,  104,    2, 0x08,   13 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject packages::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSpackagesENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSpackagesENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSpackagesENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<packages, std::true_type>,
        // method 'pack_closed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'added'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'pack_save'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'pack_edit'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'pack_search'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'pack_delete'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'clearData'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'pt_save'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'pt_search'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'pt_edit'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'pt_delete'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'clearData_pt'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateIcon'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void packages::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<packages *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->pack_closed(); break;
        case 1: _t->added(); break;
        case 2: _t->pack_save(); break;
        case 3: _t->pack_edit(); break;
        case 4: _t->pack_search(); break;
        case 5: _t->pack_delete(); break;
        case 6: _t->clearData(); break;
        case 7: _t->pt_save(); break;
        case 8: _t->pt_search(); break;
        case 9: _t->pt_edit(); break;
        case 10: _t->pt_delete(); break;
        case 11: _t->clearData_pt(); break;
        case 12: _t->updateIcon(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (packages::*)();
            if (_t _q_method = &packages::pack_closed; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (packages::*)();
            if (_t _q_method = &packages::added; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
    }
    (void)_a;
}

const QMetaObject *packages::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *packages::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSpackagesENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int packages::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void packages::pack_closed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void packages::added()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
