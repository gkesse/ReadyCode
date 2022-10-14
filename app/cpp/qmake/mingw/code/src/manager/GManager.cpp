//===============================================
#include "GManager.h"
#include "GLog.h"
#include "GSocket.h"
#include "GCode.h"
//===============================================
GManager::GManager(const GString& _code)
: GObject(_code) {
    m_server = 0;
}
//===============================================
GManager::~GManager() {

}
//===============================================
GObject* GManager::clone() const {
    return new GManager;
}
//===============================================
GString GManager::serialize(const GString& _code) const {
    GCode lDom;
    lDom.createDoc();
    lDom.addData(_code, "module", m_moduleName);
    lDom.addData(_code, "method", m_methodName);
    return lDom.toString();
}
//===============================================
bool GManager::deserialize(const GString& _data, const GString& _code) {
    GCode lDom;
    lDom.loadXml(_data);
    m_moduleName = lDom.getData(_code, "module");
    m_methodName = lDom.getData(_code, "method");
    return true;
}
//===============================================
void GManager::setClient(GSocket* _client) {
    m_server = _client;
}
//===============================================
void GManager::setModule(const GString& _module) {
    m_moduleName = _module;
}
//===============================================
void GManager::setMethod(const GString& _method) {
    m_methodName = _method;
}
//===============================================
