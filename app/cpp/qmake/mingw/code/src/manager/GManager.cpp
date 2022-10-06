//===============================================
#include "GManager.h"
#include "GLog.h"
#include "GSocket.h"
#include "GCode.h"
//===============================================
GManager::GManager()
: GObject() {
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
    lDom.addData(_code, "module", m_modules);
    lDom.addData(_code, "method", m_method);
    return lDom.toString();
}
//===============================================
bool GManager::deserialize(const GString& _data, const GString& _code) {
    GCode lDom;
    lDom.loadXml(_data);
    m_modules = lDom.getData(_code, "module");
    m_method = lDom.getData(_code, "method");
    return true;
}
//===============================================
void GManager::setClient(GSocket* _client) {
    m_server = _client;
}
//===============================================
void GManager::setModule(const GString& _modules) {
    m_modules = _modules;
}
//===============================================
void GManager::setMethod(const GString& _method) {
    m_method = _method;
}
//===============================================
