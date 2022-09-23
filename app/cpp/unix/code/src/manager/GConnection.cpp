//===============================================
#include "GConnection.h"
#include "GLog.h"
#include "GServer.h"
#include "GCode2.h"
#include "GMySQL2.h"
#include "GMd5_2.h"
//===============================================
GConnection::GConnection()
: GModule2() {
    m_id = 0;
    m_active = 0;
    m_isConnect = false;
}
//===============================================
GConnection::GConnection(GModule2* _module)
: GModule2(_module) {
    m_id = 0;
    m_active = 0;
    m_isConnect = false;
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
    lDom.addData(_code, "id", m_id);
    lDom.addData(_code, "pseudo", m_pseudo);
    lDom.addData(_code, "password", m_password);
    lDom.addData(_code, "email", m_email);
    lDom.addData(_code, "group", m_group);
    lDom.addData(_code, "active", m_active);
    lDom.addData(_code, "is_connect", m_isConnect);
    return lDom.toString();
}
//===============================================
bool GConnection::deserialize(const GString2& _data, const GString2& _code) {
    GModule2::deserialize(_data);
    GCode2 lDom;
    lDom.loadXml(_data);
    m_id = lDom.getData(_code, "id").toInt();
    m_pseudo = lDom.getData(_code, "pseudo");
    m_password = lDom.getData(_code, "password");
    m_email = lDom.getData(_code, "email");
    m_group = lDom.getData(_code, "group");
    m_active = lDom.getData(_code, "active").toChar();
    m_isConnect = lDom.getData(_code, "is_connect").toBool();
    return true;
}
//===============================================
bool GConnection::onModule() {
    deserialize(m_client->getRequest());
    if(m_method == "run_connection") {
        onRunConnection();
    }
    return true;
}
//===============================================
bool GConnection::onRunConnection() {
    if(m_pseudo == "") {GERROR_ADD(eGERR, "Le nom d'utilisateur est obligatoire."); return false;}
    if(m_password == "") {GERROR_ADD(eGERR, "Le mot de passe est obligatoire."); return false;}
    if(!loadUserPseudo()) return false;
    if(m_id == 0) {GERROR_ADD(eGERR, "Le nom d'utilisateur n'existe pas encore."); return false;}
    if(!computePassword()) return false;
    if(!loadUserPassword()) return false;
    if(m_id == 0) {GERROR_ADD(eGERR, "Le mot de passe est incorrect."); return false;}
    if(!loadUser()) return false;
    GLOG_ADD(eGLOG, "La connexion a réussi.");
    m_isConnect = true;
    if(!updateConnection()) return false;
    return true;
}
//===============================================
bool GConnection::loadUserPseudo() {
    GString2 lData = GMySQL2().readData(sformat(""
            " select _id "
            " from _user "
            " where _pseudo = '%s' "
            " and _active = '1' "
            "", m_pseudo.c_str()
    ));
    m_id = lData.toInt();
    return true;
}
//===============================================
bool GConnection::loadUserPassword() {
    if(m_id == 0) return false;
    if(m_passwordMd5 == "") return false;
    GString2 lData = GMySQL2().readData(sformat(""
            " select _id "
            " from _user "
            " where _id = %d "
            " and _password = '%s' "
            " and _active = '1' "
            "", m_id
            , m_passwordMd5.c_str()
    ));
    m_id = lData.toInt();
    return true;
}
//===============================================
bool GConnection::loadUser() {
    if(m_id == 0) return false;

    std::vector<GString2> lRow = GMySQL2().readRow(sformat(""
            " select _pseudo, _password, _email, _group, _active "
            " from _user "
            " where _id = %d "
            " and _active = '1' "
            "", m_id
    ));

    int i = 0;
    m_pseudo = lRow.at(i++);
    m_password = lRow.at(i++);
    m_email = lRow.at(i++);
    m_group = lRow.at(i++);
    m_active = lRow.at(i++).toChar();
    return true;
}
//===============================================
bool GConnection::computePassword() {
    if(m_pseudo == "") return false;
    if(m_password == "") return false;
    m_passwordMd5 = sformat("%s|%s", m_pseudo.c_str(), m_password.c_str());
    m_passwordMd5 = GMd5_2().encodeData(m_passwordMd5);
    return true;
}
//===============================================
bool GConnection::saveUser() {
    if(m_id == 0) return insertUser();
    return updateUser();
}
//===============================================
bool GConnection::insertUser() {
    if(m_id != 0) return false;
    if(m_pseudo == "") return false;
    if(m_passwordMd5 == "") return false;

    m_id = GMySQL2().execQuery(sformat(""
            " insert into _user "
            " ( _pseudo, _password ) "
            " values ( '%s', '%s' ) "
            "", m_pseudo.c_str()
            , m_passwordMd5.c_str()
    )).getId();

    return true;
}
//===============================================
bool GConnection::updateUser() {
    if( m_id == 0) return false;
    if(m_pseudo == "") return false;
    if(m_password == "") return false;

    GMySQL2().execQuery(sformat(""
            " update _user "
            " set _pseudo = '%s' "
            " , _password = '%s' "
            " where _id = %d "
            "", m_pseudo.c_str()
            , m_passwordMd5.c_str()
            , m_id
    ));

    return true;
}
//===============================================
bool GConnection::updateConnection() {
    if( m_id == 0) return false;

    GMySQL2().execQuery(sformat(""
            " update _user "
            " set _connect = '%d' "
            " , _d_connect = now() "
            " where _id = %d "
            "", m_isConnect
            , m_id
    ));

    return true;
}
//===============================================