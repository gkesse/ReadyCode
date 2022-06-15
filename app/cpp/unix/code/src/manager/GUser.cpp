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
    m_mode = D_USER_MODE_EMAIL;
    m_email = "";
    m_pseudo = "";
    m_password = "";
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
void GUser::onModule(GSocket* _client) {
    deserialize(_client->toReq());
    //===============================================
    // method
    //===============================================
    if(m_method == "has_user") {
        onHasUser(_client);
    }
    else if(m_method == "has_user_password") {
        onHasUserPassword(_client);
    }
    else if(m_method == "create_user") {
        onCreateUser(_client);
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
}
//===============================================
void GUser::onHasUser(GSocket* _client) {
    deserialize(_client->toReq());
    computePassword();
    loadId();
    std::string lData = serialize();
    _client->addResponse(lData);
}
//===============================================
void GUser::onHasUserPassword(GSocket* _client) {
    deserialize(_client->toReq());
    computePassword();
    loadIdPassword();
    loadUser();
    std::string lData = serialize();
    _client->addResponse(lData);
}
//===============================================
void GUser::onCreateUser(GSocket* _client) {
    deserialize(_client->toReq());
    computePassword();
    loadId();
    saveData();
    loadId();
    loadUser();
    std::string lData = serialize();
    _client->addResponse(lData);
}
//===============================================
void GUser::onRunConnection(GSocket* _client) {
    runConnection();
    /*computePassword();
    loadId();
    saveData();
    loadId();
    loadUser();*/
    std::string lData = serialize();
    _client->addResponse(lData);
}
//===============================================
bool GUser::runConnection() {
    if(m_mode == D_USER_MODE_EMAIL) return runConnectionEmail();
    if(m_mode == D_USER_MODE_PSEUDO) return runConnectionPseudo();
    GERROR(eGERR, "Le mode de recherche n'est pas defini.");
    return false;
}
//===============================================
bool GUser::runConnectionEmail() {
    if(m_email == "") {GERROR(eGERR, "L'email est obligatoire."); return false;}
    if(m_password == "") {GERROR(eGERR, "Le mot de passe est obligatoire."); return false;}
    loadUserEmail();
    if(m_id == 0) {GERROR(eGERR, "L'email n'existe pas encore."); return false;}
    return true;
}
//===============================================
bool GUser::runConnectionPseudo() {
    if(m_mode == "") {GERROR(eGERR, "Le mode de recherche n'est pas defini."); return false;}
    if(m_pseudo == "") {GERROR(eGERR, "Le nom d'utilisateur est obligatoire."); return false;}
    if(m_password == "") {GERROR(eGERR, "Le mot de passe est obligatoire."); return false;}
    return true;
}
//===============================================
bool GUser::loadUserEmail() {
    std::string lData = GMySQL().readData(sformat(""
            " select _id "
            " from _user "
            " where _email = '%s' "
            "", m_email.c_str()
    ));
    m_id = GString(lData).toInt();
    return true;
}
//===============================================
int GUser::countMode(const std::string& _mode) {
    std::string lData = GMySQL().readData(sformat(""
            " select count(*) "
            " from user_mode "
            " where _mode = '%s' "
            "", _mode.c_str()
    ));
    int lCount = GString(lData).toInt();
    return lCount;
}
//===============================================
int GUser::getId() const {
    return m_id;
}
//===============================================
void GUser::loadId() {
    if(m_pseudo == "") return;

    std::string lId = GMySQL().readData(sformat(""
            " select _id "
            " from user "
            " where _pseudo = '%s' "
            "", m_pseudo.c_str()
    ));

    m_id = GString(lId).toInt();
}
//===============================================
void GUser::loadIdPassword() {
    if(m_pseudo == "") return;
    if(m_password == "") return;

    std::string lId = GMySQL().readData(sformat(""
            " select _id "
            " from user "
            " where _pseudo = '%s' "
            " and _password = '%s' "
            "", m_pseudo.c_str()
            , m_password.c_str()
    ));

    m_id = GString(lId).toInt();
}
//===============================================
void GUser::loadUser() {
    if(!m_id) return;

    std::vector<std::string> lRow = GMySQL().readRow(sformat(""
            " select _id, _pseudo, _group, _active "
            " from user "
            " where _id = %d "
            "", m_id
    ));

    int i = 0;
    m_id = GString(lRow.at(i++)).toInt();
    m_pseudo = lRow.at(i++);
    m_group = lRow.at(i++);
    m_active = lRow.at(i++);
}
//===============================================
void GUser::computePassword() {
    if(m_pseudo == "") return;
    if(m_password == "") return;

    m_password = sformat("%s|%s", m_pseudo.c_str(), m_password.c_str());
    m_password = GMd5(m_password).encodeData();
}
//===============================================
void GUser::saveData() {
    if(!m_id) {
        insertData();
    }
    else {
        updateData();
    }
}
//===============================================
void GUser::insertData() {
    if(m_id != 0) return;
    if(m_pseudo == "") return;
    if(m_password == "") return;

    GMySQL().execQuery(sformat(""
            " insert into user "
            " ( _pseudo, _password ) "
            " values ( '%s', '%s' ) "
            "", m_pseudo.c_str()
            , m_password.c_str()
    ));
}
//===============================================
void GUser::updateData() {
    if( m_id == 0) return;
    if(m_pseudo == "") return;
    if(m_password == "") return;

    GMySQL().execQuery(sformat(""
            " update user "
            " set _pseudo = '%s' "
            " , _password = '%s' "
            " where _id = %d "
            "", m_pseudo.c_str()
            , m_password.c_str()
            , m_id
    ));
}
//===============================================
