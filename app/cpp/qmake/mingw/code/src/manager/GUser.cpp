//===============================================
#include "GUser.h"
#include "GCode.h"
#include "GSocket.h"
#include "GLog.h"
//===============================================
GUser::GUser(QObject* _parent)
: GModule(_parent) {
    m_pseudo = "";
    m_password = "";
}
//===============================================
GUser::~GUser() {

}
//===============================================
QString GUser::serialize(const QString& _code) const {
    GCode lDom;
    lDom.createDoc();
    lDom.addData(_code, "pseudo", m_pseudo);
    lDom.addData(_code, "password", m_password);
    return lDom.toStringData();
}
//===============================================
void GUser::deserialize(const QString& _data, const QString& _code) {
    GModule::deserialize(_data);
    GCode lDom;
    lDom.loadXml(_data);
    m_pseudo = lDom.getItem(_code, "pseudo");
    m_password = lDom.getItem(_code, "password");
}
//===============================================
QString GUser::getPseudo() const {
    return m_pseudo;
}
//===============================================
QString GUser::getPassword() const {
    return m_password;
}
//===============================================
bool GUser::runConnection() {
    if(GLOGI->hasErrors()) return false;
    GSocket lClient;
    QString lData = serialize();
    lData = lClient.callServer("user", "run_connection", lData);
    deserialize(lData);
    return !GLOGI->hasErrors();
}
//===============================================
