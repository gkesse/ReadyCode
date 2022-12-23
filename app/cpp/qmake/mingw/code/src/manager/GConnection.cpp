//===============================================
#include "GConnection.h"
#include "GCode.h"
#include "GClient.h"
//===============================================
GConnection* GConnection::m_instance = 0;
//===============================================
GConnection::GConnection()
: GObject() {
    m_id = 0;
}
//===============================================
GConnection::~GConnection() {

}
//===============================================
GConnection* GConnection::Instance() {
    if(m_instance == 0) {
        m_instance = new GConnection;
    }
    return m_instance;
}
//===============================================
void GConnection::assign(const GConnection& _connect) {
    m_id = _connect.m_id;
    m_pseudo = _connect.m_pseudo;
    m_password = _connect.m_password;
}
//===============================================
GString GConnection::serialize() const {
    GCode lDom;
    lDom.createDoc();
    lDom.addData(m_codeName, "id", m_id);
    lDom.addData(m_codeName, "pseudo", m_pseudo);
    lDom.addData(m_codeName, "password", m_password);
    return lDom.toString();
}
//===============================================
bool GConnection::deserialize(const GString& _data) {
    GCode lDom;
    lDom.loadXml(_data);
    m_id = lDom.getData(m_codeName, "id").toInt();
    m_pseudo = lDom.getData(m_codeName, "pseudo");
    m_password = lDom.getData(m_codeName, "password");
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
bool GConnection::isConnect() const {
    return (m_id != 0);
}
//===============================================
void GConnection::runConnection() {
    GString lData = serialize();
    lData = GCALL_SERVER("connection", "run_connection", lData);
    deserialize(lData);
}
//===============================================
void GConnection::runDisconnection() {
    assign(GConnection());
}
//===============================================
