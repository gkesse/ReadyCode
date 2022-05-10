//===============================================
#include "GAsync.h"
#include "GThread.h"
#include "GTimer.h"
#include "GCode.h"
#include "GString.h"
#include "GFormat.h"
#include "GMySQL.h"
#include "GLog.h"
//===============================================
GAsync::GAsync() : GObject() {
    m_id = 0;
    m_uid = 0;
    m_title = "";
    m_status = "";
    m_data = "";
    //
    m_client = 0;
    m_running = true;
}
//===============================================
GAsync::~GAsync() {

}
//===============================================
std::string GAsync::serialize() const {
    GCode lReq;
    lReq.createCode("async", "id", m_id);
    lReq.createCode("async", "title", m_title);
    lReq.createCode("async", "status", m_status);
    lReq.createCode("async", "data", m_data);
    return lReq.toStringCode("async");
}
//===============================================
void GAsync::deserialize(const std::string& _req) {
    GCode lReq(_req);
    m_id = GString(lReq.getParam("id")).toInt();
    m_uid = GString(lReq.getSession("user_id")).toInt();
    m_title = lReq.getParam("title");
    m_status = lReq.getParam("status");
    m_data = lReq.getParam("data");
}
//===============================================
void GAsync::setTitle(const std::string& _title) {
    m_title = _title;
}
//===============================================
void GAsync::setStatus(const std::string& _status) {
    m_status = _status;
}
//===============================================
void GAsync::setData(const std::string& _data) {
    m_data = _data;
}
//===============================================
void GAsync::addData(const std::string& _data) {
    m_data += _data;
}
//===============================================
void GAsync::setClient(GSocket* _socket) {
    m_client = _socket;
}
//===============================================
GSocket* GAsync::getClient() {
    return m_client;
}
//===============================================
void GAsync::onMajAsync() {
    if(m_title == "") return;
    if(m_status == "") return;
    saveData();
}
//===============================================
void GAsync::saveData() {
    if(m_id == 0) {
        insertData();
    }
    else {
        updateData();
    }
}
//===============================================
void GAsync::insertData() {
    if(m_id != 0) return;
    if(m_uid == 0) return;
    if(m_title == "") return;
    if(m_status == "") return;

    m_id = GMySQL().execQuery(sformat(""
            " insert into async "
            " ( _u_id, _title, _status, _data ) "
            " values ( %d, '%s', '%s', '%s' ) "
            "", m_uid
            , m_title.c_str()
            , m_status.c_str()
            , m_data.c_str()
    )).getId();
}
//===============================================
void GAsync::updateData() {
    if(m_id == 0) return;
    if(m_uid == 0) return;
    if(m_title == "") return;
    if(m_status == "") return;

    GMySQL().execQuery(sformat(""
            " update async "
            " set _u_id = %d "
            " , _title = '%s' "
            " , _status = '%s' "
            " , _data = '%s' "
            " where _id = %d "
            "", m_uid
            , m_title.c_str()
            , m_status.c_str()
            , m_data.c_str()
            , m_id
    ));
}
//===============================================
void GAsync::exec(void* _onThreadCB, void* _params) {
    maj("En cours");
    GThread lThread;
    lThread.createThread(_onThreadCB, _params);
    while(m_running) {
        GLOGT(eGINF, "");
        pause();
    }
}
//===============================================
void GAsync::maj(const std::string& _status) {
    setStatus(_status);
    onMajAsync();
}
//===============================================
void GAsync::finish() {
    maj("Terminé");
    m_running = false;
}
//===============================================
