//===============================================
#include "GObject.h"
#include "GSocketUi.h"
#include "GXmlUi.h"
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
    if(_key == "socket") return new GSocketUi(_parent);
    if(_key == "xml") return new GXmlUi(_parent);
    return new GObject(_parent);
}
//===============================================
void GObject::onEvent() {}
//===============================================
