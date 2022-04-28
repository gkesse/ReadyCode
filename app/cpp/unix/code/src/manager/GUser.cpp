//===============================================
#include "GUser.h"
#include "GLog.h"
#include "GFormat.h"
#include "GCode.h"
#include "GMySQL.h"
#include "GSocket.h"
//===============================================
GUser::GUser() : GModule() {
    m_id = 0;
    m_pseudo = "";
    m_password = "";
}
//===============================================
GUser::GUser(const std::string& _pseudo) : GModule() {
    m_id = 0;
    m_pseudo = _pseudo;
    m_password = "";
    loadId();
}
//===============================================
GUser::~GUser() {

}
//===============================================
void GUser::onModule(GSocket* _client) {
    std::string lMethod = _client->getReq()->getMethod();
    //===============================================
    // method
    //===============================================
    if(lMethod == "create_user") {
        onCreateUser(_client);
    }
    else if(lMethod == "save_user") {
        onSaveUser(_client);
    }
    //===============================================
    // unknown
    //===============================================
    else {
        onMethodUnknown(_client);
    }
}
//===============================================
void GUser::onCreateUser(GSocket* _client) {
    std::shared_ptr<GCode>& lReq = _client->getReq();
    m_pseudo = lReq->getParam("pseudo");
    m_password = lReq->getParam("password");
    GLOGT(eGMSG, ""
            "pseudo.......: %s\n"
            "password.....: (%s)\n"
            "", m_pseudo.c_str() , m_password.c_str());
    loadId();
    saveData();
}
//===============================================
void GUser::onSaveUser(GSocket* _client) {

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
    if(lId != "") m_id = std::stoi(lId);
    GLOGT(eGOFF, "id...........: %d", m_id);
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
    GMySQL().execQuery(sformat(""
            " insert into user "
            " ( _pseudo, _password ) "
            " values ( '%s', md5('%s|%s') ) "
            "", m_pseudo.c_str()
            , m_pseudo.c_str()
            , m_password.c_str()
    ));
}
//===============================================
void GUser::updateData() {
    GMySQL().execQuery(sformat(""
            " update user "
            " set _pseudo = '%s' "
            " , _password = md5('%s|%s') "
            " where _id = %d "
            "", m_pseudo.c_str()
            , m_pseudo.c_str()
            , m_password.c_str()
            , m_id
    ));
}
//===============================================
