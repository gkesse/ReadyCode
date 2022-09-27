//===============================================
#include "GRequest.h"
#include "GLog.h"
#include "GMySQL.h"
#include "GCode.h"
#include "GUser.h"
#include "GBase64.h"
#include "GSocket.h"
#include "GString.h"
//===============================================
GRequest::GRequest()
: GModule() {
    m_id = 0;
    m_msg = "";
    m_dataOffset = 0;
    m_dataSize = 0;
    m_dataCount = 0;
}
//===============================================
GRequest::~GRequest() {

}
//===============================================
std::string GRequest::serialize(const std::string& _code) const {
    GCode lDom;
    lDom.createDoc();
    lDom.addData(_code, "id", m_id);
    lDom.addData(_code, "data_count", m_dataCount);
    lDom.addData(_code, "data_offset", m_dataOffset);
    lDom.addData(_code, "data_size", m_dataSize);
    return lDom.toStringData();
}
//===============================================
void GRequest::deserialize(const std::string& _data, const std::string& _code) {
    GModule::deserialize(_data);
    GCode lDom;
    lDom.loadXml(_data);
    m_id = GString(lDom.getItem(_code, "id")).toInt();
    m_msg = _data;
    m_dataOffset = GString(lDom.getItem(_code, "data_offset")).toInt();
    m_dataSize = GString(lDom.getItem(_code, "data_size")).toInt();
}
//===============================================
void GRequest::onModule(GSocket* _client) {
    deserialize(_client->toReq());
    //===============================================
    // method
    //===============================================
    if(m_method == "get_req_list") {
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
    if(m_userId == 0) return;
    if(m_module == "") return;
    if(m_method == "") return;

    std::string lId = GMySQL().readData(GFORMAT(""
            " select r._id "
            " from request r, user u "
            " where r._u_id = u._id "
            " and r._module = '%s' "
            " and r._method = '%s' "
            " and r._u_id = %d "
            "", m_module.c_str()
            , m_method.c_str()
            , m_userId
    ));

    m_id = GString(lId).toInt();
}
//===============================================
void GRequest::loadRequestCount(GSocket* _client) {
    if(m_userId == 0) return;
    std::string lData = GMySQL().readData(GFORMAT(""
            " select count(*) "
            " from request r, user u "
            " where r._u_id = u._id "
            " and u._id = %d "
            "", m_userId
    ));
    int lCount = GString(lData).toInt();
}
//===============================================
void GRequest::loadRequestList(GSocket* _client) {
    if(m_userId == 0) return;
    if(!m_dataSize) return;

    std::vector<std::vector<std::string>> lReq = GMySQL().readMap(GFORMAT(""
            " select r._id, r._module, r._method, r._msg "
            " from request r, user u "
            " where r._u_id = u._id "
            " and u._id = %d "
            " and r._id > %d "
            " order by r._id "
            " limit %d "
            "", m_userId
            , m_dataOffset
            , m_dataSize
    ));

    for(int i = 0; i < (int)lReq.size(); i++) {
        std::vector<std::string> lDataRow = lReq.at(i);
        int j = 0;
        GRequest lReqObj;
        lReqObj.m_id = std::stoi(lDataRow.at(j++));
        lReqObj.m_module = lDataRow.at(j++);
        lReqObj.m_method = lDataRow.at(j++);
        lReqObj.m_msg = lDataRow.at(j++);

        //lRes->createMap("req", "id", lReqObj.m_id, i);
        //lRes->createMap("req", "module", lReqObj.m_module, i);
        //lRes->createMap("req", "method", lReqObj.m_method, i);
        //lRes->createMap("req", "msg", lReqObj.m_msg, i, true);
    }

    int i = 0;
    //lRes->createMap("req/header", "header", "id", i++);
    //lRes->createMap("req/header", "header", "module", i++);
    //lRes->createMap("req/header", "header", "methode", i++);
    //lRes->createMap("req/header", "header", "message", i++);
}
//===============================================
void GRequest::saveData() {
    insertData();
    updateData();
}
//===============================================
void GRequest::insertData() {
    if(m_id != 0) return;
    if(m_userId == 0) return;
    if(m_module == "") return;
    if(m_method == "") return;
    if(m_msg == "") return;

    GMySQL().execQuery(GFORMAT(""
            " insert into request "
            " ( _u_id, _module, _method, _msg ) "
            " values ( %d, '%s', '%s', '%s' ) "
            "", m_userId
            , m_module.c_str()
            , m_method.c_str()
            , m_msg.c_str()
    ));
}
//===============================================
void GRequest::updateData() {
    if(m_id == 0) return;
    if(m_userId == 0) return;
    if(m_module == "") return;
    if(m_method == "") return;
    if(m_msg == "") return;

    GMySQL().execQuery(GFORMAT(""
            " update request "
            " set _u_id = %d "
            " , _module = '%s' "
            " , _method = '%s' "
            " , _msg = '%s' "
            " where _id = %d "
            "", m_userId
            , m_module.c_str()
            , m_method.c_str()
            , m_msg.c_str()
            , m_id
    ));
}
//===============================================
