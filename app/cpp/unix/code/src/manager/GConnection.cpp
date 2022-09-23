//===============================================
#include "GConnection.h"
#include "GLog.h"
#include "GServer.h"
#include "GCode2.h"
//===============================================
GConnection::GConnection()
: GModule2() {
    m_client = 0;
}
//===============================================
GConnection::~GConnection() {

}
//===============================================
GObject2* GConnection::clone() const {
    return new GConnection;
}
//===============================================
GString2 GConnection::serialize(const GString2& _code) const {
    GCode2 lDom;
    lDom.createDoc();
    lDom.addData(_code, "pseudo", m_psedudo);
    lDom.addData(_code, "password", m_password);
    return lDom.toString();
}
//===============================================
bool GConnection::deserialize(const GString2& _data, const GString2& _code) {
    GModule2::deserialize(_data);
    return true;
}
//===============================================
bool GConnection::onModule() {
    deserialize(m_client->getRequest());
    if(m_password == "run_connection") {
        onRunConnection();
    }
    return true;
}
//===============================================
bool GConnection::onRunConnection() {

    return true;
}
//===============================================
