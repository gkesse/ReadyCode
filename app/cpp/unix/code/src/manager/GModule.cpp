//===============================================
#include "GModule.h"
#include "GLog.h"
#include "GFormat.h"
#include "GCode.h"
#include "GSocket.h"
#include "GXml.h"
//===============================================
GModule::GModule() : GObject() {
    m_xml = "";
}
//===============================================
GModule::GModule(const std::string& _req) : GObject() {
    m_xml = _req;
    loadReq();
}
//===============================================
GModule::~GModule() {

}
//===============================================
void GModule::onModuleUnknown(GSocket* _client) {
    GERROR(eGERR, "Erreur le module (%s) n'existe pas",
            m_req->getModule().c_str());
}
//===============================================
void GModule::onMethodUnknown(GSocket* _client) {
    GERROR(eGERR, "Erreur la methode (%s : %s) n'existe pas",
            m_req->getModule().c_str(), m_req->getMethod().c_str());
}
//===============================================
void GModule::loadReq() {
    if(m_xml == "") return;
    m_req.reset(new GCode(m_xml));
}
//===============================================
bool GModule::isValidReq() const {
    if(m_xml == "") return false;
    return m_req->isValidXml();
}
//===============================================
void GModule::sendResponse(GSocket* _client) {
    GSocket* lClient = _client;
    std::shared_ptr<GCode>& lRes = lClient->getResponse();

    if(GLOGI->hasErrors()) {
        std::vector<std::string>& lErrors = GLOGI->getErrors();
        for(int i = 0; i < lErrors.size(); i++) {
            std::string lError = lErrors.at(i);
            lRes->createMap("error", "msg", lError);
        }
        GLOGI->clearErrors();
    }
    else {
        lRes->createCode("result", "msg", "ok");
    }

    GLOGT(eGOFF, "%s", lRes->toString().c_str());

    lClient->writeData(lRes->toString());

    lClient->closeSocket();
    delete lClient;
}
//===============================================
