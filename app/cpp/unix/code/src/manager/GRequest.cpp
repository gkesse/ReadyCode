//===============================================
#include "GRequest.h"
#include "GLog.h"
#include "GFormat.h"
#include "GMySQL.h"
#include "GCode.h"
#include "GUser.h"
#include "GBase64.h"
#include "GSocket.h"
#include "GString.h"
//===============================================
GRequest::GRequest() : GModule() {
    m_id = 0;
    m_uid = 0;
    m_module = "";
    m_method = "";
    m_msg = "";
    m_dataOffset = 0;
    m_dataSize = 0;
    m_dataCount = 0;
}
//===============================================
GRequest::~GRequest() {

}
//===============================================
std::string GRequest::serialize() const {
    GCode lReq;
    lReq.createCode("user", "id", m_id);
    lReq.createCode("user", "data_count", m_dataCount);
    return lReq.toStringCode("user");
}
//===============================================
void GRequest::deserialize(const std::string& _req) {
    GCode lReq(_req);
    m_id = GString(lReq.getParam("id")).toInt();
    m_uid = GString(lReq.getSession("user_id")).toInt();
    m_module = lReq.getModule();
    m_method = lReq.getMethod();
    m_msg = _req;
    m_dataOffset = GString(lReq.getParam("data_offset")).toInt();
    m_dataSize = GString(lReq.getParam("data_size")).toInt();
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
void GRequest::onSaveRequest(GSocket* _client) {
    deserialize(_client->toReq());
    loadId();
    saveData();
    loadId();
    std::string lData = serialize();
    _client->addResponse(lData);
}
//===============================================
void GRequest::onGetRequestList(GSocket* _client) {
    deserialize(_client->toReq());
    loadRequestCount(_client);
    loadRequestList(_client);
    std::string lData = serialize();
    _client->addResponse(lData);
}
//===============================================
void GRequest::loadId() {
    if(!m_uid) return;
    if(m_module == "") return;
    if(m_method == "") return;

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

    m_id = GString(lId).toInt();
}
//===============================================
void GRequest::loadRequestCount(GSocket* _client) {
    if(!m_uid) return;
    std::string lData = GMySQL().readData(sformat(""
            " select count(*) "
            " from request r, user u "
            " where r._u_id = u._id "
            " and u._id = %d "
            "", m_uid
    ));
    int lCount = GString(lData).toInt();
    std::shared_ptr<GCode>& lRes = _client->getResponse();
    lRes->createCode("req", "data_count", lCount);
}
//===============================================
void GRequest::loadRequestList(GSocket* _client) {
    if(!m_uid) return;
    if(!m_dataSize) return;

    std::vector<std::vector<std::string>> lReq = GMySQL().readMap(sformat(""
            " select r._id, r._module, r._method, r._msg "
            " from request r, user u "
            " where r._u_id = u._id "
            " and u._id = %d "
            " and r._id > %d "
            " order by r._id "
            " limit %d "
            "", m_uid
            , m_dataOffset
            , m_dataSize
    ));

    std::shared_ptr<GCode>& lRes = _client->getResponse();

    for(int i = 0; i < (int)lReq.size(); i++) {
        std::vector<std::string> lDataRow = lReq.at(i);
        int j = 0;
        GRequest lReqObj;
        lReqObj.m_id = std::stoi(lDataRow.at(j++));
        lReqObj.m_module = lDataRow.at(j++);
        lReqObj.m_method = lDataRow.at(j++);
        lReqObj.m_msg = lDataRow.at(j++);

        lRes->createMap("req", "id", lReqObj.m_id, i);
        lRes->createMap("req", "module", lReqObj.m_module, i);
        lRes->createMap("req", "method", lReqObj.m_method, i);
        lRes->createMap("req", "msg", lReqObj.m_msg, i, true);
    }

    int i = 0;
    lRes->createMap("req/header", "header", "id", i++);
    lRes->createMap("req/header", "header", "module", i++);
    lRes->createMap("req/header", "header", "methode", i++);
    lRes->createMap("req/header", "header", "message", i++);
}
//===============================================
void GRequest::saveData() {
    insertData();
    updateData();
}
//===============================================
void GRequest::insertData() {
    if(m_id != 0) return;
    if(m_uid == 0) return;
    if(m_module == "") return;
    if(m_method == "") return;
    if(m_msg == "") return;

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
    if(m_id == 0) return;
    if(m_uid == 0) return;
    if(m_module == "") return;
    if(m_method == "") return;
    if(m_msg == "") return;

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
