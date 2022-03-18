//===============================================
#include "GModule.h"
#include "GLog.h"
#include "GFormat.h"
#include "GCode.h"
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
void GModule::onModuleUnknown(GSocket* _client) {
    GLOG("Erreur le module (%s) n'existe pas",
            m_req->getModule().c_str());
}
//===============================================
void GModule::onMethodUnknown(GSocket* _client) {
    GLOG("Erreur la methode (%s : %s) n'existe pas",
            m_req->getModule().c_str(), m_req->getMethod().c_str());
}
//===============================================
void GModule::setRequest(const std::string& _req) {
    m_req.reset(new GCode);
    m_req->loadXmlData(_req);
    m_req->createXPath();
}
//===============================================
void GModule::sendResponse(GSocket* _client) {
    GSocket* lClient = _client;
    std::shared_ptr< GCode>& lRes = lClient->getResponse();

    if(GLOGI->hasError()) {
        QVector<std::string>& lErrors = GLOGI->getErrors();
        for(int i = 0; i < lErrors.size(); i++) {
            std::string lError = lErrors.at(i);
            lRes->createMap("error", "msg", lError);
        }
        GLOGI->clearErrors();
    }
    else {
        lRes->createCode("result", "msg", "ok");
    }

    lClient->writeData(lRes->toString());

    delete lClient;
}
//===============================================
