//===============================================
#include "GModule.h"
#include "GLog.h"
#include "GFormat.h"
#include "GCode.h"
#include "GSocket.h"
#include "GXml.h"
//===============================================
GModule::GModule() : GSession() {
    m_module = "";
    m_method = "";
}
//===============================================
GModule::~GModule() {

}
//===============================================
std::string GModule::serialize(const std::string& _code) const {
    GCode lReq;
    lReq.createDoc();
    lReq.addData(_code, "module", m_module);
    lReq.addData(_code, "method", m_method);
    return lReq.toStringCode(_code);
}
//===============================================
void GModule::deserialize(const std::string& _data, const std::string& _code) {
    GSession::deserialize(_data);
    GCode lReq;
    lReq.loadXml(_data);
    m_module = lReq.getItem(_code, "module");
    m_method = lReq.getItem(_code, "method");
}
//===============================================
void GModule::onModuleNone(GSocket* _client) {
    GERROR(eGERR, "Le module est obligatoire.");
}
//===============================================
void GModule::onMethodNone(GSocket* _client) {
    GERROR(eGERR, "La methode est obligatoire.");
}
//===============================================
void GModule::onModuleUnknown(GSocket* _client) {
    GERROR(eGERR, "Le module n'existe pas.");
}
//===============================================
void GModule::onMethodUnknown(GSocket* _client) {
    GERROR(eGERR, "La methode n'existe pas.");
}
//===============================================
