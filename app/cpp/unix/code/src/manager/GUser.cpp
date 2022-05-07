//===============================================
#include "GUser.h"
#include "GLog.h"
#include "GFormat.h"
#include "GCode.h"
#include "GMySQL.h"
#include "GSocket.h"
#include "GString.h"
#include "GMd5.h"
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
    if(lMethod == "has_user") {
        onHasUser(_client);
    }
    else if(lMethod == "has_user_password") {
        onHasUserPassword(_client);
    }
    else if(lMethod == "create_user") {
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
void GUser::onHasUser(GSocket* _client) {
    std::shared_ptr<GCode>& lReq = _client->getReq();
    m_pseudo = lReq->getParam("pseudo");
    loadId();
    std::shared_ptr<GCode>& lRes = _client->getResponse();
    lRes->createCode("user", "id", m_id);
}
//===============================================
void GUser::onHasUserPassword(GSocket* _client) {
    std::shared_ptr<GCode>& lReq = _client->getReq();
    m_pseudo = lReq->getParam("pseudo");
    m_password = lReq->getParam("password");
    computePassword();
    loadIdPassword();
    std::shared_ptr<GCode>& lRes = _client->getResponse();
    lRes->createCode("user", "id", m_id);
}
//===============================================
void GUser::onCreateUser(GSocket* _client) {
    std::shared_ptr<GCode>& lReq = _client->getReq();
    m_pseudo = lReq->getParam("pseudo");
    m_password = lReq->getParam("password");
    computePassword();
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
    if(!m_id) return;
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
