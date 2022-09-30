//===============================================
#include "GAsync.h"
#include "GThread.h"
#include "GTimer.h"
#include "GCode.h"
#include "GString.h"
#include "GMySQL.h"
#include "GLog.h"
//===============================================
GAsync::GAsync() : GModule() {
    m_id = 0;
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
GString GAsync::serialize(const GString& _code) const {
    GCode lReq;
    lReq.createDoc();
    lReq.addData(_code, "id", m_id);
    lReq.addData(_code, "title", m_title);
    lReq.addData(_code, "status", m_status);
    lReq.addData(_code, "data", m_data);
    return lReq.toStringCode("async");
}
//===============================================
void GAsync::deserialize(const GString& _req, const GString& _code) {
    GModule::deserialize(_req);
    GCode lReq;
    lReq.loadXml(_req);
    m_id = GString(lReq.getItem(_code, "id")).toInt();
    m_title = lReq.getItem(_code, "title");
    m_status = lReq.getItem(_code, "status");
    m_data = lReq.getItem(_code, "data");
}
//===============================================
void GAsync::setTitle(const GString& _title) {
    m_title = _title;
}
//===============================================
void GAsync::setStatus(const GString& _status) {
    m_status = _status;
}
//===============================================
void GAsync::setData(const GString& _data) {
    m_data = _data;
}
//===============================================
void GAsync::addData(const GString& _data) {
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
    if(m_userId == 0) return;
    if(m_title == "") return;
    if(m_status == "") return;

    m_id = GMySQL().execQuery(GFORMAT(""
            " insert into async "
            " ( _u_id, _title, _status, _data ) "
            " values ( %d, '%s', '%s', '%s' ) "
            "", m_userId
            , m_title.c_str()
            , m_status.c_str()
            , m_data.c_str()
    )).getId();
}
//===============================================
void GAsync::updateData() {
    if(m_id == 0) return;
    if(m_userId == 0) return;
    if(m_title == "") return;
    if(m_status == "") return;

    GMySQL().execQuery(GFORMAT(""
            " update async "
            " set _u_id = %d "
            " , _title = '%s' "
            " , _status = '%s' "
            " , _data = '%s' "
            " where _id = %d "
            "", m_userId
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
    lThread.joinThread(0);
}
//===============================================
void GAsync::maj(const GString& _status) {
    setStatus(_status);
    onMajAsync();
}
//===============================================
void GAsync::finish() {
    maj("Terminé");
    m_running = false;
}
//===============================================
