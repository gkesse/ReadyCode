//===============================================
#include "GModule.h"
#include "GLog.h"
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
GString GModule::serialize(const GString& _code) const {
    GCode lReq;
    lReq.createDoc();
    lReq.addData(_code, "module", m_module);
    lReq.addData(_code, "method", m_method);
    return lReq.toStringCode(_code);
}
//===============================================
void GModule::deserialize(const GString& _data, const GString& _code) {
    GSession::deserialize(_data);
    GCode lReq;
    lReq.loadXml(_data);
    m_module = lReq.getItem(_code, "module");
    m_method = lReq.getItem(_code, "method");
}
//===============================================
void GModule::onModuleNone(GSocket* _client) {
    GERROR_ADD(eGERR, "Le module est obligatoire.");
}
//===============================================
void GModule::onMethodNone(GSocket* _client) {
    GERROR_ADD(eGERR, "La methode est obligatoire.");
}
//===============================================
void GModule::onModuleUnknown(GSocket* _client) {
    GERROR_ADD(eGERR, "Le module n'existe pas.");
}
//===============================================
void GModule::onMethodUnknown(GSocket* _client) {
    GERROR_ADD(eGERR, "La methode n'existe pas.");
}
//===============================================
