//===============================================
#include "GUser.h"
#include "GCode.h"
#include "GSocket.h"
#include "GLog.h"
//===============================================
GUser::GUser(QObject* _parent)
: GModule(_parent) {
    m_id = 0;
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
    lDom.addData(_code, "id", m_id);
    lDom.addData(_code, "pseudo", m_pseudo);
    lDom.addData(_code, "password", m_password);
    return lDom.toStringData();
}
//===============================================
void GUser::deserialize(const QString& _data, const QString& _code) {
    GModule::deserialize(_data);
    GCode lDom;
    lDom.loadXml(_data);
    m_id = lDom.getItem(_code, "id").toInt();
    m_pseudo = lDom.getItem(_code, "pseudo");
    m_password = lDom.getItem(_code, "password");
}
//===============================================
void GUser::setId(int _id) {
    m_id = _id;
}
//===============================================
void GUser::setPseudo(const QString& _pseudo) {
    m_pseudo = _pseudo;
}
//===============================================
void GUser::setPassword(const QString& _password) {
    m_password = _password;
}
//===============================================
int GUser::getId() const {
    return m_id;
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
bool GUser::createAccount() {
    if(GLOGI->hasErrors()) return false;
    GSocket lClient;
    QString lData = serialize();
    lData = lClient.callServer("user", "create_account", lData);
    deserialize(lData);
    return !GLOGI->hasErrors();
}
//===============================================
