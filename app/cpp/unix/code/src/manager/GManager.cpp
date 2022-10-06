//===============================================
#include "GManager.h"
#include "GCode.h"
#include "GFile.h"
#include "GLog.h"
#include "GServer.h"
#include "GConnection.h"
#include "GModule.h"
#include "GModuleData.h"
//===============================================
GManager::GManager()
: GObject() {
    m_server = 0;
}
//===============================================
GManager::GManager(const GManager& _modules)
: GObject() {
    setModule(_modules);
}
//===============================================
GManager::GManager(GManager* _modules)
: GObject() {
    setModule(_modules);
}
//===============================================
GManager::GManager(GServer* _server)
: GObject() {
    setServer(_server);
}
//===============================================
GManager::~GManager() {

}
//===============================================
GObject* GManager::clone() const {
    return new GManager;
}
//===============================================
void GManager::setModule(const GManager& _modules) {
    setServer(_modules.m_server);
}
//===============================================
void GManager::setModule(GManager* _modules) {
    setServer(_modules->m_server);
}
//===============================================
void GManager::setServer(GServer* _server) {
    m_server = _server;
}
//===============================================
GString GManager::serialize(const GString& _code) const {
    GCode lDom;
    lDom.createDoc();
    lDom.addData(_code, "module", m_module);
    lDom.addData(_code, "method", m_method);
    return lDom.toString();
}
//===============================================
bool GManager::deserialize(const GString& _data, const GString& _code) {
    GCode lDom;
    lDom.loadXml(_data);
    m_module = lDom.getData(_code, "module");
    m_method = lDom.getData(_code, "method");
    return true;
}
//===============================================
void GManager::setModule(const GString& _modules) {
    m_module = _modules;
}
//===============================================
void GManager::setMethod(const GString& _method) {
    m_method = _method;
}
//===============================================
bool GManager::onModule() {
    deserialize(m_server->getRequest());
    if(m_module == "") {
        GMODULE_REQUIRED();
    }
    else if(m_module == "connection") {
        onConnection();
    }
    else if(m_module == "file") {
        onFile();
    }
    else if(m_module == "module") {
        onModules();
    }
    else if(m_module == "modules_data") {
        onModulesData();
    }
    else {
        GMODULE_UNKNOWN();
    }
    return true;
}
//===============================================
bool GManager::onConnection() {
    GConnection lConnect;
    lConnect.setModule(this);
    lConnect.onModule();
    return true;
}
//===============================================
bool GManager::onFile() {
    GFile lFile;
    lFile.setModule(this);
    lFile.onModule();
    return true;
}
//===============================================
bool GManager::onModules() {
    GModule lModules;
    lModules.setModule(this);
    lModules.onModule();
    return true;
}
//===============================================
bool GManager::onModulesData() {
    GModuleData lModulesData;
    lModulesData.setModule(this);
    lModulesData.onModule();
    return true;
}
//===============================================
