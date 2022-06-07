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
    lReq.createCode(_code, "module", m_module);
    lReq.createCode(_code, "method", m_method);
    return lReq.toStringCode(_code);
}
//===============================================
void GModule::deserialize(const std::string& _data, const std::string& _code) {
    GSession::deserialize(_data);
    GCode lReq(_data);
    m_module = lReq.getItem(_code, "module");
    m_method = lReq.getItem(_code, "method");
}
//===============================================
void GModule::onXmlInvalid(GSocket* _client) {
    GERROR(eGERR, "Erreur le format XML est invalide.",
            m_module.c_str());
}
//===============================================
void GModule::onReqInvalid(GSocket* _client) {
    GERROR(eGERR, "Erreur le format de la requete est invalide.",
            m_module.c_str());
}
//===============================================
void GModule::onModuleUnknown(GSocket* _client) {
    GERROR(eGERR, "Erreur le module (%s) n'existe pas.",
            m_module.c_str());
}
//===============================================
void GModule::onMethodUnknown(GSocket* _client) {
    GERROR(eGERR, "Erreur la methode (%s : %s) n'existe pas.",
            m_module.c_str(), m_method.c_str());
}
//===============================================
void GModule::sendResponse(GSocket* _client) {
    GSocket* lClient = _client;
    std::shared_ptr<GCode>& lRes = lClient->getResponse();

    if(GLOGI->hasErrors()) {
        std::vector<std::string>& lErrors = GLOGI->getErrors();
        for(int i = 0; i < lErrors.size(); i++) {
            std::string lError = lErrors.at(i);
            lRes->createMap("error", lError, i);
        }
        GLOGI->clearErrors();
    }
    else if(!lRes->hasCode()) {
        lRes->createCode("result", "msg", "ok");
    }
}
//===============================================
