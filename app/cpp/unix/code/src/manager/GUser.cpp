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

}
//===============================================
void GUser::onSaveUser(GSocket* _client) {

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
