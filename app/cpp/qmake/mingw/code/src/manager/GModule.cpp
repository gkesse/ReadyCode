//===============================================
#include "GModule.h"
#include "GLog.h"
#include "GXml.h"
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
    if(GLOGI->hasError()) return;
}
//===============================================
void GModule::onMethodUnknown(const QString& _req, GSocket* _client) {
    if(GLOGI->hasError()) return;
}
//===============================================
void GModule::setRequest(const QString& _req) {
    if(GLOGI->hasError()) return;
    m_req.reset(new GXml);
    m_req->loadXmlData(_req);
    m_req->createXPath();
}
//===============================================
QString GModule::getModule() {
    if(GLOGI->hasError()) return "";
    QString lData = m_req->getNodeValue("/rdv/module");
    return lData;
}
//===============================================
QString GModule::getMethod() {
    if(GLOGI->hasError()) return "";
    QString lData = m_req->getNodeValue("/rdv/method");
    return lData;
}
//===============================================
void GModule::sendResponse(GSocket* _client) {
    GSocket* lClient = _client;
    GXml lRes;
    lRes.createDoc("1.0", "rdv");
    lRes.createNodePath("/rdv/datas/data/code", "result");
    if(!GLOGI->hasError()) {
        lRes.createNodePath("/rdv/datas/data/msg", "ok");
    }
    else {
        lRes.createNodePath("/rdv/datas/data/msg", "error");
    }
    lClient->writeData(lRes.toString());
    delete lClient;
}
//===============================================
