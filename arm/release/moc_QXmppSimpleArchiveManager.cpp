/****************************************************************************
** Meta object code from reading C++ file 'QXmppSimpleArchiveManager.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/qxmpp/client/QXmppSimpleArchiveManager.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QXmppSimpleArchiveManager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QXmppSimpleArchiveManager[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      36,   27,   26,   26, 0x05,
     114,  109,   26,   26, 0x25,

       0        // eod
};

static const char qt_meta_stringdata_QXmppSimpleArchiveManager[] = {
    "QXmppSimpleArchiveManager\0\0jid,,rsm\0"
    "archiveMessagesReceived(QString,QList<QXmppMessage>,QXmppResultSetRepl"
    "y)\0"
    "jid,\0archiveMessagesReceived(QString,QList<QXmppMessage>)\0"
};

void QXmppSimpleArchiveManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QXmppSimpleArchiveManager *_t = static_cast<QXmppSimpleArchiveManager *>(_o);
        switch (_id) {
        case 0: _t->archiveMessagesReceived((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QList<QXmppMessage>(*)>(_a[2])),(*reinterpret_cast< const QXmppResultSetReply(*)>(_a[3]))); break;
        case 1: _t->archiveMessagesReceived((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QList<QXmppMessage>(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QXmppSimpleArchiveManager::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QXmppSimpleArchiveManager::staticMetaObject = {
    { &QXmppClientExtension::staticMetaObject, qt_meta_stringdata_QXmppSimpleArchiveManager,
      qt_meta_data_QXmppSimpleArchiveManager, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QXmppSimpleArchiveManager::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QXmppSimpleArchiveManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QXmppSimpleArchiveManager::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QXmppSimpleArchiveManager))
        return static_cast<void*>(const_cast< QXmppSimpleArchiveManager*>(this));
    return QXmppClientExtension::qt_metacast(_clname);
}

int QXmppSimpleArchiveManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QXmppClientExtension::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void QXmppSimpleArchiveManager::archiveMessagesReceived(const QString & _t1, const QList<QXmppMessage> & _t2, const QXmppResultSetReply & _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
