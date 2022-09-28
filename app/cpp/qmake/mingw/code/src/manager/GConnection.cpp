//===============================================
#include "GConnection.h"
#include "GCode2.h"
#include "GClient.h"
#include "GLog2.h"
//===============================================
GConnection::GConnection()
: GModule2() {
    m_id = 0;
    m_pseudo = "";
    m_password = "";
    m_isConnect = false;
}
//===============================================
GConnection::~GConnection() {

}
//===============================================
GString GConnection::serialize(const GString& _code) const {
    GCode2 lDom;
    lDom.createDoc();
    lDom.addData(_code, "id", m_id);
    lDom.addData(_code, "pseudo", m_pseudo);
    lDom.addData(_code, "password", m_password);
    lDom.addData(_code, "is_connect", m_isConnect);
    return lDom.toString();
}
//===============================================
bool GConnection::deserialize(const GString& _data, const GString& _code) {
    GModule2::deserialize(_data);
    GCode2 lDom;
    lDom.loadXml(_data);
    m_id = lDom.getData(_code, "id").toInt();
    m_pseudo = lDom.getData(_code, "pseudo");
    m_password = lDom.getData(_code, "password");
    m_isConnect = lDom.getData(_code, "is_connect").toBool();
    return true;
}
//===============================================
void GConnection::setId(int _id) {
    m_id = _id;
}
//===============================================
void GConnection::setPseudo(const GString& _pseudo) {
    m_pseudo = _pseudo;
}
//===============================================
void GConnection::setPassword(const GString& _password) {
    m_password = _password;
}
//===============================================
int GConnection::getId() const {
    return m_id;
}
//===============================================
GString GConnection::getPseudo() const {
    return m_pseudo;
}
//===============================================
GString GConnection::getPassword() const {
    return m_password;
}
//===============================================
bool GConnection::runConnection() {
    if(GLOGI2->hasErrors()) return false;
    GString lData = serialize();
    lData = GSERVER_CALL("connection", "run_connection", lData);
    deserialize(lData);
    return !GLOGI2->hasErrors();
}
//===============================================
bool GConnection::createAccount() {
    if(GLOGI2->hasErrors()) return false;
    GString lData = serialize();
    lData = GCLIENTI->callServer("connection", "create_account", lData);
    deserialize(lData);
    return !GLOGI2->hasErrors();
}
//===============================================
bool GConnection::runDisconnection() {
    if(GLOGI2->hasErrors()) return false;
    GString lData = serialize();
    lData = GCLIENTI->callServer("connection", "run_disconnection", lData);
    deserialize(lData);
    return !GLOGI2->hasErrors();
}
//===============================================
bool GConnection::isConnect() const {
    return m_isConnect;
}
//===============================================
