//===============================================
#include "GManager.h"
#include "GCode.h"
#include "GFile.h"
#include "GSocket.h"
#include "GConnection.h"
#include "GModule.h"
#include "GModuleData.h"
#include "GModuleKey.h"
#include "GModuleMap.h"
#include "GModuleType.h"
#include "GQuery.h"
#include "GQueryType.h"
#include "GPage.h"
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
void GManager::setManager(const GManager& _manager) {
    setServer(_manager.m_server);
}
//===============================================
void GManager::setManager(GManager* _manager) {
    setServer(_manager->m_server);
}
//===============================================
void GManager::setServer(GSocket* _socket) {
    m_server = _socket;
}
//===============================================
GString GManager::serialize(const GString& _code)  {
    GCode lDom;
    lDom.createDoc();
    lDom.addData(_code, "module", m_moduleName);
    lDom.addData(_code, "method", m_methodName);
    return lDom.toString();
}
//===============================================
void GManager::deserialize(const GString& _data, const GString& _code) {
    GCode lDom;
    lDom.loadXml(_data);
    m_moduleName = lDom.getData(_code, "module");
    m_methodName = lDom.getData(_code, "method");
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
bool GManager::isValid() const {
    if(m_methodName.isEmpty()) return false;
    if(m_moduleName.isEmpty()) return false;
    return !m_logs.hasErrors();
}
//===============================================
bool GManager::run(const GString& _request) {
    deserialize(_request);
    if(m_moduleName == "") {
        m_logs.addError("Le module est obligatoire.");
    }
    else if(m_moduleName == "page") {
        onPage(_request);
    }
    else {
        m_logs.addError("Le module est inconnu.");
    }
    return !m_logs.hasErrors();
}
//===============================================
bool GManager::onPage(const GString& _request) {
    GPage lObj;
    lObj.run(_request);
    m_logs.addLogs(lObj.getLogs());
    m_responseXml.loadData(lObj.serialize());
    return !m_logs.hasErrors();
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
    else if(m_moduleName == "module_key") {
        onModuleKey();
    }
    else if(m_moduleName == "module_map") {
        onModuleMap();
    }
    else if(m_moduleName == "module_type") {
        onModuleType();
    }
    else if(m_moduleName == "query") {
        onQuery();
    }
    else if(m_moduleName == "query_type") {
        onQueryType();
    }
    else {
        GMODULE_UNKNOWN();
    }
    return true;
}
//===============================================
bool GManager::onConnection() {
    GConnection lObj;
    lObj.setManager(this);
    lObj.onModule();
    return true;
}
//===============================================
bool GManager::onFile() {
    GFile lObj;
    lObj.setManager(this);
    lObj.onModule();
    return true;
}
//===============================================
bool GManager::onModule() {
    GModule lObj;
    lObj.setManager(this);
    lObj.onModule();
    return true;
}
//===============================================
bool GManager::onModuleData() {
    GModuleData lObj;
    lObj.setManager(this);
    lObj.onModule();
    return true;
}
//===============================================
bool GManager::onModuleKey() {
    GModuleKey lObj;
    lObj.setManager(this);
    lObj.onModule();
    return true;
}
//===============================================
bool GManager::onModuleMap() {
    GModuleMap lObj;
    lObj.setManager(this);
    lObj.onModule();
    return true;
}
//===============================================
bool GManager::onModuleType() {
    GModuleType lObj;
    lObj.setManager(this);
    lObj.onModule();
    return true;
}
//===============================================
bool GManager::onQuery() {
    GQuery lObj;
    lObj.setManager(this);
    lObj.onModule();
    return true;
}
//===============================================
bool GManager::onQueryType() {
    GQueryType lObj;
    lObj.setManager(this);
    lObj.onModule();
    return true;
}
//===============================================
