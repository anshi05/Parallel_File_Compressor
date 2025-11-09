/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.hpp'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../include/mainwindow.hpp"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.10.0. It"
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
struct qt_meta_tag_ZN10MainWindowE_t {};
} // unnamed namespace

template <> constexpr inline auto MainWindow::qt_create_metaobjectdata<qt_meta_tag_ZN10MainWindowE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "MainWindow",
        "onCompressClicked",
        "",
        "onDecompressClicked",
        "onBenchmarkClicked",
        "onSelectInputFile",
        "onSelectOutputFile",
        "onCompressionProgress",
        "percentage",
        "status",
        "onCompressionFinished",
        "success",
        "message",
        "uint64_t",
        "originalSize",
        "compressedSize",
        "timeMs",
        "onDecompressionProgress",
        "onDecompressionFinished",
        "onBenchmarkProgress",
        "onBenchmarkFinished",
        "sequentialTime",
        "parallelTime",
        "speedup",
        "efficiency",
        "onWorkerError",
        "error",
        "onShowAbout"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'onCompressClicked'
        QtMocHelpers::SlotData<void()>(1, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onDecompressClicked'
        QtMocHelpers::SlotData<void()>(3, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onBenchmarkClicked'
        QtMocHelpers::SlotData<void()>(4, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onSelectInputFile'
        QtMocHelpers::SlotData<void()>(5, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onSelectOutputFile'
        QtMocHelpers::SlotData<void()>(6, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onCompressionProgress'
        QtMocHelpers::SlotData<void(int, const QString &)>(7, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 8 }, { QMetaType::QString, 9 },
        }}),
        // Slot 'onCompressionFinished'
        QtMocHelpers::SlotData<void(bool, const QString &, uint64_t, uint64_t, double)>(10, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Bool, 11 }, { QMetaType::QString, 12 }, { 0x80000000 | 13, 14 }, { 0x80000000 | 13, 15 },
            { QMetaType::Double, 16 },
        }}),
        // Slot 'onDecompressionProgress'
        QtMocHelpers::SlotData<void(int, const QString &)>(17, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 8 }, { QMetaType::QString, 9 },
        }}),
        // Slot 'onDecompressionFinished'
        QtMocHelpers::SlotData<void(bool, const QString &, double)>(18, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Bool, 11 }, { QMetaType::QString, 12 }, { QMetaType::Double, 16 },
        }}),
        // Slot 'onBenchmarkProgress'
        QtMocHelpers::SlotData<void(const QString &)>(19, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 9 },
        }}),
        // Slot 'onBenchmarkFinished'
        QtMocHelpers::SlotData<void(double, double, double, double, uint64_t, uint64_t)>(20, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Double, 21 }, { QMetaType::Double, 22 }, { QMetaType::Double, 23 }, { QMetaType::Double, 24 },
            { 0x80000000 | 13, 14 }, { 0x80000000 | 13, 15 },
        }}),
        // Slot 'onWorkerError'
        QtMocHelpers::SlotData<void(const QString &)>(25, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 26 },
        }}),
        // Slot 'onShowAbout'
        QtMocHelpers::SlotData<void()>(27, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<MainWindow, qt_meta_tag_ZN10MainWindowE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MainWindowE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MainWindowE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN10MainWindowE_t>.metaTypes,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<MainWindow *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->onCompressClicked(); break;
        case 1: _t->onDecompressClicked(); break;
        case 2: _t->onBenchmarkClicked(); break;
        case 3: _t->onSelectInputFile(); break;
        case 4: _t->onSelectOutputFile(); break;
        case 5: _t->onCompressionProgress((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2]))); break;
        case 6: _t->onCompressionFinished((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<uint64_t>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<uint64_t>>(_a[4])),(*reinterpret_cast<std::add_pointer_t<double>>(_a[5]))); break;
        case 7: _t->onDecompressionProgress((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2]))); break;
        case 8: _t->onDecompressionFinished((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<double>>(_a[3]))); break;
        case 9: _t->onBenchmarkProgress((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 10: _t->onBenchmarkFinished((*reinterpret_cast<std::add_pointer_t<double>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<double>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<double>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<double>>(_a[4])),(*reinterpret_cast<std::add_pointer_t<uint64_t>>(_a[5])),(*reinterpret_cast<std::add_pointer_t<uint64_t>>(_a[6]))); break;
        case 11: _t->onWorkerError((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 12: _t->onShowAbout(); break;
        default: ;
        }
    }
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MainWindowE_t>.strings))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 13;
    }
    return _id;
}
QT_WARNING_POP
