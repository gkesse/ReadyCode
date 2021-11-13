//===============================================
#include "GObject.h"
#include "GSocket.h"
//===============================================
GObject::GObject(QObject* _parent) :
QObject(_parent) {

}
//===============================================
GObject::~GObject() {

}
//===============================================
GObject* GObject::Create(const QString& _key, QObject* _parent) {
    if(_key == "object") return new GObject(_parent);
    if(_key == "socket") return new GSocket(_parent);
    return new GObject(_parent);
}
//===============================================
void GObject::onEvent() {}
//===============================================
