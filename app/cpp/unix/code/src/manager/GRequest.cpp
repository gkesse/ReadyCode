//===============================================
#include "GRequest.h"
#include "GLog.h"
#include "GFormat.h"
#include "GMySQL.h"
#include "GCode.h"
//===============================================
GRequest::GRequest() : GObject() {
    m_id = 0;
    m_module = "";
    m_method = "";
    m_msg = "";
}
//===============================================
GRequest::GRequest(const std::string& _msg) : GObject() {
    m_id = 0;
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
    loadId();
}
//===============================================
void GRequest::loadId() {
    if(m_module == "") return;
    if(m_method == "") return;
    std::string lId = GMySQL().readData(sformat(""
            " select _id "
            " from request "
            " where _module = '%s' "
            " and _method = '%s' "
            "", m_module.c_str()
            , m_method.c_str()
    ));
    if(lId != "") m_id = std::stoi(lId);
    GLOGT(eGINF, "m_id : %d", m_id);
}
//===============================================
void GRequest::saveData() {
    if(m_id == 0) {
        insertData();
    }
    else {
        updateData();
    }
}
//===============================================
void GRequest::insertData() {
    GMySQL().execQuery(sformat(""
            " insert into request "
            " ( _module, _method, _msg ) "
            " values ( '%s', '%s', '%s' ) "
            "", m_module.c_str()
            , m_method.c_str()
            , m_msg.c_str()
    ));
}
//===============================================
void GRequest::updateData() {
    GMySQL().execQuery(sformat(""
            " update request "
            " set _module = '%s' "
            " , _method = '%s' "
            " , _msg = '%s' "
            " where _id = %d "
            "", m_module.c_str()
            , m_method.c_str()
            , m_msg.c_str()
            , m_id
    ));
}
//===============================================
