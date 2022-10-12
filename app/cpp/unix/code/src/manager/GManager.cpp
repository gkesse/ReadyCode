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
void GManager::setManager(const GManager& _manager) {
    setServer(_manager.m_server);
}
//===============================================
void GManager::setManager(GManager* _manager) {
    setServer(_manager->m_server);
}
//===============================================
void GManager::setServer(GServer* _server) {
    m_server = _server;
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
void GManager::setModule(const GString& _module) {
    m_moduleName = _module;
}
//===============================================
void GManager::setMethod(const GString& _method) {
    m_methodName = _method;
}
//===============================================
bool GManager::onModule() {
    deserialize(m_server->getRequest());
    if(m_moduleName == "") {
        GMODULE_REQUIRED();
    }
    else if(m_moduleName == "connection") {
        onConnection();
    }
    else if(m_moduleName == "file") {
        onFile();
    }
    else if(m_moduleName == "module") {
        onModules();
    }
    else if(m_moduleName == "module_data") {
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
    lConnect.setManager(this);
    lConnect.onModule();
    return true;
}
//===============================================
bool GManager::onFile() {
    GFile lFile;
    lFile.setManager(this);
    lFile.onModule();
    return true;
}
//===============================================
bool GManager::onModules() {
    GModule lModules;
    lModules.setManager(this);
    lModules.onModule();
    return true;
}
//===============================================
bool GManager::onModulesData() {
    GModuleData lModulesData;
    lModulesData.setManager(this);
    lModulesData.onModule();
    return true;
}
//===============================================
