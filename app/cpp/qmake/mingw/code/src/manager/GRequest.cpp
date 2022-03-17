//===============================================
#include "GRequest.h"
#include "GLog.h"
//===============================================
GRequest::GRequest(QObject* _parent) : GCode(_parent) {

}
//===============================================
GRequest::GRequest(const QString& _code, QObject* _parent) : GCode(_code, _parent) {

}
//===============================================
GRequest::~GRequest() {

}
//===============================================
GRequest& GRequest::createRequest(const QString& _module, const QString& _method) {
    createDoc("1.0", "rdv");
    createNodePath("/rdv/module", _module);
    createNodePath("/rdv/method", _method);
    return *this;
}
//===============================================
QString GRequest::getModule() {
    QString lData = getNodeValue("/rdv/module");
    return lData;
}
//===============================================
QString GRequest::getMethod() {
    QString lData = getNodeValue("/rdv/method");
    return lData;
}
//===============================================
