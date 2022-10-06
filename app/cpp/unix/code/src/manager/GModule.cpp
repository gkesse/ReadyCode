//===============================================
#include "GModule.h"
#include "GCode.h"
#include "GFile.h"
#include "GLog.h"
#include "GServer.h"
#include "GConnection.h"
#include "GModules.h"
#include "GModulesData.h"
//===============================================
GModule::GModule()
: GObject() {
    m_server = 0;
}
//===============================================
GModule::GModule(const GModule& _modules)
: GObject() {
    setModule(_modules);
}
//===============================================
GModule::GModule(GModule* _modules)
: GObject() {
    setModule(_modules);
}
//===============================================
GModule::GModule(GServer* _server)
: GObject() {
    setServer(_server);
}
//===============================================
GModule::~GModule() {

}
//===============================================
GObject* GModule::clone() const {
    return new GModule;
}
//===============================================
void GModule::setModule(const GModule& _modules) {
    setServer(_modules.m_server);
}
//===============================================
void GModule::setModule(GModule* _modules) {
    setServer(_modules->m_server);
}
//===============================================
void GModule::setServer(GServer* _server) {
    m_server = _server;
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
void GModule::setModule(const GString& _modules) {
    m_modules = _modules;
}
//===============================================
void GModule::setMethod(const GString& _method) {
    m_method = _method;
}
//===============================================
bool GModule::onModule() {
    deserialize(m_server->getRequest());
    if(m_modules == "") {
        GMODULE_REQUIRED();
    }
    else if(m_modules == "connection") {
        onConnection();
    }
    else if(m_modules == "file") {
        onFile();
    }
    else if(m_modules == "modules") {
        onModules();
    }
    else if(m_modules == "modules_data") {
        onModulesData();
    }
    else {
        GMODULE_UNKNOWN();
    }
    return true;
}
//===============================================
bool GModule::onConnection() {
    GConnection lConnect;
    lConnect.setModule(this);
    lConnect.onModule();
    return true;
}
//===============================================
bool GModule::onFile() {
    GFile lFile;
    lFile.setModule(this);
    lFile.onModule();
    return true;
}
//===============================================
bool GModule::onModules() {
    GModules lModules;
    lModules.setModule(this);
    lModules.onModule();
    return true;
}
//===============================================
bool GModule::onModulesData() {
    GModulesData lModulesData;
    lModulesData.setModule(this);
    lModulesData.onModule();
    return true;
}
//===============================================
