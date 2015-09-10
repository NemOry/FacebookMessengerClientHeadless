/****************************************************************************
** Meta object code from reading C++ file 'Utilities.hpp'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/Utilities/Utilities.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Utilities.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Utilities[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      21,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: signature, parameters, type, tag, flags
      19,   10,   11,   10, 0x02,
      33,   10,   11,   10, 0x02,
      44,   10,   11,   10, 0x02,
      56,   10,   11,   10, 0x02,
      77,   10,   11,   10, 0x02,
     100,   92,   10,   10, 0x02,
     138,   92,   10,   10, 0x02,
     187,  165,   11,   10, 0x02,
     214,   10,   10,   10, 0x02,
     236,   10,   10,   10, 0x02,
     272,   10,  265,   10, 0x02,
     301,  289,  265,   10, 0x02,
     341,  331,  326,   10, 0x02,
     381,  367,   10,   10, 0x02,
     427,  413,   10,   10, 0x02,
     473,  463,   11,   10, 0x02,
     521,  503,   11,   10, 0x02,
     560,  550,   10,   10, 0x02,
     589,  463,   10,   10, 0x02,
     617,  610,   10,   10, 0x02,
     638,  610,   10,   10, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_Utilities[] = {
    "Utilities\0\0QString\0author_name()\0"
    "app_name()\0fb_app_id()\0headless_target_id()\0"
    "ui_target_id()\0from,to\0"
    "copy_and_remove_file(QString,QString)\0"
    "copy_file(QString,QString)\0"
    "text,expression,index\0regex(QString,QString,int)\0"
    "clear_notifications()\0"
    "clear_notification_effects()\0qint64\0"
    "get_cache_size()\0folder_path\0"
    "get_folder_size(QString)\0bool\0text,find\0"
    "contains(QString,QString)\0title,message\0"
    "notify_regular(QString,QString)\0"
    "log,file_name\0set_string_to_file(QString,QString)\0"
    "file_name\0get_string_from_file(QString)\0"
    "key,default_value\0get_setting(QString,QString)\0"
    "key,value\0set_setting(QString,QString)\0"
    "delete_file(QString)\0folder\0"
    "wipe_folder(QString)\0wipe_folder_contents(QString)\0"
};

void Utilities::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Utilities *_t = static_cast<Utilities *>(_o);
        switch (_id) {
        case 0: { QString _r = _t->author_name();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 1: { QString _r = _t->app_name();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 2: { QString _r = _t->fb_app_id();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 3: { QString _r = _t->headless_target_id();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 4: { QString _r = _t->ui_target_id();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 5: _t->copy_and_remove_file((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 6: _t->copy_file((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 7: { QString _r = _t->regex((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 8: _t->clear_notifications(); break;
        case 9: _t->clear_notification_effects(); break;
        case 10: { qint64 _r = _t->get_cache_size();
            if (_a[0]) *reinterpret_cast< qint64*>(_a[0]) = _r; }  break;
        case 11: { qint64 _r = _t->get_folder_size((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< qint64*>(_a[0]) = _r; }  break;
        case 12: { bool _r = _t->contains((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 13: _t->notify_regular((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 14: _t->set_string_to_file((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 15: { QString _r = _t->get_string_from_file((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 16: { QString _r = _t->get_setting((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 17: _t->set_setting((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 18: _t->delete_file((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 19: _t->wipe_folder((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 20: _t->wipe_folder_contents((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Utilities::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Utilities::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Utilities,
      qt_meta_data_Utilities, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Utilities::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Utilities::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Utilities::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Utilities))
        return static_cast<void*>(const_cast< Utilities*>(this));
    return QObject::qt_metacast(_clname);
}

int Utilities::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
