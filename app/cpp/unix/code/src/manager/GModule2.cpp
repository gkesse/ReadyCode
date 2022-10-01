//===============================================
#include "GModule2.h"
#include "GLog.h"
#include "GServer.h"
#include "GCode2.h"
#include "GConnection.h"
//===============================================
GModule2::GModule2()
: GObject2() {
    m_server = 0;
}
//===============================================
GModule2::GModule2(const GModule2& _module)
: GObject2() {
    m_server = _module.m_server;
}
//===============================================
GModule2::GModule2(GModule2* _module)
: GObject2() {
    m_server = _module->m_server;
}
//===============================================
GModule2::GModule2(GServer* _server)
: GObject2() {
    m_server = _server;
}
//===============================================
GModule2::~GModule2() {

}
//===============================================
GObject2* GModule2::clone() const {
    return new GModule2;
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
        GERROR_ADD(eGERR, "Le module est obligatoire.");
    }
    else if(m_module == "connection") {
        onConnection();
    }
    else {
        GERROR_ADD(eGERR, "Le module (%s) est inconnu.", m_module.c_str());
    }
    return true;
}
//===============================================
bool GModule2::onConnection() {
    GConnection lConnect(this);
    lConnect.onModule();
    return true;
}
//===============================================
