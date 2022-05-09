//===============================================
#include "GModule.h"
#include "GLog.h"
#include "GCode.h"
#include "GSocket.h"
//===============================================
GModule::GModule(QObject* _parent) : GObject(_parent) {

}
//===============================================
GModule::~GModule() {

}
//===============================================
void GModule::onModuleUnknown(GSocket* _client) {
    QSharedPointer<GCode>& lReq = _client->getReq();
    GERROR(eGERR, QString("Erreur le module (%1) n'existe pas")
            .arg(lReq->getModule()));
}
//===============================================
void GModule::onMethodUnknown(GSocket* _client) {
    QSharedPointer<GCode>& lReq = _client->getReq();
    GERROR(eGERR, QString("Erreur la methode (%1 : %2) n'existe pas")
            .arg(lReq->getModule()).arg(lReq->getMethod()));
}
//===============================================
void GModule::sendResponse(GSocket* _client) {
    GSocket* lClient = _client;
    QSharedPointer<GCode>& lRes = lClient->getResponse();

    if(GLOGI->hasErrors()) {
        QVector<QString>& lErrors = GLOGI->getErrors();
        for(int i = 0; i < lErrors.size(); i++) {
            QString lError = lErrors.at(i);
            lRes->createMap("error", "msg", lError, i);
        }
        GLOGI->clearErrors();
    }
    else {
        lRes->createCode("result", "msg", "ok");
    }

    lClient->writePack(lRes->toString());

    delete lClient;
}
//===============================================
