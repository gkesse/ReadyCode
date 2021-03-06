//===============================================
#include "GModule.h"
#include "GLog.h"
#include "GFormat.h"
#include "GCode.h"
#include "GSocket.h"
#include "GXml.h"
//===============================================
GModule::GModule() : GObject() {

}
//===============================================
GModule::~GModule() {

}
//===============================================
void GModule::onXmlInvalid(GSocket* _client) {
    GERROR(eGERR, "Erreur le format XML est invalide.",
            _client->getReq()->getModule().c_str());
}
//===============================================
void GModule::onReqInvalid(GSocket* _client) {
    GERROR(eGERR, "Erreur le format de la requete est invalide.",
            _client->getReq()->getModule().c_str());
}
//===============================================
void GModule::onModuleUnknown(GSocket* _client) {
    GERROR(eGERR, "Erreur le module (%s) n'existe pas",
            _client->getReq()->getModule().c_str());
}
//===============================================
void GModule::onMethodUnknown(GSocket* _client) {
    GERROR(eGERR, "Erreur la methode (%s : %s) n'existe pas",
            _client->getReq()->getModule().c_str(), _client->getReq()->getMethod().c_str());
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

    lClient->writeData(lRes->toString());

    GLOGT(eGMSG, "[EMISSION]...: (%d)\n(%s)\n", (int)lRes->toString().size(), lRes->toString().c_str());

    lClient->closeSocket();
    delete lClient;
}
//===============================================
