//===============================================
#include "GConnection.h"
#include "GMySQL.h"
#include "GSocket.h"
#include "GMd5.h"
#include "GCode.h"
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
GString GConnection::serialize(const GString& _code) {
    GCode lDom;
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
void GConnection::deserialize(const GString& _data, const GString& _code) {
    GManager::deserialize(_data);
    GCode lDom;
    lDom.loadXml(_data);
    m_id = lDom.getData(_code, "id").toInt();
    m_pseudo = lDom.getData(_code, "pseudo");
    m_password = lDom.getData(_code, "password");
    m_email = lDom.getData(_code, "email");
    m_group = lDom.getData(_code, "group");
    m_active = lDom.getData(_code, "active").toBool();
    m_isConnect = lDom.getData(_code, "is_connect").toBool();
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
void GConnection::print() {
    printf("%s\n", serialize().c_str());
}
//===============================================
bool GConnection::onModule() {
    deserialize(m_server->getRequest());
    if(m_methodName == "") {
        m_logs.addError("La méthode est obligatoire.");
    }
    else if(m_methodName == "run_connection") {
        onRunConnection();
    }
    else {
        m_logs.addError("La méthode est inconnue.");
    }
    m_server->addResponse(serialize());
    return true;
}
//===============================================
bool GConnection::onRunConnection() {
    if(m_pseudo == "") {
        m_logs.addError("Le nom d'utilisateur est obligatoire.");
        return false;
    }
    if(m_password == "") {
        m_logs.addError("Le mot de passe est obligatoire.");
        return false;
    }
    if(!loadUserPseudo()) return false;
    if(m_id == 0) {
        m_logs.addError("Le nom d'utilisateur n'existe pas encore.");
        return false;
    }
    if(!computePassword()) return false;
    if(!loadUserPassword()) return false;
    if(m_id == 0) {
        m_logs.addError("Le mot de passe est incorrect.");
        return false;
    }
    if(!loadUser()) return false;
    m_logs.addLog("La connexion a réussi.");
    m_isConnect = true;
    if(!updateConnection()) return false;
    return true;
}
//===============================================
