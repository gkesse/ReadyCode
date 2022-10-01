//===============================================
#include "GModule2.h"
#include "GLog.h"
#include "GServer.h"
#include "GCode2.h"
#include "GConnection.h"
#include "GFile3.h"
//===============================================
GModule2::GModule2()
: GObject2() {
    m_server = 0;
}
//===============================================
GModule2::GModule2(const GModule2& _module)
: GObject2() {
    assign(_module);
}
//===============================================
GModule2::GModule2(GModule2* _module)
: GObject2() {
    assign(_module);
}
//===============================================
GModule2::GModule2(GServer* _server)
: GObject2() {
    assign(_server);
}
//===============================================
GModule2::~GModule2() {

}
//===============================================
GObject2* GModule2::clone() const {
    return new GModule2;
}
//===============================================
void GModule2::assign(const GModule2& _module) {
    assign(_module.m_server);
}
//===============================================
void GModule2::assign(GModule2* _module) {
    assign(_module->m_server);
}
//===============================================
void GModule2::assign(GServer* _server) {
    m_server = _server;
}
//===============================================
GString GModule2::serialize(const GString& _code) const {
    GCode2 lDom;
    lDom.createDoc();
    lDom.addData(_code, "module", m_module);
    lDom.addData(_code, "method", m_method);
    return lDom.toString();
}
//===============================================
bool GModule2::deserialize(const GString& _data, const GString& _code) {
    GCode2 lDom;
    lDom.loadXml(_data);
    m_module = lDom.getData(_code, "module");
    m_method = lDom.getData(_code, "method");
    return true;
}
//===============================================
void GModule2::setModule(const GString& _module) {
    m_module = _module;
}
//===============================================
void GModule2::setMethod(const GString& _method) {
    m_method = _method;
}
//===============================================
bool GModule2::onModule() {
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
    else {
        GMODULE_UNKNOWN();
    }
    return true;
}
//===============================================
bool GModule2::onConnection() {
    GConnection lConnect;
    lConnect.assign(this);
    lConnect.onModule();
    return true;
}
//===============================================
bool GModule2::onFile() {
    GFile3 lFile;
    lFile.assign(this);
    lFile.onModule();
    return true;
}
//===============================================
