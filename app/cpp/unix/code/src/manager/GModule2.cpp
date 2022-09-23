//===============================================
#include "GModule2.h"
#include "GLog.h"
#include "GServer.h"
#include "GCode2.h"
#include "GConnection.h"
//===============================================
GModule2::GModule2()
: GObject2() {
    m_client = 0;
}
//===============================================
GModule2::~GModule2() {

}
//===============================================
GObject2* GModule2::clone() const {
    return new GModule2;
}
//===============================================
GString2 GModule2::serialize(const GString2& _code) const {
    GCode2 lDom;
    lDom.createDoc();
    lDom.addData(_code, "module", m_module);
    lDom.addData(_code, "method", m_method);
    return lDom.toString();
}
//===============================================
bool GModule2::deserialize(const GString2& _data, const GString2& _code) {
    GCode2 lDom;
    lDom.loadXml(_data);
    m_module = lDom.getData(_code, "module");
    m_method = lDom.getData(_code, "method");
    return true;
}
//===============================================
void GModule2::setClient(GServer* _client) {
    m_client = _client;
}
//===============================================
void GModule2::setModule(const GString2& _module) {
    m_module = _module;
}
//===============================================
void GModule2::setMethod(const GString2& _method) {
    m_method = _method;
}
//===============================================
bool GModule2::onModule() {
    deserialize(m_client->getRequest());
    if(m_module == "connection") {
        onConnection();
    }
    return true;
}
//===============================================
bool GModule2::onConnection() {
    GConnection lConnect;
    lConnect.setClient(m_client);
    lConnect.onModule();
    return true;
}
//===============================================
