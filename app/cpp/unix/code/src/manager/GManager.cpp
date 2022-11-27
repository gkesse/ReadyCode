//===============================================
#include "GManager.h"
#include "GCode.h"
#include "GFile.h"
#include "GLog.h"
#include "GServer.h"
#include "GConnection.h"
#include "GModule.h"
#include "GModuleData.h"
#include "GModuleMap.h"
#include "GQuery.h"
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
void GManager::setModule(const GString& _module) {
    m_moduleName = _module;
}
//===============================================
void GManager::setMethod(const GString& _method) {
    m_methodName = _method;
}
//===============================================
bool GManager::onManager() {
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
        onModule();
    }
    else if(m_moduleName == "module_data") {
        onModuleData();
    }
    else if(m_moduleName == "module_map") {
        onModuleMap();
    }
    else if(m_moduleName == "query") {
        onQuery();
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
bool GManager::onModule() {
    GModule lModule;
    lModule.setManager(this);
    lModule.onModule();
    return true;
}
//===============================================
bool GManager::onModuleData() {
    GModuleData lModuleData;
    lModuleData.setManager(this);
    lModuleData.onModule();
    return true;
}
//===============================================
bool GManager::onModuleMap() {
    GModuleMap lModuleMap;
    lModuleMap.setManager(this);
    lModuleMap.onModule();
    return true;
}
//===============================================
bool GManager::onQuery() {
    GQuery lQuery;
    lQuery.setManager(this);
    lQuery.onModule();
    return true;
}
//===============================================
