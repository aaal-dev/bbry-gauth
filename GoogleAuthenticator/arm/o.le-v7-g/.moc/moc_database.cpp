/****************************************************************************
** Meta object code from reading C++ file 'database.hpp'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/database.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'database.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Database[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       9,   79, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x05,
      30,    9,    9,    9, 0x05,
      57,    9,    9,    9, 0x05,
      88,    9,    9,    9, 0x05,
     120,    9,    9,    9, 0x05,
     147,    9,    9,    9, 0x05,
     173,    9,    9,    9, 0x05,
     198,    9,    9,    9, 0x05,
     231,    9,    9,    9, 0x05,

 // methods: signature, parameters, type, tag, flags
     266,    9,  261,    9, 0x02,
     277,    9,  261,    9, 0x02,
     289,    9,  261,    9, 0x02,
     302,    9,  261,    9, 0x02,

 // properties: name, type, flags
     319,  315, 0x02495103,
     330,  322, 0x0a495103,
     336,  322, 0x0a495103,
     346,  322, 0x0a495103,
     357,  315, 0x02495103,
     367,  315, 0x02495103,
     376,  315, 0x02495103,
     384,  322, 0x0a495103,
     396,  322, 0x0a495103,

 // properties: notify_signal_id
       0,
       1,
       2,
       3,
       4,
       5,
       6,
       7,
       8,

       0        // eod
};

static const char qt_meta_stringdata_Database[] = {
    "Database\0\0idValueChanged(int)\0"
    "titleValueChanged(QString)\0"
    "authLoginValueChanged(QString)\0"
    "secretCodeValueChanged(QString)\0"
    "keyLenghtValueChanged(int)\0"
    "authTypeValueChanged(int)\0"
    "counterValueChanged(int)\0"
    "publishDateValueChanged(QString)\0"
    "editDateValueChanged(QString)\0bool\0"
    "readData()\0writeData()\0updateData()\0"
    "deleteData()\0int\0id\0QString\0title\0"
    "authLogin\0secretCode\0keyLenght\0authType\0"
    "counter\0publishDate\0editDate\0"
};

void Database::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Database *_t = static_cast<Database *>(_o);
        switch (_id) {
        case 0: _t->idValueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->titleValueChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->authLoginValueChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->secretCodeValueChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->keyLenghtValueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->authTypeValueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->counterValueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->publishDateValueChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->editDateValueChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: { bool _r = _t->readData();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 10: { bool _r = _t->writeData();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 11: { bool _r = _t->updateData();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 12: { bool _r = _t->deleteData();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Database::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Database::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Database,
      qt_meta_data_Database, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Database::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Database::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Database::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Database))
        return static_cast<void*>(const_cast< Database*>(this));
    return QObject::qt_metacast(_clname);
}

int Database::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = getId(); break;
        case 1: *reinterpret_cast< QString*>(_v) = getTitle(); break;
        case 2: *reinterpret_cast< QString*>(_v) = getAuthLogin(); break;
        case 3: *reinterpret_cast< QString*>(_v) = getSecretCode(); break;
        case 4: *reinterpret_cast< int*>(_v) = getKeyLenght(); break;
        case 5: *reinterpret_cast< int*>(_v) = getAuthType(); break;
        case 6: *reinterpret_cast< int*>(_v) = getCounter(); break;
        case 7: *reinterpret_cast< QString*>(_v) = getPublishDate(); break;
        case 8: *reinterpret_cast< QString*>(_v) = getEditDate(); break;
        }
        _id -= 9;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setId(*reinterpret_cast< int*>(_v)); break;
        case 1: setTitle(*reinterpret_cast< QString*>(_v)); break;
        case 2: setAuthLogin(*reinterpret_cast< QString*>(_v)); break;
        case 3: setSecretCode(*reinterpret_cast< QString*>(_v)); break;
        case 4: setKeyLenght(*reinterpret_cast< int*>(_v)); break;
        case 5: setAuthType(*reinterpret_cast< int*>(_v)); break;
        case 6: setCounter(*reinterpret_cast< int*>(_v)); break;
        case 7: setPublishDate(*reinterpret_cast< QString*>(_v)); break;
        case 8: setEditDate(*reinterpret_cast< QString*>(_v)); break;
        }
        _id -= 9;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 9;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void Database::idValueChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Database::titleValueChanged(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Database::authLoginValueChanged(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Database::secretCodeValueChanged(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Database::keyLenghtValueChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void Database::authTypeValueChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void Database::counterValueChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void Database::publishDateValueChanged(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void Database::editDateValueChanged(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}
QT_END_MOC_NAMESPACE
