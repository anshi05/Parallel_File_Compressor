/****************************************************************************
** Meta object code from reading C++ file 'compressionworker.hpp'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../include/compressionworker.hpp"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'compressionworker.hpp' doesn't include <QObject>."
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
struct qt_meta_tag_ZN17CompressionWorkerE_t {};
} // unnamed namespace

template <> constexpr inline auto CompressionWorker::qt_create_metaobjectdata<qt_meta_tag_ZN17CompressionWorkerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "CompressionWorker",
        "progressUpdated",
        "",
        "percentage",
        "status",
        "compressionFinished",
        "success",
        "message",
        "uint64_t",
        "originalSize",
        "compressedSize",
        "timeMs",
        "chunkProcessed",
        "chunkIndex",
        "totalChunks",
        "errorOccurred",
        "error",
        "compress",
        "inputFile",
        "outputFile",
        "threadCount"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'progressUpdated'
        QtMocHelpers::SignalData<void(int, const QString &)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 3 }, { QMetaType::QString, 4 },
        }}),
        // Signal 'compressionFinished'
        QtMocHelpers::SignalData<void(bool, const QString &, uint64_t, uint64_t, double)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 6 }, { QMetaType::QString, 7 }, { 0x80000000 | 8, 9 }, { 0x80000000 | 8, 10 },
            { QMetaType::Double, 11 },
        }}),
        // Signal 'chunkProcessed'
        QtMocHelpers::SignalData<void(int, int)>(12, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 13 }, { QMetaType::Int, 14 },
        }}),
        // Signal 'errorOccurred'
        QtMocHelpers::SignalData<void(const QString &)>(15, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 16 },
        }}),
        // Slot 'compress'
        QtMocHelpers::SlotData<void(const QString &, const QString &, int)>(17, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 18 }, { QMetaType::QString, 19 }, { QMetaType::Int, 20 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<CompressionWorker, qt_meta_tag_ZN17CompressionWorkerE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject CompressionWorker::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN17CompressionWorkerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN17CompressionWorkerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN17CompressionWorkerE_t>.metaTypes,
    nullptr
} };

void CompressionWorker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<CompressionWorker *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->progressUpdated((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2]))); break;
        case 1: _t->compressionFinished((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<uint64_t>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<uint64_t>>(_a[4])),(*reinterpret_cast<std::add_pointer_t<double>>(_a[5]))); break;
        case 2: _t->chunkProcessed((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[2]))); break;
        case 3: _t->errorOccurred((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 4: _t->compress((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[3]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (CompressionWorker::*)(int , const QString & )>(_a, &CompressionWorker::progressUpdated, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (CompressionWorker::*)(bool , const QString & , uint64_t , uint64_t , double )>(_a, &CompressionWorker::compressionFinished, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (CompressionWorker::*)(int , int )>(_a, &CompressionWorker::chunkProcessed, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (CompressionWorker::*)(const QString & )>(_a, &CompressionWorker::errorOccurred, 3))
            return;
    }
}

const QMetaObject *CompressionWorker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CompressionWorker::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN17CompressionWorkerE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int CompressionWorker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void CompressionWorker::progressUpdated(int _t1, const QString & _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1, _t2);
}

// SIGNAL 1
void CompressionWorker::compressionFinished(bool _t1, const QString & _t2, uint64_t _t3, uint64_t _t4, double _t5)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1, _t2, _t3, _t4, _t5);
}

// SIGNAL 2
void CompressionWorker::chunkProcessed(int _t1, int _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1, _t2);
}

// SIGNAL 3
void CompressionWorker::errorOccurred(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1);
}
QT_WARNING_POP
