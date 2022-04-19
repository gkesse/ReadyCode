//===============================================
#include "GRequest.h"
#include "GLog.h"
#include "GFormat.h"
#include "GMySQL.h"
#include "GCode.h"
#include "GUser.h"
//===============================================
GRequest::GRequest() : GObject() {
    m_id = 0;
    m_uid = 0;
    m_module = "";
    m_method = "";
    m_msg = "";
}
//===============================================
GRequest::GRequest(const std::string& _msg) : GObject() {
    m_id = 0;
    m_uid = 0;
    m_module = "";
    m_method = "";
    m_msg = _msg;
    loadObj();
}
//===============================================
GRequest::~GRequest() {

}
//===============================================
void GRequest::loadObj() {
    if(m_msg == "") return;
    GCode lMsg(m_msg);
    m_module = lMsg.getModule();
    m_method = lMsg.getMethod();
    std::string lPseudo = lMsg.getParam("pseudo");
    m_uid = GUser(lPseudo).getId();
    GLOGT(eGMSG, ""
            "module........: %s\n"
            "method........: %s\n"
            "pseudo........: %s\n"
            "uid...........: %d"
            "", m_module.c_str(), m_method.c_str(), lPseudo.c_str(), m_uid);
    loadId();
}
//===============================================
void GRequest::loadId() {
    if(m_module == "") return;
    if(m_method == "") return;
    if(!m_uid) return;
    std::string lId = GMySQL().readData(sformat(""
            " select r._id "
            " from request r, user u "
            " where r._u_id = u._id "
            " and r._module = '%s' "
            " and r._method = '%s' "
            " and r._u_id = %d "
            "", m_module.c_str()
            , m_method.c_str()
            , m_uid
    ));
    if(lId != "") m_id = std::stoi(lId);
    GLOGT(eGINF, ""
            "id............: %d\n"
            "uid...........: %d"
            "", m_id, m_uid);
}
//===============================================
void GRequest::saveData() {
    if(!m_id) {
        insertData();
    }
    else {
        updateData();
    }
}
//===============================================
void GRequest::insertData() {
    if(!m_uid) return;
    GMySQL().execQuery(sformat(""
            " insert into request "
            " ( _u_id, _module, _method, _msg ) "
            " values ( %d, '%s', '%s', '%s' ) "
            "", m_uid
            , m_module.c_str()
            , m_method.c_str()
            , m_msg.c_str()
    ));
}
//===============================================
void GRequest::updateData() {
    if(!m_uid) return;
    GMySQL().execQuery(sformat(""
            " update request "
            " set _u_id = %d "
            " , _module = '%s' "
            " , _method = '%s' "
            " , _msg = '%s' "
            " where _id = %d "
            "", m_uid
            , m_module.c_str()
            , m_method.c_str()
            , m_msg.c_str()
            , m_id
    ));
}
//===============================================
