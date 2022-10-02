//===============================================
#include "GModule2.h"
#include "GLog.h"
#include "GSocket2.h"
#include "GCode2.h"
//===============================================
GModule2::GModule2()
: GObject() {
    m_server = 0;
}
//===============================================
GModule2::~GModule2() {

}
//===============================================
GObject* GModule2::clone() const {
    return new GModule2;
}
//===============================================
GString GModule2::serialize(const GString& _code) const {
    GCode2 lDom;
    lDom.createDoc();
    lDom.addData(_code, "module", m_module);
    lDom.addData(_code, "method", m_method);
    return lDom.toString();
}
//===============================================
bool GModule2::deserialize(const GString& _data, const GString& _code) {
    GCode2 lDom;
    lDom.loadXml(_data);
    m_module = lDom.getData(_code, "module");
    m_method = lDom.getData(_code, "method");
    return true;
}
//===============================================
void GModule2::setClient(GSocket2* _client) {
    m_server = _client;
}
//===============================================
void GModule2::setModule(const GString& _module) {
    m_module = _module;
}
//===============================================
void GModule2::setMethod(const GString& _method) {
    m_method = _method;
}
//===============================================
