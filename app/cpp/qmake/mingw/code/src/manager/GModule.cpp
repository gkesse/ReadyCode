//===============================================
#include "GModule.h"
#include "GLog.h"
#include "GRequest.h"
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
    m_req.reset(new GRequest);
    m_req->loadXmlData(_req);
    m_req->createXPath();
    m_res.reset(new GCode);
    m_res->createCode();
}
//===============================================
void GModule::sendResponse(GSocket* _client) {
    GSocket* lClient = _client;
    if(!GLOGI->hasError()) {
        m_res->createCode("result", "msg", "ok");
    }
    else {
        QVector<QString>& lErrors = GLOGI->getErrors();
        for(int i = 0; i < lErrors.size(); i++) {
            QString lError = lErrors.at(i);
            m_res->createMap("error", "map", "msg", lError);
        }
        GLOGI->clearErrors();
    }
    lClient->writeData(m_res->toString());
    delete lClient;
}
//===============================================
