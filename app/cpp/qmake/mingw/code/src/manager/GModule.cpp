//===============================================
#include "GModule.h"
#include "GLog.h"
#include "GCode.h"
#include "GSocket.h"
//===============================================
GModule::GModule(QObject* _parent)
: GSession(_parent) {
    m_module = "";
    m_method = "";
}
//===============================================
GModule::~GModule() {

}
//===============================================
QString GModule::serialize(const QString& _code) const {
    GCode lDom;
    lDom.createDoc();
    lDom.addData(_code, "module", m_module);
    lDom.addData(_code, "method", m_method);
    return lDom.toStringCode(_code);
}
//===============================================
void GModule::deserialize(const QString& _data, const QString& _code) {
    GSession::deserialize(_data);
    GCode lDom;
    lDom.loadXml(_data);
    m_module = lDom.getItem(_code, "module");
    m_method = lDom.getItem(_code, "method");
}
//===============================================
QString GModule::getModule() const {
    return m_module;
}
//===============================================
QString GModule::getMethod() const {
    return m_method;
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
