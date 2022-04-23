//===============================================
#include "GRequest.h"
#include "GLog.h"
#include "GFormat.h"
#include "GMySQL.h"
#include "GCode.h"
#include "GUser.h"
#include "GBase64.h"
#include "GSocket.h"
//===============================================
GRequest::GRequest() : GModule() {
    m_id = 0;
    m_uid = 0;
    m_module = "";
    m_method = "";
    m_msg = "";
}
//===============================================
GRequest::GRequest(const std::string& _msg) : GModule() {
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
void GRequest::onModule(GSocket* _client) {
    std::string lMethod = _client->getReq()->getMethod();
    //===============================================
    // method
    //===============================================
    if(lMethod == "get_req_list") {
        onGetRequestList(_client);
    }
    //===============================================
    // unknown
    //===============================================
    else {
        onMethodUnknown(_client);
    }
}
//===============================================
void GRequest::onGetRequestList(GSocket* _client) {
    std::shared_ptr<GCode>& lReq = _client->getReq();
    std::string lPseudo = lReq->getSession("pseudo");
    m_uid = GUser(lPseudo).getId();
    GLOGT(eGMSG, ""
            "pseudo.......: %s\n"
            "uid..........: %d\n"
            "", lPseudo.c_str()
            , m_uid
    );
    loadRequestList(_client);
}
//===============================================
void GRequest::loadObj() {
    if(m_msg == "") return;
    GCode lMsg(m_msg);
    m_module = lMsg.getModule();
    m_method = lMsg.getMethod();
    std::string lPseudo = lMsg.getSession("pseudo");
    m_uid = GUser(lPseudo).getId();
    GLOGT(eGMSG, ""
            "module.......: %s\n"
            "method.......: %s\n"
            "pseudo.......: %s\n"
            "uid..........: %d\n"
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
            "id...........: %d\n"
            "uid..........: %d\n"
            "", m_id, m_uid);
}
//===============================================
void GRequest::loadRequestList(GSocket* _client) {
    if(!m_uid) return;
    std::vector<std::vector<std::string>> lReq = GMySQL().readMap(sformat(""
            " select r._module, r._method, r._msg "
            " from request r, user u "
            " where r._u_id = u._id "
            " and u._id = %d "
            "", m_uid
    ));

    std::shared_ptr<GCode>& lRes = _client->getResponse();

    for(int i = 0; i < (int)lReq.size(); i++) {
        std::vector<std::string> lDataRow = lReq.at(i);
        int j = 0;
        GRequest lReqObj;
        lReqObj.m_module = lDataRow.at(j++);
        lReqObj.m_method = lDataRow.at(j++);
        lReqObj.m_msg = lDataRow.at(j++);

        GLOGT(eGOFF, ""
                "i............: %d\n"
                "module.......: %s\n"
                "method.......: %s\n"
                "msg..........: %s\n"
                "", i
                , lReqObj.m_module.c_str()
                , lReqObj.m_method.c_str()
                , lReqObj.m_msg.c_str()
        );

        lRes->createMap("req", "module", lReqObj.m_module, i);
        lRes->createMap("req", "method", lReqObj.m_method, i);
        lRes->createMap("req", "msg", lReqObj.m_msg, i, true);
    }
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
