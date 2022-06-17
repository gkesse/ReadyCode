//===============================================
#include "GUser.h"
#include "GLog.h"
#include "GFormat.h"
#include "GCode.h"
#include "GMySQL.h"
#include "GSocket.h"
#include "GString.h"
#include "GMd5.h"
#include "GDefine.h"
//===============================================
GUser::GUser() : GModule() {
    m_id = 0;
    m_mode = "";
    m_email = "";
    m_pseudo = "";
    m_password = "";
    m_passwordMd5 = "";
    m_group = "";
    m_active = "";
}
//===============================================
GUser::~GUser() {

}
//===============================================
std::string GUser::serialize(const std::string& _code) const {
    GCode lReq;
    lReq.createDoc();
    lReq.addData(_code, "id", m_id);
    lReq.addData(_code, "mode", m_mode);
    lReq.addData(_code, "email", m_email);
    lReq.addData(_code, "pseudo", m_pseudo);
    lReq.addData(_code, "password", m_password);
    lReq.addData(_code, "group", m_group);
    lReq.addData(_code, "active", m_active);
    return lReq.toStringCode(_code);
}
//===============================================
void GUser::deserialize(const std::string& _data, const std::string& _code) {
    GModule::deserialize(_data);
    GCode lReq;
    lReq.loadXml(_data);
    m_id = GString(lReq.getItem(_code, "id")).toInt();
    m_mode = lReq.getItem(_code, "mode");
    m_email = lReq.getItem(_code, "email");
    m_pseudo = lReq.getItem(_code, "pseudo");
    m_password = lReq.getItem(_code, "password");
    m_group = lReq.getItem(_code, "group");
    m_active = lReq.getItem(_code, "active");
}
//===============================================
bool GUser::onModule(GSocket* _client) {
    deserialize(_client->toReq());
    //===============================================
    if(m_method == "") {
        return false;
    }
    //===============================================
    // method
    //===============================================
    else if(m_method == "create_account") {
        onCreateAccount(_client);
    }
    else if(m_method == "run_connection") {
        onRunConnection(_client);
    }
    //===============================================
    // unknown
    //===============================================
    else {
        onMethodUnknown(_client);
    }
    return true;
}
//===============================================
void GUser::onCreateAccount(GSocket* _client) {
    createConnection();
    std::string lData = serialize();
    _client->addResponse(lData);
}
//===============================================
void GUser::onRunConnection(GSocket* _client) {
    runConnection();
    std::string lData = serialize();
    _client->addResponse(lData);
}
//===============================================
bool GUser::runConnection() {
    if(m_pseudo == "") {GERROR(eGERR, "Le nom d'utilisateur est obligatoire."); return false;}
    if(m_password == "") {GERROR(eGERR, "Le mot de passe est obligatoire."); return false;}
    loadUserPseudo();
    if(m_id == 0) {GERROR(eGERR, "Le nom d'utilisateur n'existe pas encore."); return false;}
    computePassword();
    loadUserPassword();
    if(m_id == 0) {GERROR(eGERR, "Le mot de passe est incorrect."); return false;}
    loadUser();
    return true;
}
//===============================================
bool GUser::createConnection() {
    if(m_pseudo == "") {GERROR(eGERR, "Le nom d'utilisateur est obligatoire."); return false;}
    if(m_password == "") {GERROR(eGERR, "Le mot de passe est obligatoire."); return false;}
    loadUserPseudo();
    if(m_id != 0) {GERROR(eGERR, "Le nom d'utilisateur n'existe pas encore."); return false;}
    computePassword();
    saveUser();
    if(m_id == 0) {GERROR(eGERR, "Le mot de passe est incorrect."); return false;}
    loadUser();
    return true;
}
//===============================================
bool GUser::loadUserPseudo() {
    std::string lData = GMySQL().readData(sformat(""
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
    std::string lData = GMySQL().readData(sformat(""
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

    std::vector<std::string> lRow = GMySQL().readRow(sformat(""
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
    m_passwordMd5 = sformat("%s|%s", m_pseudo.c_str(), m_password.c_str());
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

    m_id = GMySQL().execQuery(sformat(""
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

    GMySQL().execQuery(sformat(""
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
