//===============================================
#include "GManager.h"
#include "GLog.h"
#include "GSocket.h"
#include "GCode.h"
//===============================================
GManager::GManager(const GString& _codeName)
: GObject(_codeName) {
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
GString GManager::serialize() const {
    GCode lDom;
    lDom.createDoc();
    lDom.addData(m_codeName, "module", m_moduleName);
    lDom.addData(m_codeName, "method", m_methodName);
    return lDom.toString();
}
//===============================================
bool GManager::deserialize(const GString& _data) {
    GCode lDom;
    lDom.loadXml(_data);
    m_moduleName = lDom.getData(m_codeName, "module");
    m_methodName = lDom.getData(m_codeName, "method");
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
