/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../mainwindow.h"
#include <QtGui/qtextcursor.h>
#include <QScreen>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    const uint offsetsAndSize[42];
    char stringdata0[447];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 10), // "MainWindow"
QT_MOC_LITERAL(11, 31), // "on_Add_from_file_button_clicked"
QT_MOC_LITERAL(43, 0), // ""
QT_MOC_LITERAL(44, 27), // "on_chooseFileButton_clicked"
QT_MOC_LITERAL(72, 35), // "on_Alphabetical_sort_Button_c..."
QT_MOC_LITERAL(108, 25), // "on_ID_sort_Button_clicked"
QT_MOC_LITERAL(134, 22), // "on_Save_Button_clicked"
QT_MOC_LITERAL(157, 29), // "on_Search_Mode_Toggle_clicked"
QT_MOC_LITERAL(187, 26), // "on_lineEdit_ID_textChanged"
QT_MOC_LITERAL(214, 4), // "arg1"
QT_MOC_LITERAL(219, 29), // "on_lineEdit_Model_textChanged"
QT_MOC_LITERAL(249, 34), // "on_lineEdit_Horsepower_textCh..."
QT_MOC_LITERAL(284, 31), // "on_comboBox_Types_textActivated"
QT_MOC_LITERAL(316, 26), // "on_Add_from_search_clicked"
QT_MOC_LITERAL(343, 26), // "on_horsepower_sort_clicked"
QT_MOC_LITERAL(370, 24), // "on_checkBox_stateChanged"
QT_MOC_LITERAL(395, 14), // "lineConvertion"
QT_MOC_LITERAL(410, 4), // "line"
QT_MOC_LITERAL(415, 10), // "pick_color"
QT_MOC_LITERAL(426, 11), // "std::string"
QT_MOC_LITERAL(438, 8) // "add_line"

    },
    "MainWindow\0on_Add_from_file_button_clicked\0"
    "\0on_chooseFileButton_clicked\0"
    "on_Alphabetical_sort_Button_clicked\0"
    "on_ID_sort_Button_clicked\0"
    "on_Save_Button_clicked\0"
    "on_Search_Mode_Toggle_clicked\0"
    "on_lineEdit_ID_textChanged\0arg1\0"
    "on_lineEdit_Model_textChanged\0"
    "on_lineEdit_Horsepower_textChanged\0"
    "on_comboBox_Types_textActivated\0"
    "on_Add_from_search_clicked\0"
    "on_horsepower_sort_clicked\0"
    "on_checkBox_stateChanged\0lineConvertion\0"
    "line\0pick_color\0std::string\0add_line"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  110,    2, 0x08,    1 /* Private */,
       3,    0,  111,    2, 0x08,    2 /* Private */,
       4,    0,  112,    2, 0x08,    3 /* Private */,
       5,    0,  113,    2, 0x08,    4 /* Private */,
       6,    0,  114,    2, 0x08,    5 /* Private */,
       7,    0,  115,    2, 0x08,    6 /* Private */,
       8,    1,  116,    2, 0x08,    7 /* Private */,
      10,    1,  119,    2, 0x08,    9 /* Private */,
      11,    1,  122,    2, 0x08,   11 /* Private */,
      12,    1,  125,    2, 0x08,   13 /* Private */,
      13,    0,  128,    2, 0x08,   15 /* Private */,
      14,    0,  129,    2, 0x08,   16 /* Private */,
      15,    1,  130,    2, 0x08,   17 /* Private */,
      16,    1,  133,    2, 0x08,   19 /* Private */,
      18,    0,  136,    2, 0x08,   21 /* Private */,
      20,    1,  137,    2, 0x08,   22 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::QString, QMetaType::QString,   17,
    0x80000000 | 19,
    QMetaType::Void, QMetaType::QString,   17,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_Add_from_file_button_clicked(); break;
        case 1: _t->on_chooseFileButton_clicked(); break;
        case 2: _t->on_Alphabetical_sort_Button_clicked(); break;
        case 3: _t->on_ID_sort_Button_clicked(); break;
        case 4: _t->on_Save_Button_clicked(); break;
        case 5: _t->on_Search_Mode_Toggle_clicked(); break;
        case 6: _t->on_lineEdit_ID_textChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 7: _t->on_lineEdit_Model_textChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 8: _t->on_lineEdit_Horsepower_textChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 9: _t->on_comboBox_Types_textActivated((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 10: _t->on_Add_from_search_clicked(); break;
        case 11: _t->on_horsepower_sort_clicked(); break;
        case 12: _t->on_checkBox_stateChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 13: { QString _r = _t->lineConvertion((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 14: { std::string _r = _t->pick_color();
            if (_a[0]) *reinterpret_cast< std::string*>(_a[0]) = std::move(_r); }  break;
        case 15: _t->add_line((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.offsetsAndSize,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_MainWindow_t
, QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<std::string, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>


>,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
