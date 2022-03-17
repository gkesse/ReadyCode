//===============================================
#include "GModule.h"
#include "GLog.h"
#include "GCode.h"
#include "GSocket.h"
//===============================================
GModule::GModule(QObject* _parent) : GObject(_parent) {

}
//===============================================
GModule::GModule(const QString& _req, QObject* _parent) : GObject(_parent) {
    setRequest(_req);
}
//===============================================
GModule::~GModule() {

}
//===============================================
void GModule::onModuleUnknown(const QString& _req, GSocket* _client) {
    GLOG(QString("Erreur le module (%1) n'existe pas").arg(m_req->getModule()));
}
//===============================================
void GModule::onMethodUnknown(const QString& _req, GSocket* _client) {
    GLOG(QString("Erreur la methode (%1 : %2) n'existe pas").arg(m_req->getModule()).arg(m_req->getMethod()));
}
//===============================================
void GModule::setRequest(const QString& _req) {
    m_req.reset(new GCode);
    m_req->loadXmlData(_req);
    m_req->createXPath();
}
//===============================================
void GModule::sendResponse(GSocket* _client) {
    GSocket* lClient = _client;
    QSharedPointer<GCode>& lRes = lClient->getResponse();

    if(GLOGI->hasError()) {
        QVector<QString>& lErrors = GLOGI->getErrors();
        for(int i = 0; i < lErrors.size(); i++) {
            QString lError = lErrors.at(i);
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
