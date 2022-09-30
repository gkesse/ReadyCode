//===============================================
#include "GUser.h"
#include "GLog.h"
#include "GCode.h"
#include "GMySQL.h"
#include "GSocket.h"
#include "GString.h"
#include "GMd5.h"
#include "GDefine.h"
//===============================================
GUser::GUser()
: GModule() {
    m_id = 0;
    m_mode = "";
    m_email = "";
    m_pseudo = "";
    m_password = "";
    m_passwordMd5 = "";
    m_group = "";
    m_active = "";
    m_isConnect = false;
}
//===============================================
GUser::~GUser() {

}
//===============================================
GString GUser::serialize(const GString& _code) const {
    GCode lDom;
    lDom.createDoc();
    lDom.addData(_code, "id", m_id);
    lDom.addData(_code, "mode", m_mode);
    lDom.addData(_code, "email", m_email);
    lDom.addData(_code, "pseudo", m_pseudo);
    lDom.addData(_code, "password", m_password);
    lDom.addData(_code, "group", m_group);
    lDom.addData(_code, "active", m_active);
    lDom.addData(_code, "is_connect", m_isConnect);
    return lDom.toStringData();
}
//===============================================
void GUser::deserialize(const GString& _data, const GString& _code) {
    GModule::deserialize(_data);
    GCode lDom;
    lDom.loadXml(_data);
    m_id = GString(lDom.getItem(_code, "id")).toInt();
    m_mode = lDom.getItem(_code, "mode");
    m_email = lDom.getItem(_code, "email");
    m_pseudo = lDom.getItem(_code, "pseudo");
    m_password = lDom.getItem(_code, "password");
    m_group = lDom.getItem(_code, "group");
    m_active = lDom.getItem(_code, "active");
    m_isConnect = GString(lDom.getItem(_code, "is_connect")).toBool();
}
//===============================================
bool GUser::onModule(GSocket* _client) {
    deserialize(_client->toReq());
    //
    if(m_method == "") {
        return false;
    }
    else if(m_method == "create_account") {
        onCreateAccount(_client);
    }
    else if(m_method == "run_connection") {
        onRunConnection(_client);
    }
    else if(m_method == "run_disconnection") {
        onRunDisconnection(_client);
    }
    else {
        onMethodUnknown(_client);
    }
    return true;
}
//===============================================
void GUser::onCreateAccount(GSocket* _client) {
    createAccount();
    GString lData = serialize();
    _client->addResponse(lData);
}
//===============================================
void GUser::onRunConnection(GSocket* _client) {
    runConnection();
    GString lData = serialize();
    _client->addResponse(lData);
}
//===============================================
void GUser::onRunDisconnection(GSocket* _client) {
    runDisconnection();
    GString lData = serialize();
    _client->addResponse(lData);
}
//===============================================
bool GUser::runConnection() {
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
bool GUser::runDisconnection() {
    if(m_id == 0) {GERROR_ADD(eGERR, "L'identifiant est obligatoire."); return false;}
    m_isConnect = false;
    if(!updateConnection()) return false;
    return true;
}
//===============================================
bool GUser::createAccount() {
    if(m_pseudo == "") {GERROR_ADD(eGERR, "Le nom d'utilisateur est obligatoire."); return false;}
    if(m_pseudo.size() < 4) {GERROR_ADD(eGERR, "Le nom d'utilisateur doit faire au minimum 4 caractères."); return false;}
    if(m_pseudo.size() > 50) {GERROR_ADD(eGERR, "Le nom d'utilisateur doit faire au maximum 50 caractères."); return false;}
    if(m_password == "") {GERROR_ADD(eGERR, "Le mot de passe est obligatoire."); return false;}
    if(m_password.size() < 4) {GERROR_ADD(eGERR, "Le mot de passe doit faire au minimum 4 caractères."); return false;}
    if(m_password.size() > 50) {GERROR_ADD(eGERR, "Le mot de passe doit faire au maximum 50 caractères."); return false;}
    if(!loadUserPseudo()) return false;
    if(m_id != 0) {GERROR_ADD(eGERR, "Le nom d'utilisateur existe déjà."); return false;}
    if(!computePassword()) return false;
    if(!saveUser()) return false;
    GLOG_ADD(eGLOG, "La création du compte a réussi.");
    return true;
}
//===============================================
bool GUser::loadUserPseudo() {
    GString lData = GMySQL().readData(GFORMAT(""
            " select _id "
            " from _user "
            " where _pseudo = '%s' "
            " and _active = '1' "
            "", m_pseudo.c_str()
    ));
    m_id = GString(lData).toInt();
    return true;
}
//===============================================
bool GUser::loadUserPassword() {
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
    m_id = GString(lData).toInt();
    return true;
}
//===============================================
bool GUser::loadUser() {
    if(m_id == 0) return false;

    std::vector<GString> lRow = GMySQL().readRow(GFORMAT(""
            " select _email, _pseudo, _group, _active "
            " from _user "
            " where _id = %d "
            " and _active = '1' "
            "", m_id
    ));

    int i = 0;
    m_email = lRow.at(i++);
    m_pseudo = lRow.at(i++);
    m_group = lRow.at(i++);
    m_active = lRow.at(i++);
    return true;
}
//===============================================
bool GUser::computePassword() {
    if(m_pseudo == "") return false;
    if(m_password == "") return false;
    m_passwordMd5 = GFORMAT("%s|%s", m_pseudo.c_str(), m_password.c_str());
    m_passwordMd5 = GMd5().encodeData(m_passwordMd5);
    return true;
}
//===============================================
bool GUser::saveUser() {
    if(m_id == 0) return insertUser();
    return updateUser();
}
//===============================================
bool GUser::insertUser() {
    if(m_id != 0) return false;
    if(m_pseudo == "") return false;
    if(m_passwordMd5 == "") return false;

    m_id = GMySQL().execQuery(GFORMAT(""
            " insert into _user "
            " ( _pseudo, _password ) "
            " values ( '%s', '%s' ) "
            "", m_pseudo.c_str()
            , m_passwordMd5.c_str()
    )).getId();

    return true;
}
//===============================================
bool GUser::updateUser() {
    if( m_id == 0) return false;
    if(m_pseudo == "") return false;
    if(m_password == "") return false;

    GMySQL().execQuery(GFORMAT(""
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
bool GUser::updateConnection() {
    if( m_id == 0) return false;

    GMySQL().execQuery(GFORMAT(""
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
