//===============================================
#include "GModule.h"
#include "GLog.h"
#include "GXml.h"
#include "GSocket.h"
//===============================================
GModule::GModule() : GObject() {

}
//===============================================
GModule::GModule(const std::string& _req) : GObject() {
    setRequest(_req);
}
//===============================================
GModule::~GModule() {

}
//===============================================
void GModule::onModuleUnknown(const std::string& _req, GSocket* _client) {
    if(GLOGI->hasError()) return;
}
//===============================================
void GModule::onMethodUnknown(const std::string& _req, GSocket* _client) {
    if(GLOGI->hasError()) return;
}
//===============================================
void GModule::setRequest(const std::string& _req) {
    if(GLOGI->hasError()) return;
    m_req.reset(new GXml);
    m_req->createXPath(_req);
}
//===============================================
std::string GModule::getModule() {
    if(GLOGI->hasError()) return "";
    std::string lData = m_req->getNodeValue("/rdv/module");
    return lData;
}
//===============================================
std::string GModule::getMethod() {
    if(GLOGI->hasError()) return "";
    std::string lData = m_req->getNodeValue("/rdv/method");
    return lData;
}
//===============================================
