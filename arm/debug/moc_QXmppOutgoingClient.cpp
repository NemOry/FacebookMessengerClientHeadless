/****************************************************************************
** Meta object code from reading C++ file 'QXmppOutgoingClient.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/qxmpp/client/QXmppOutgoingClient.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QXmppOutgoingClient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QXmppOutgoingClient[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      11,       // signalCount

 // signals: signature, parameters, type, tag, flags
      21,   20,   20,   20, 0x05,
      63,   47,   20,   20, 0x05,
      98,   20,   20,   20, 0x05,
     130,   20,   20,   20, 0x05,
     160,   20,   20,   20, 0x05,
     182,  180,   20,   20, 0x05,
     221,  180,   20,   20, 0x05,
     262,  180,   20,   20, 0x05,
     291,   20,   20,   20, 0x05,
     358,  344,   20,   20, 0x05,
     396,  388,   20,   20, 0x05,

 // slots: signature, parameters, type, tag, flags
     426,   20,   20,   20, 0x08,
     449,   20,   20,   20, 0x08,
     473,   20,   20,   20, 0x08,
     515,   20,   20,   20, 0x08,
     549,   20,   20,   20, 0x08,
     561,   20,   20,   20, 0x08,
     572,   20,   20,   20, 0x08,
     583,   20,   20,   20, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QXmppOutgoingClient[] = {
    "QXmppOutgoingClient\0\0error(QXmppClient::Error)\0"
    "element,handled\0elementReceived(QDomElement,bool&)\0"
    "presenceReceived(QXmppPresence)\0"
    "messageReceived(QXmppMessage)\0"
    "iqReceived(QXmppIq)\0,\0"
    "messageAcknowledged(QXmppMessage,bool)\0"
    "presenceAcknowledged(QXmppPresence,bool)\0"
    "iqAcknowledged(QXmppIq,bool)\0"
    "streamManagementError(QXmppStanza::Error::Condition)\0"
    "resumeEnabled\0streamManagementEnabled(bool)\0"
    "resumed\0streamManagementResumed(bool)\0"
    "_q_dnsLookupFinished()\0_q_socketDisconnected()\0"
    "socketError(QAbstractSocket::SocketError)\0"
    "socketSslErrors(QList<QSslError>)\0"
    "pingStart()\0pingStop()\0pingSend()\0"
    "pingTimeout()\0"
};

void QXmppOutgoingClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QXmppOutgoingClient *_t = static_cast<QXmppOutgoingClient *>(_o);
        switch (_id) {
        case 0: _t->error((*reinterpret_cast< QXmppClient::Error(*)>(_a[1]))); break;
        case 1: _t->elementReceived((*reinterpret_cast< const QDomElement(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 2: _t->presenceReceived((*reinterpret_cast< const QXmppPresence(*)>(_a[1]))); break;
        case 3: _t->messageReceived((*reinterpret_cast< const QXmppMessage(*)>(_a[1]))); break;
        case 4: _t->iqReceived((*reinterpret_cast< const QXmppIq(*)>(_a[1]))); break;
        case 5: _t->messageAcknowledged((*reinterpret_cast< const QXmppMessage(*)>(_a[1])),(*reinterpret_cast< const bool(*)>(_a[2]))); break;
        case 6: _t->presenceAcknowledged((*reinterpret_cast< const QXmppPresence(*)>(_a[1])),(*reinterpret_cast< const bool(*)>(_a[2]))); break;
        case 7: _t->iqAcknowledged((*reinterpret_cast< const QXmppIq(*)>(_a[1])),(*reinterpret_cast< const bool(*)>(_a[2]))); break;
        case 8: _t->streamManagementError((*reinterpret_cast< QXmppStanza::Error::Condition(*)>(_a[1]))); break;
        case 9: _t->streamManagementEnabled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->streamManagementResumed((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: _t->_q_dnsLookupFinished(); break;
        case 12: _t->_q_socketDisconnected(); break;
        case 13: _t->socketError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 14: _t->socketSslErrors((*reinterpret_cast< const QList<QSslError>(*)>(_a[1]))); break;
        case 15: _t->pingStart(); break;
        case 16: _t->pingStop(); break;
        case 17: _t->pingSend(); break;
        case 18: _t->pingTimeout(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QXmppOutgoingClient::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QXmppOutgoingClient::staticMetaObject = {
    { &QXmppStream::staticMetaObject, qt_meta_stringdata_QXmppOutgoingClient,
      qt_meta_data_QXmppOutgoingClient, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QXmppOutgoingClient::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QXmppOutgoingClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QXmppOutgoingClient::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QXmppOutgoingClient))
        return static_cast<void*>(const_cast< QXmppOutgoingClient*>(this));
    return QXmppStream::qt_metacast(_clname);
}

int QXmppOutgoingClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QXmppStream::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    }
    return _id;
}

// SIGNAL 0
void QXmppOutgoingClient::error(QXmppClient::Error _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QXmppOutgoingClient::elementReceived(const QDomElement & _t1, bool & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QXmppOutgoingClient::presenceReceived(const QXmppPresence & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QXmppOutgoingClient::messageReceived(const QXmppMessage & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void QXmppOutgoingClient::iqReceived(const QXmppIq & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void QXmppOutgoingClient::messageAcknowledged(const QXmppMessage & _t1, const bool _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void QXmppOutgoingClient::presenceAcknowledged(const QXmppPresence & _t1, const bool _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void QXmppOutgoingClient::iqAcknowledged(const QXmppIq & _t1, const bool _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void QXmppOutgoingClient::streamManagementError(QXmppStanza::Error::Condition _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void QXmppOutgoingClient::streamManagementEnabled(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void QXmppOutgoingClient::streamManagementResumed(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}
QT_END_MOC_NAMESPACE
