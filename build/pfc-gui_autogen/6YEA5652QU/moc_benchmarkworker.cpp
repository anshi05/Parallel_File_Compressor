/****************************************************************************
** Meta object code from reading C++ file 'benchmarkworker.hpp'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../include/benchmarkworker.hpp"
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'benchmarkworker.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
namespace {
struct qt_meta_stringdata_BenchmarkWorker_t {
    uint offsetsAndSizes[34];
    char stringdata0[16];
    char stringdata1[16];
    char stringdata2[1];
    char stringdata3[7];
    char stringdata4[18];
    char stringdata5[15];
    char stringdata6[13];
    char stringdata7[8];
    char stringdata8[11];
    char stringdata9[9];
    char stringdata10[13];
    char stringdata11[15];
    char stringdata12[14];
    char stringdata13[6];
    char stringdata14[13];
    char stringdata15[10];
    char stringdata16[12];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_BenchmarkWorker_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_BenchmarkWorker_t qt_meta_stringdata_BenchmarkWorker = {
    {
        QT_MOC_LITERAL(0, 15),  // "BenchmarkWorker"
        QT_MOC_LITERAL(16, 15),  // "progressUpdated"
        QT_MOC_LITERAL(32, 0),  // ""
        QT_MOC_LITERAL(33, 6),  // "status"
        QT_MOC_LITERAL(40, 17),  // "benchmarkFinished"
        QT_MOC_LITERAL(58, 14),  // "sequentialTime"
        QT_MOC_LITERAL(73, 12),  // "parallelTime"
        QT_MOC_LITERAL(86, 7),  // "speedup"
        QT_MOC_LITERAL(94, 10),  // "efficiency"
        QT_MOC_LITERAL(105, 8),  // "uint64_t"
        QT_MOC_LITERAL(114, 12),  // "originalSize"
        QT_MOC_LITERAL(127, 14),  // "compressedSize"
        QT_MOC_LITERAL(142, 13),  // "errorOccurred"
        QT_MOC_LITERAL(156, 5),  // "error"
        QT_MOC_LITERAL(162, 12),  // "runBenchmark"
        QT_MOC_LITERAL(175, 9),  // "inputFile"
        QT_MOC_LITERAL(185, 11)   // "threadCount"
    },
    "BenchmarkWorker",
    "progressUpdated",
    "",
    "status",
    "benchmarkFinished",
    "sequentialTime",
    "parallelTime",
    "speedup",
    "efficiency",
    "uint64_t",
    "originalSize",
    "compressedSize",
    "errorOccurred",
    "error",
    "runBenchmark",
    "inputFile",
    "threadCount"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_BenchmarkWorker[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   38,    2, 0x06,    1 /* Public */,
       4,    6,   41,    2, 0x06,    3 /* Public */,
      12,    1,   54,    2, 0x06,   10 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      14,    2,   57,    2, 0x0a,   12 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, 0x80000000 | 9, 0x80000000 | 9,    5,    6,    7,    8,   10,   11,
    QMetaType::Void, QMetaType::QString,   13,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   15,   16,

       0        // eod
};

Q_CONSTINIT const QMetaObject BenchmarkWorker::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_BenchmarkWorker.offsetsAndSizes,
    qt_meta_data_BenchmarkWorker,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_BenchmarkWorker_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<BenchmarkWorker, std::true_type>,
        // method 'progressUpdated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'benchmarkFinished'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<uint64_t, std::false_type>,
        QtPrivate::TypeAndForceComplete<uint64_t, std::false_type>,
        // method 'errorOccurred'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'runBenchmark'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>
    >,
    nullptr
} };

void BenchmarkWorker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<BenchmarkWorker *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->progressUpdated((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->benchmarkFinished((*reinterpret_cast< std::add_pointer_t<double>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<uint64_t>>(_a[5])),(*reinterpret_cast< std::add_pointer_t<uint64_t>>(_a[6]))); break;
        case 2: _t->errorOccurred((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 3: _t->runBenchmark((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (BenchmarkWorker::*)(const QString & );
            if (_t _q_method = &BenchmarkWorker::progressUpdated; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (BenchmarkWorker::*)(double , double , double , double , uint64_t , uint64_t );
            if (_t _q_method = &BenchmarkWorker::benchmarkFinished; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (BenchmarkWorker::*)(const QString & );
            if (_t _q_method = &BenchmarkWorker::errorOccurred; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject *BenchmarkWorker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BenchmarkWorker::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_BenchmarkWorker.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int BenchmarkWorker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void BenchmarkWorker::progressUpdated(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void BenchmarkWorker::benchmarkFinished(double _t1, double _t2, double _t3, double _t4, uint64_t _t5, uint64_t _t6)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t5))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t6))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void BenchmarkWorker::errorOccurred(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
