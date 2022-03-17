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

}
//===============================================
void GModule::onMethodUnknown(const std::string& _req, GSocket* _client) {

}
//===============================================
void GModule::setRequest(const std::string& _req) {
    m_req.reset(new GXml);
    m_req->createXPath(_req);
}
//===============================================
std::string GModule::getModule() {
    std::string lData = m_req->getNodeValue("/rdv/module");
    return lData;
}
//===============================================
std::string GModule::getMethod() {
    std::string lData = m_req->getNodeValue("/rdv/method");
    return lData;
}
//===============================================
