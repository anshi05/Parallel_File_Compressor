/****************************************************************************
** Meta object code from reading C++ file 'decompressionworker.hpp'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../include/decompressionworker.hpp"
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'decompressionworker.hpp' doesn't include <QObject>."
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
struct qt_meta_stringdata_DecompressionWorker_t {
    uint offsetsAndSizes[36];
    char stringdata0[20];
    char stringdata1[16];
    char stringdata2[1];
    char stringdata3[11];
    char stringdata4[7];
    char stringdata5[22];
    char stringdata6[8];
    char stringdata7[8];
    char stringdata8[7];
    char stringdata9[15];
    char stringdata10[11];
    char stringdata11[12];
    char stringdata12[14];
    char stringdata13[6];
    char stringdata14[11];
    char stringdata15[10];
    char stringdata16[11];
    char stringdata17[12];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_DecompressionWorker_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_DecompressionWorker_t qt_meta_stringdata_DecompressionWorker = {
    {
        QT_MOC_LITERAL(0, 19),  // "DecompressionWorker"
        QT_MOC_LITERAL(20, 15),  // "progressUpdated"
        QT_MOC_LITERAL(36, 0),  // ""
        QT_MOC_LITERAL(37, 10),  // "percentage"
        QT_MOC_LITERAL(48, 6),  // "status"
        QT_MOC_LITERAL(55, 21),  // "decompressionFinished"
        QT_MOC_LITERAL(77, 7),  // "success"
        QT_MOC_LITERAL(85, 7),  // "message"
        QT_MOC_LITERAL(93, 6),  // "timeMs"
        QT_MOC_LITERAL(100, 14),  // "chunkProcessed"
        QT_MOC_LITERAL(115, 10),  // "chunkIndex"
        QT_MOC_LITERAL(126, 11),  // "totalChunks"
        QT_MOC_LITERAL(138, 13),  // "errorOccurred"
        QT_MOC_LITERAL(152, 5),  // "error"
        QT_MOC_LITERAL(158, 10),  // "decompress"
        QT_MOC_LITERAL(169, 9),  // "inputFile"
        QT_MOC_LITERAL(179, 10),  // "outputFile"
        QT_MOC_LITERAL(190, 11)   // "threadCount"
    },
    "DecompressionWorker",
    "progressUpdated",
    "",
    "percentage",
    "status",
    "decompressionFinished",
    "success",
    "message",
    "timeMs",
    "chunkProcessed",
    "chunkIndex",
    "totalChunks",
    "errorOccurred",
    "error",
    "decompress",
    "inputFile",
    "outputFile",
    "threadCount"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_DecompressionWorker[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,   44,    2, 0x06,    1 /* Public */,
       5,    3,   49,    2, 0x06,    4 /* Public */,
       9,    2,   56,    2, 0x06,    8 /* Public */,
      12,    1,   61,    2, 0x06,   11 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      14,    3,   64,    2, 0x0a,   13 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    3,    4,
    QMetaType::Void, QMetaType::Bool, QMetaType::QString, QMetaType::Double,    6,    7,    8,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   10,   11,
    QMetaType::Void, QMetaType::QString,   13,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Int,   15,   16,   17,

       0        // eod
};

Q_CONSTINIT const QMetaObject DecompressionWorker::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_DecompressionWorker.offsetsAndSizes,
    qt_meta_data_DecompressionWorker,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_DecompressionWorker_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<DecompressionWorker, std::true_type>,
        // method 'progressUpdated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'decompressionFinished'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'chunkProcessed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'errorOccurred'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'decompress'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>
    >,
    nullptr
} };

void DecompressionWorker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DecompressionWorker *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->progressUpdated((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 1: _t->decompressionFinished((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[3]))); break;
        case 2: _t->chunkProcessed((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 3: _t->errorOccurred((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 4: _t->decompress((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (DecompressionWorker::*)(int , const QString & );
            if (_t _q_method = &DecompressionWorker::progressUpdated; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (DecompressionWorker::*)(bool , const QString & , double );
            if (_t _q_method = &DecompressionWorker::decompressionFinished; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (DecompressionWorker::*)(int , int );
            if (_t _q_method = &DecompressionWorker::chunkProcessed; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (DecompressionWorker::*)(const QString & );
            if (_t _q_method = &DecompressionWorker::errorOccurred; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject *DecompressionWorker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DecompressionWorker::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DecompressionWorker.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int DecompressionWorker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void DecompressionWorker::progressUpdated(int _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DecompressionWorker::decompressionFinished(bool _t1, const QString & _t2, double _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void DecompressionWorker::chunkProcessed(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void DecompressionWorker::errorOccurred(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
