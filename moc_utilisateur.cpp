/****************************************************************************
** Meta object code from reading C++ file 'utilisateur.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "utilisateur.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'utilisateur.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Utilisateur[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x08,
      38,   12,   12,   12, 0x08,
      69,   12,   12,   12, 0x08,
      99,   12,   12,   12, 0x08,
     127,   12,   12,   12, 0x08,
     157,   12,   12,   12, 0x08,
     185,   12,   12,   12, 0x08,
     208,   12,   12,   12, 0x08,
     231,   12,   12,   12, 0x08,
     254,   12,   12,   12, 0x08,
     277,   12,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Utilisateur[] = {
    "Utilisateur\0\0on_ButtonLogin_clicked()\0"
    "on_ButtonDeconnecter_clicked()\0"
    "on_ButtonRechercher_clicked()\0"
    "on_ButtonModifier_clicked()\0"
    "on_ButtonTransferer_clicked()\0"
    "on_ButtonTerminer_clicked()\0"
    "on_checkBox1_clicked()\0on_checkBox2_clicked()\0"
    "on_checkBox3_clicked()\0on_checkBox4_clicked()\0"
    "on_checkBox5_clicked()\0"
};

void Utilisateur::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Utilisateur *_t = static_cast<Utilisateur *>(_o);
        switch (_id) {
        case 0: _t->on_ButtonLogin_clicked(); break;
        case 1: _t->on_ButtonDeconnecter_clicked(); break;
        case 2: _t->on_ButtonRechercher_clicked(); break;
        case 3: _t->on_ButtonModifier_clicked(); break;
        case 4: _t->on_ButtonTransferer_clicked(); break;
        case 5: _t->on_ButtonTerminer_clicked(); break;
        case 6: _t->on_checkBox1_clicked(); break;
        case 7: _t->on_checkBox2_clicked(); break;
        case 8: _t->on_checkBox3_clicked(); break;
        case 9: _t->on_checkBox4_clicked(); break;
        case 10: _t->on_checkBox5_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData Utilisateur::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Utilisateur::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Utilisateur,
      qt_meta_data_Utilisateur, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Utilisateur::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Utilisateur::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Utilisateur::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Utilisateur))
        return static_cast<void*>(const_cast< Utilisateur*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Utilisateur::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
