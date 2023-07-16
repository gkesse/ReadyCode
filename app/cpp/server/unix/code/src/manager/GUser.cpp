//===============================================
#include "GUser.h"
#include "GMySQL.h"
//===============================================
GUser::GUser()
: GManager() {
    m_id = 0;
}
//===============================================
GUser::~GUser() {

}
//===============================================
bool GUser::isValidEmail() const {
    const std::regex lPattern(""
            "(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+"
            "");
    return std::regex_match(m_email.c_str(), lPattern);
}
//===============================================
int GUser::countUser() {
    GMySQL dbSQL;
    int lCount = dbSQL.readData(sformat(""
            " select count(*) "
            " from _user "
            " where 1 = 1 "
            " and _pseudo = '%s' "
            "", m_pseudo.c_str()
            )).toInt();
    m_logs.addLogs(dbSQL.getLogs());
    return lCount;
}
//===============================================
void GUser::loadUser() {
    GString lPassword = sformat(""
            "%s|%s"
            "", m_pseudo.c_str()
            , m_password.c_str()).toMd5();

    GMySQL dbSQL;
    GMySQL::GMaps lDataMap = dbSQL.readMap(sformat(""
            " select _id, _pseudo, _email "
            " , _create_date, _update_date "
            " from _user "
            " where 1 = 1 "
            " and _pseudo = '%s' "
            " and _password = '%s' "
            "", m_pseudo.c_str()
            , lPassword.c_str()
            ));
    m_logs.addLogs(dbSQL.getLogs());

    for(int i = 0; i < (int)lDataMap.size(); i++) {
        GMySQL::GRows lDataRow = lDataMap.at(i);
        int j = 0;
        m_id = lDataRow.at(j++).toInt();
        m_pseudo = lDataRow.at(j++);
        m_email = lDataRow.at(j++);
        m_createDate = lDataRow.at(j++).toDateTime();
        m_updateDate = lDataRow.at(j++).toDateTime();
        break;
    }
}
//===============================================
void GUser::insertUser() {
    GString lPassword = sformat(""
            "%s|%s"
            "", m_pseudo.c_str()
            , m_password.c_str()).toMd5();

    GMySQL dbSQL;
    dbSQL.insertQuery(sformat(""
            " insert into _user "
            " ( _pseudo, _password ) "
            " values ( '%s', '%s' ) "
            "", m_pseudo.c_str()
            , lPassword.c_str()
            ));
    m_logs.addLogs(dbSQL.getLogs());

    if(!m_logs.hasErrors()) {
        m_id = dbSQL.getId();
    }
}
//===============================================
void GUser::updateUser(const GString& _sql) {
    GMySQL dbSQL;
    dbSQL.execQuery(_sql);
    m_logs.addLogs(dbSQL.getLogs());
}
//===============================================
GString GUser::serialize(const GString& _code) const {
    GCode lDom;
    lDom.createDoc();
    lDom.addData(_code, "id", m_id);
    lDom.addData(_code, "pseudo", m_pseudo);
    lDom.addData(_code, "password", m_password);
    lDom.addData(_code, "email", m_email);
    lDom.addData(_code, "create_date", m_createDate.toString());
    lDom.addData(_code, "update_date", m_updateDate.toString());
    lDom.addMap(_code, m_map);
    return lDom.toString();
}
//===============================================
void GUser::deserialize(const GString& _data, const GString& _code) {
    GManager::deserialize(_data);
    GCode lDom;
    lDom.loadXml(_data);
    m_id = lDom.getData(_code, "id").toInt();
    m_pseudo = lDom.getData(_code, "pseudo");
    m_password = lDom.getData(_code, "password");
    m_email = lDom.getData(_code, "email");
    m_createDate = lDom.getData(_code, "create_date").toDateTime();
    m_updateDate = lDom.getData(_code, "update_date").toDateTime();
    lDom.getMap(_code, m_map, this);
}
//===============================================
void GUser::run(const GString& _data) {
    deserialize(_data);
    if(m_method == "") {
        m_logs.addError("La méthode est obligatoire.");
    }
    else if(m_method == "login_user") {
        onLoginUser(_data);
    }
    else if(m_method == "insert_user") {
        onInsertUser(_data);
    }
    else if(m_method == "update_user") {
        onUpdateUser(_data);
    }
    else {
        m_logs.addError("La méthode est inconnue.");
    }
}
//===============================================
void GUser::onLoginUser(const GString& _data) {
    if(m_pseudo == "") {
        m_logs.addError("Le nom d'utilisateur est obligatoire.");
        return;
    }
    if(m_pseudo.size() < 5) {
        m_logs.addError("Le nom d'utilisateur est trop petit.");
        return;
    }
    if(m_pseudo.size() > 50) {
        m_logs.addError("Le nom d'utilisateur est trop long.");
        return;
    }

    if(m_password == "") {
        m_logs.addError("Le mot de passe est obligatoire.");
        return;
    }
    if(m_password.size() < 5) {
        m_logs.addError("Le mot de passe est trop petit.");
        return;
    }
    if(m_password.size() > 50) {
        m_logs.addError("Le mot de passe est trop long.");
        return;
    }

    if(!countUser()) {
        m_logs.addError("Cet utilisateur n'est pas encore inscrit.");
        return;
    }
    loadUser();
}
//===============================================
void GUser::onInsertUser(const GString& _data) {
    if(m_pseudo == "") {
        m_logs.addError("Le nom d'utilisateur est obligatoire.");
        return;
    }
    if(m_pseudo.size() < 5) {
        m_logs.addError("Le nom d'utilisateur est trop petit.");
        return;
    }
    if(m_pseudo.size() > 50) {
        m_logs.addError("Le nom d'utilisateur est trop long.");
        return;
    }

    if(m_password == "") {
        m_logs.addError("Le mot de passe est obligatoire.");
        return;
    }
    if(m_password.size() < 5) {
        m_logs.addError("Le mot de passe est trop petit.");
        return;
    }
    if(m_password.size() > 50) {
        m_logs.addError("Le mot de passe est trop long.");
        return;
    }

    insertUser();
}
//===============================================
void GUser::onUpdateUser(const GString& _data) {
    if(m_id == 0) {
        m_logs.addError("L'identifiant d'utilisateur est obligatoire.");
        return;
    }

    std::vector<GString> lMap;
    bool hasPseudo = false;

    if(m_pseudo != "") {
        if(m_pseudo.size() < 5) {
            m_logs.addError("Le nom d'utilisateur est trop petit.");
            return;
        }
        if(m_pseudo.size() > 50) {
            m_logs.addError("Le nom d'utilisateur est trop long.");
            return;
        }
        hasPseudo = true;
        lMap.push_back(sformat(" _pseudo = '%s' ", m_pseudo.c_str()));
    }

    if(hasPseudo && m_password != "") {
        if(m_password.size() < 5) {
            m_logs.addError("Le mot de passe est trop petit.");
            return;
        }
        if(m_password.size() > 50) {
            m_logs.addError("Le mot de passe est trop long.");
            return;
        }

        GString lPassword = sformat(""
                "%s|%s"
                "", m_pseudo.c_str()
                , m_password.c_str()).toMd5();

        lMap.push_back(sformat(" _password = '%s' ", lPassword.c_str()));
    }

    if(m_email != "") {
        if(m_email.size() < 5) {
            m_logs.addError("L'email est trop petit.");
            return;
        }
        if(m_email.size() > 50) {
            m_logs.addError("L'email est trop long.");
            return;
        }
        if(!isValidEmail()) {
            m_logs.addError("L'email n'est pas valide.");
            return;
        }
        lMap.push_back(sformat(" _email = '%s' ", m_email.c_str()));
    }

    if(lMap.size()) {
        GString lSql = "";
        lSql += " update _user set ";
        for(int i = 0; i < (int)lMap.size(); i++) {
            GString lUpdate = lMap[i];
            if(i != 0) lSql += ",";
            lSql += lUpdate;
        }
        lSql += sformat(" where _id = %d ", m_id);

        updateUser(lSql);
    }
}
//===============================================
