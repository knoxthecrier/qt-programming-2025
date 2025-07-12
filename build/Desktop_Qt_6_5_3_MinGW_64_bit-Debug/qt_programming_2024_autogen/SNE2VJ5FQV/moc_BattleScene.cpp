/****************************************************************************
** Meta object code from reading C++ file 'BattleScene.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/Scenes/BattleScene.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'BattleScene.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.5.3. It"
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
struct qt_meta_stringdata_CLASSBattleSceneENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSBattleSceneENDCLASS = QtMocHelpers::stringData(
    "BattleScene",
    "update",
    "",
    "handlePickUp",
    "SimpleCharacter*",
    "character"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSBattleSceneENDCLASS_t {
    uint offsetsAndSizes[12];
    char stringdata0[12];
    char stringdata1[7];
    char stringdata2[1];
    char stringdata3[13];
    char stringdata4[17];
    char stringdata5[10];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSBattleSceneENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSBattleSceneENDCLASS_t qt_meta_stringdata_CLASSBattleSceneENDCLASS = {
    {
        QT_MOC_LITERAL(0, 11),  // "BattleScene"
        QT_MOC_LITERAL(12, 6),  // "update"
        QT_MOC_LITERAL(19, 0),  // ""
        QT_MOC_LITERAL(20, 12),  // "handlePickUp"
        QT_MOC_LITERAL(33, 16),  // "SimpleCharacter*"
        QT_MOC_LITERAL(50, 9)   // "character"
    },
    "BattleScene",
    "update",
    "",
    "handlePickUp",
    "SimpleCharacter*",
    "character"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSBattleSceneENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   26,    2, 0x09,    1 /* Protected */,
       3,    1,   27,    2, 0x08,    2 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,

       0        // eod
};

Q_CONSTINIT const QMetaObject BattleScene::staticMetaObject = { {
    QMetaObject::SuperData::link<Scene::staticMetaObject>(),
    qt_meta_stringdata_CLASSBattleSceneENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSBattleSceneENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSBattleSceneENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<BattleScene, std::true_type>,
        // method 'update'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'handlePickUp'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<SimpleCharacter *, std::false_type>
    >,
    nullptr
} };

void BattleScene::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<BattleScene *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->update(); break;
        case 1: _t->handlePickUp((*reinterpret_cast< std::add_pointer_t<SimpleCharacter*>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< SimpleCharacter* >(); break;
            }
            break;
        }
    }
}

const QMetaObject *BattleScene::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BattleScene::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSBattleSceneENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return Scene::qt_metacast(_clname);
}

int BattleScene::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Scene::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_WARNING_POP
