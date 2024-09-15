/****************************************************************************
** Meta object code from reading C++ file 'dashboard.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../dashboard.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dashboard.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSdashboardENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSdashboardENDCLASS = QtMocHelpers::stringData(
    "dashboard",
    "membeer",
    "",
    "user",
    "package",
    "safe",
    "sheets",
    "emp",
    "disableButtons_signal",
    "memberClosedSignal",
    "user_closed",
    "member_slot",
    "user_slot",
    "pack_slot",
    "member_enable",
    "disableButtons",
    "safe_click",
    "sheet_click"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSdashboardENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  110,    2, 0x06,    1 /* Public */,
       3,    0,  111,    2, 0x06,    2 /* Public */,
       4,    0,  112,    2, 0x06,    3 /* Public */,
       5,    0,  113,    2, 0x06,    4 /* Public */,
       6,    0,  114,    2, 0x06,    5 /* Public */,
       7,    0,  115,    2, 0x06,    6 /* Public */,
       8,    0,  116,    2, 0x06,    7 /* Public */,
       9,    0,  117,    2, 0x06,    8 /* Public */,
      10,    0,  118,    2, 0x06,    9 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      11,    0,  119,    2, 0x08,   10 /* Private */,
      12,    0,  120,    2, 0x08,   11 /* Private */,
      13,    0,  121,    2, 0x08,   12 /* Private */,
      14,    0,  122,    2, 0x08,   13 /* Private */,
      15,    0,  123,    2, 0x08,   14 /* Private */,
      16,    0,  124,    2, 0x08,   15 /* Private */,
      17,    0,  125,    2, 0x08,   16 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
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

       0        // eod
};

Q_CONSTINIT const QMetaObject dashboard::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSdashboardENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSdashboardENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSdashboardENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<dashboard, std::true_type>,
        // method 'membeer'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'user'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'package'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'safe'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'sheets'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'emp'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'disableButtons_signal'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'memberClosedSignal'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'user_closed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'member_slot'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'user_slot'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'pack_slot'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'member_enable'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'disableButtons'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'safe_click'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'sheet_click'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void dashboard::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<dashboard *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->membeer(); break;
        case 1: _t->user(); break;
        case 2: _t->package(); break;
        case 3: _t->safe(); break;
        case 4: _t->sheets(); break;
        case 5: _t->emp(); break;
        case 6: _t->disableButtons_signal(); break;
        case 7: _t->memberClosedSignal(); break;
        case 8: _t->user_closed(); break;
        case 9: _t->member_slot(); break;
        case 10: _t->user_slot(); break;
        case 11: _t->pack_slot(); break;
        case 12: _t->member_enable(); break;
        case 13: _t->disableButtons(); break;
        case 14: _t->safe_click(); break;
        case 15: _t->sheet_click(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (dashboard::*)();
            if (_t _q_method = &dashboard::membeer; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (dashboard::*)();
            if (_t _q_method = &dashboard::user; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (dashboard::*)();
            if (_t _q_method = &dashboard::package; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (dashboard::*)();
            if (_t _q_method = &dashboard::safe; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (dashboard::*)();
            if (_t _q_method = &dashboard::sheets; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (dashboard::*)();
            if (_t _q_method = &dashboard::emp; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (dashboard::*)();
            if (_t _q_method = &dashboard::disableButtons_signal; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (dashboard::*)();
            if (_t _q_method = &dashboard::memberClosedSignal; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (dashboard::*)();
            if (_t _q_method = &dashboard::user_closed; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 8;
                return;
            }
        }
    }
    (void)_a;
}

const QMetaObject *dashboard::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *dashboard::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSdashboardENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int dashboard::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void dashboard::membeer()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void dashboard::user()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void dashboard::package()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void dashboard::safe()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void dashboard::sheets()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void dashboard::emp()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void dashboard::disableButtons_signal()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void dashboard::memberClosedSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void dashboard::user_closed()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}
QT_WARNING_POP
