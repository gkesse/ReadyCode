//================================================
#include "GDBusObject.h"
//================================================
GDBusObject::GDBusObject(QObject* parent) : 
QObject(parent) {

}
//================================================
GDBusObject::~GDBusObject() {

}
//================================================
QString GDBusObject::say_hello() {
    return QString("Bonjour tout le monde");
}
//================================================
int GDBusObject::add_data(const int& a, const int& b) {
    return (a + b);
}
//================================================
