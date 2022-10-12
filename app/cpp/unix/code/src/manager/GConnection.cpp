//===============================================
#include "GConnection.h"
#include "GMySQL.h"
#include "GCode.h"
#include "GLog.h"
#include "GServer.h"
#include "GMd5.h"
//===============================================
GConnection::GConnection()
: GManager() {
    m_id = 0;
    m_active = 0;
    m_isConnect = false;
}
//===============================================
GConnection::~GConnection() {

}
//===============================================
GObject* GConnection::clone() const {
    return new GConnection;
}
//===============================================
GString GConnection::serialize() const {
    GCode lDom;
    lDom.createDoc();
    lDom.addData(m_codeName, "id", m_id);
    lDom.addData(m_codeName, "pseudo", m_pseudo);
    lDom.addData(m_codeName, "password", m_password);
    lDom.addData(m_codeName, "email", m_email);
    lDom.addData(m_codeName, "group", m_group);
    lDom.addData(m_codeName, "active", m_active);
    lDom.addData(m_codeName, "is_connect", m_isConnect);
    return lDom.toString();
}
//===============================================
bool GConnection::deserialize(const GString& _data) {
    GManager::deserialize(_data);
    GCode lDom;
    lDom.loadXml(_data);
    m_id = lDom.getData(m_codeName, "id").toInt();
    m_pseudo = lDom.getData(m_codeName, "pseudo");
    m_password = lDom.getData(m_codeName, "password");
    m_email = lDom.getData(m_codeName, "email");
    m_group = lDom.getData(m_codeName, "group");
    m_active = lDom.getData(m_codeName, "active").toBool();
    m_isConnect = lDom.getData(m_codeName, "is_connect").toBool();
    return true;
}
//===============================================
bool GConnection::loadUserPseudo() {
    GString lData = GMySQL().readData(GFORMAT(""
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
    GString lData = GMySQL().readData(GFORMAT(""
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

    std::vector<GString> lRow = GMySQL().readRow(GFORMAT(""
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
    m_active = lRow.at(i++).toBool();
    return true;
}
//===============================================
bool GConnection::computePassword() {
    if(m_pseudo == "") return false;
    if(m_password == "") return false;
    m_passwordMd5 = GFORMAT("%s|%s", m_pseudo.c_str(), m_password.c_str());
    m_passwordMd5 = GMd5().encodeData(m_passwordMd5);
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
    GMySQL lMySQL2;
    if(!GMySQL().execQuery(GFORMAT(""
            " insert into _user "
            " ( _pseudo, _password ) "
            " values ( '%s', '%s' ) "
            "", m_pseudo.c_str()
            , m_passwordMd5.c_str()
    ))) return false;
    m_id = lMySQL2.getId();
    return true;
}
//===============================================
bool GConnection::updateUser() {
    if( m_id == 0) return false;
    if(!GMySQL().execQuery(GFORMAT(""
            " update _user "
            " set _pseudo = '%s' "
            " , _password = '%s' "
            " where _id = %d "
            "", m_pseudo.c_str()
            , m_passwordMd5.c_str()
            , m_id
    ))) return false;
    return true;
}
//===============================================
bool GConnection::updateConnection() {
    if( m_id == 0) return false;
    if(!GMySQL().execQuery(GFORMAT(""
            " update _user "
            " set _connect = '%d' "
            " , _d_connect = now() "
            " where _id = %d "
            "", m_isConnect
            , m_id
    ))) return false;
    return true;
}
//===============================================
void GConnection::print() const {
    printf("%s\n", serialize().c_str());
}
//===============================================
bool GConnection::onModule() {
    deserialize(m_server->getRequest());
    if(m_methodName == "") {
        GMETHOD_REQUIRED();
    }
    else if(m_methodName == "run_connection") {
        onRunConnection();
    }
    else {
        GMETHOD_UNKNOWN();
    }
    m_server->addResponse(serialize());
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
