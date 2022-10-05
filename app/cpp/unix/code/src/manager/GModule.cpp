//===============================================
#include "GModule.h"
#include "GCode.h"
#include "GFile.h"
#include "GLog.h"
#include "GServer.h"
#include "GConnection.h"
#include "GModules.h"
//===============================================
GModule::GModule()
: GObject() {
    m_server = 0;
}
//===============================================
GModule::GModule(const GModule& _module)
: GObject() {
    setModule(_module);
}
//===============================================
GModule::GModule(GModule* _module)
: GObject() {
    setModule(_module);
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
void GModule::setModule(const GModule& _module) {
    setServer(_module.m_server);
}
//===============================================
void GModule::setModule(GModule* _module) {
    setServer(_module->m_server);
}
//===============================================
void GModule::setServer(GServer* _server) {
    m_server = _server;
}
//===============================================
GString GModule::serialize(const GString& _code) const {
    GCode lDom;
    lDom.createDoc();
    lDom.addData(_code, "module", m_module);
    lDom.addData(_code, "method", m_method);
    return lDom.toString();
}
//===============================================
bool GModule::deserialize(const GString& _data, const GString& _code) {
    GCode lDom;
    lDom.loadXml(_data);
    m_module = lDom.getData(_code, "module");
    m_method = lDom.getData(_code, "method");
    return true;
}
//===============================================
void GModule::setModule(const GString& _module) {
    m_module = _module;
}
//===============================================
void GModule::setMethod(const GString& _method) {
    m_method = _method;
}
//===============================================
bool GModule::onModule() {
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
    else if(m_module == "modules") {
        onModules();
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
