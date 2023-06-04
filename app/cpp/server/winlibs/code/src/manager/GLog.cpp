//===============================================
#include "GLog.h"
//===============================================
GLog::GLog() {

}
//===============================================
GLog::~GLog() {
    clear();
}
//===============================================
void GLog::clear() {
    for(int i = 0; i < m_map.size(); i++) {
        GLog* lObj = m_map[i];
        delete lObj;
    }
}
//===============================================
void GLog::setObj(const GLog& _obj) {
    m_type = _obj.m_type;
    m_side = _obj.m_side;
    m_msg = _obj.m_msg;
}
//===============================================
void GLog::addError(const GString& _msg) {
    GLog* lObj = new GLog;
    lObj->m_type = "error";
    lObj->m_side = "server_cpp";
    lObj->m_msg = _msg;
    m_map.push_back(lObj);
}
//===============================================
void GLog::addLog(const GString& _msg) {
    GLog* lObj = new GLog;
    lObj->m_type = "log";
    lObj->m_side = "server_cpp";
    lObj->m_msg = _msg;
    m_map.push_back(lObj);
}
//===============================================
void GLog::addData(const GString& _msg) {
    GLog* lObj = new GLog;
    lObj->m_type = "data";
    lObj->m_side = "server_cpp";
    lObj->m_msg = _msg;
    m_map.push_back(lObj);
}
//===============================================
void GLog::addLogs(const GLog& _obj) {
    for(int i = 0; i < _obj.m_map.size(); i++) {
        GLog* lObj = _obj.m_map[i];
        GLog* lNew = new GLog;
        lNew->setObj(*lObj);
        m_map.push_back(lNew);
    }
}
//===============================================
bool GLog::hasErrors() const {
    for(int i = 0; i < m_map.size(); i++) {
        GLog* lObj = m_map[i];
        if(lObj->m_type == "error") return true;
    }
    return false;
}
//===============================================
bool GLog::hasLogs() const {
    for(int i = 0; i < m_map.size(); i++) {
        GLog* lObj = m_map[i];
        if(lObj->m_type == "log") return true;
    }
    return false;
}
//===============================================
bool GLog::hasDatas() const {
    for(int i = 0; i < m_map.size(); i++) {
        GLog* lObj = m_map[i];
        if(lObj->m_type == "data") return true;
    }
    return false;
}
//===============================================
void GLog::print() const {
    for(int i = 0; i < m_map.size(); i++) {
        GLog* lObj = m_map[i];
        printf("[%-5s] : %s\n", lObj->m_type.c_str(), lObj->m_msg.c_str());
    }
}
//===============================================
