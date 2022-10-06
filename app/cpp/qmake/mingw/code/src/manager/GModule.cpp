//===============================================
#include "GModule.h"
#include "GLog.h"
#include "GSocket.h"
#include "GCode.h"
//===============================================
GModule::GModule()
: GObject() {
    m_server = 0;
}
//===============================================
GModule::~GModule() {

}
//===============================================
GObject* GModule::clone() const {
    return new GModule;
}
//===============================================
GString GModule::serialize(const GString& _code) const {
    GCode lDom;
    lDom.createDoc();
    lDom.addData(_code, "module", m_modules);
    lDom.addData(_code, "method", m_method);
    return lDom.toString();
}
//===============================================
bool GModule::deserialize(const GString& _data, const GString& _code) {
    GCode lDom;
    lDom.loadXml(_data);
    m_modules = lDom.getData(_code, "module");
    m_method = lDom.getData(_code, "method");
    return true;
}
//===============================================
void GModule::setClient(GSocket* _client) {
    m_server = _client;
}
//===============================================
void GModule::setModule(const GString& _modules) {
    m_modules = _modules;
}
//===============================================
void GModule::setMethod(const GString& _method) {
    m_method = _method;
}
//===============================================
