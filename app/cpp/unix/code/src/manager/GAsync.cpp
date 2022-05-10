//===============================================
#include "GAsync.h"
#include "GThread.h"
#include "GTimer.h"
#include "GCode.h"
#include "GString.h"
#include "GFormat.h"
#include "GMySQL.h"
//===============================================
GAsync::GAsync() : GObject() {
    m_id = 0;
    m_uid = 0;
    m_title = "";
    m_status = "";
    m_data = "";
    //
    m_thread = new GThread;
    m_socket = 0;
}
//===============================================
GAsync::~GAsync() {
    delete m_thread;
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
void GAsync::setSocket(GSocket* _socket) {
    m_socket = _socket;
}
//===============================================
GSocket* GAsync::getSocket() {
    return m_socket;
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
void GAsync::start(void* _onThreadCB, void* _params) {
    maj("En cours");
    m_thread->createThread(_onThreadCB, _params);
}
//===============================================
void GAsync::maj(const std::string& _status) {
    setStatus(_status);
    onMajAsync();
}
//===============================================
void GAsync::finish() {
    maj("Terminé");
}
//===============================================