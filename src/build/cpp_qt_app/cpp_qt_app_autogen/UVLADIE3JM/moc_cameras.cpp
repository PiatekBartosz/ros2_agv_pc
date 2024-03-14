/****************************************************************************
** Meta object code from reading C++ file 'cameras.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../cpp_qt_app/src/cameras.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cameras.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Cameras_t {
    QByteArrayData data[14];
    char stringdata0[212];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Cameras_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Cameras_t qt_meta_stringdata_Cameras = {
    {
QT_MOC_LITERAL(0, 0, 7), // "Cameras"
QT_MOC_LITERAL(1, 8, 11), // "HomeClicked"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 14), // "ControlClicked"
QT_MOC_LITERAL(4, 36, 15), // "SettingsClicked"
QT_MOC_LITERAL(5, 52, 30), // "on_pushButton_settings_clicked"
QT_MOC_LITERAL(6, 83, 29), // "on_pushButton_control_clicked"
QT_MOC_LITERAL(7, 113, 26), // "on_pushButton_home_clicked"
QT_MOC_LITERAL(8, 140, 10), // "captureRun"
QT_MOC_LITERAL(9, 151, 7), // "QLabel*"
QT_MOC_LITERAL(10, 159, 5), // "label"
QT_MOC_LITERAL(11, 165, 12), // "QPushButton*"
QT_MOC_LITERAL(12, 178, 3), // "btn"
QT_MOC_LITERAL(13, 182, 29) // "on_pushbutton_capture_clicked"

    },
    "Cameras\0HomeClicked\0\0ControlClicked\0"
    "SettingsClicked\0on_pushButton_settings_clicked\0"
    "on_pushButton_control_clicked\0"
    "on_pushButton_home_clicked\0captureRun\0"
    "QLabel*\0label\0QPushButton*\0btn\0"
    "on_pushbutton_capture_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Cameras[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,
       3,    0,   55,    2, 0x06 /* Public */,
       4,    0,   56,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   57,    2, 0x08 /* Private */,
       6,    0,   58,    2, 0x08 /* Private */,
       7,    0,   59,    2, 0x08 /* Private */,
       8,    2,   60,    2, 0x08 /* Private */,
      13,    0,   65,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9, 0x80000000 | 11,   10,   12,
    QMetaType::Void,

       0        // eod
};

void Cameras::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Cameras *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->HomeClicked(); break;
        case 1: _t->ControlClicked(); break;
        case 2: _t->SettingsClicked(); break;
        case 3: _t->on_pushButton_settings_clicked(); break;
        case 4: _t->on_pushButton_control_clicked(); break;
        case 5: _t->on_pushButton_home_clicked(); break;
        case 6: _t->captureRun((*reinterpret_cast< QLabel*(*)>(_a[1])),(*reinterpret_cast< QPushButton*(*)>(_a[2]))); break;
        case 7: _t->on_pushbutton_capture_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QLabel* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Cameras::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Cameras::HomeClicked)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Cameras::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Cameras::ControlClicked)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Cameras::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Cameras::SettingsClicked)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Cameras::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_Cameras.data,
    qt_meta_data_Cameras,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Cameras::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Cameras::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Cameras.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int Cameras::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void Cameras::HomeClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Cameras::ControlClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Cameras::SettingsClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
