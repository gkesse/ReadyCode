//===============================================
#include "GLog.h"
#include "GCode.h"
#include "GLogUi.h"
//===============================================
GLog::GLog() {

}
//===============================================
GLog::~GLog() {
    clearMap();
}
//===============================================
GLog* GLog::clone() const {
    return new GLog;
}
//===============================================
void GLog::clearMap() {
    for(int i = 0; i < size(); i++) {
        GLog* lObj = m_map[i];
        delete lObj;
    }
    m_map.clear();
}
//===============================================
void GLog::setObj(const GLog& _obj) {
    m_type = _obj.m_type;
    m_side = _obj.m_side;
    m_msg = _obj.m_msg;
}
//===============================================
void GLog::loadFromMap(int i) {
    if(i >= 1 && i <= size()) {
        GLog* lObj = m_map[i - 1];
        setObj(*lObj);
    }
}
//===============================================
void GLog::loadToMap(int i) {
    if(i >= 1 && i <= size()) {
        GLog* lObj = m_map[i - 1];
        lObj->setObj(*this);
    }
}
//===============================================
void GLog::addError(const GString& _msg) {
    GLog* lObj = new GLog;
    lObj->m_type = "error";
    lObj->m_side = "client_cpp";
    lObj->m_msg = _msg;
    m_map.push_back(lObj);
}
//===============================================
void GLog::addErrorSrv(const GString& _msg) {
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
    lObj->m_side = "client_cpp";
    lObj->m_msg = _msg;
    m_map.push_back(lObj);
}
//===============================================
void GLog::addData(const GString& _msg) {
    GLog* lObj = new GLog;
    lObj->m_type = "data";
    lObj->m_side = "client_cpp";
    lObj->m_msg = _msg;
    m_map.push_back(lObj);
}
//===============================================
void GLog::addLogs(const GLog& _obj) {
    for(int i = 0; i < _obj.size(); i++) {
        GLog* lObj = _obj.m_map[i];
        GLog* lNew = new GLog;
        lNew->setObj(*lObj);
        m_map.push_back(lNew);
    }
}
//===============================================
bool GLog::hasErrors() const {
    for(int i = 0; i < size(); i++) {
        GLog* lObj = m_map[i];
        if(lObj->m_type == "error") return true;
    }
    return false;
}
//===============================================
bool GLog::hasLogs() const {
    for(int i = 0; i < size(); i++) {
        GLog* lObj = m_map[i];
        if(lObj->m_type == "log") return true;
    }
    return false;
}
//===============================================
bool GLog::hasDatas() const {
    for(int i = 0; i < size(); i++) {
        GLog* lObj = m_map[i];
        if(lObj->m_type == "data") return true;
    }
    return false;
}
//===============================================
bool GLog::hasServer() const {
    for(int i = 0; i < size(); i++) {
        GLog* lObj = m_map[i];
        if(lObj->m_side != "client_cpp") return true;
    }
    return false;
}
//===============================================
int GLog::size() const {
    return (int)m_map.size();
}
//===============================================
GString GLog::loadErrors() const {
    GString lData = "";
    for(int i = 0, j = 0; i < size(); i++) {
        GLog* lObj = m_map[i];
        if(lObj->m_type != "error") continue;
        if(j++ != 0) lData += "\n";
        lData += lObj->m_msg;
    }
    return lData;
}
//===============================================
GString GLog::loadDatas() const {
    GString lData = "";
    for(int i = 0, j = 0; i < size(); i++) {
        GLog* lObj = m_map[i];
        if(lObj->m_type != "data") continue;
        if(j++ != 0) lData += "\n";
        lData += lObj->m_msg;
    }
    return lData;
}
//===============================================
GString GLog::loadLogs() const {
    GString lData = "";
    for(int i = 0, j = 0; i < size(); i++) {
        GLog* lObj = m_map[i];
        if(lObj->m_type != "log") continue;
        if(j++ != 0) lData += "\n";
        lData += lObj->m_msg;
    }
    return lData;
}
//===============================================
GString GLog::loadLogsA() const {
    GString lData = "";
    for(int i = 0; i < size(); i++) {
        GLog* lObj = m_map[i];
        lData += sformat("[%-5s] : %s\n", lObj->m_type.c_str(), lObj->m_msg.c_str());
    }
    return lData;
}
//===============================================
int GLog::showErrors(QWidget* _parent) {
    int lResult = 0;
    if(hasErrors() && !hasDatas()) {
        GLogUi lLogUi(_parent);
        lLogUi.setParent(_parent);
        if(hasServer()) {
            lLogUi.setIcon(QMessageBox::Critical);
        }
        else {
            lLogUi.setIcon(QMessageBox::Warning);
        }
        lLogUi.setWindowTitle("Erreurs");
        lLogUi.setText(loadErrors().c_str());
        lResult = lLogUi.exec();
        clearMap();
    }
    return lResult;
}
//===============================================
int GLog::showDatas(QWidget* _parent) {
    int lResult = 0;
    if(hasDatas()) {
        GLogUi lLogUi(_parent);
        lLogUi.setParent(_parent);
        lLogUi.setIcon(QMessageBox::Information);
        lLogUi.setWindowTitle("Datas");
        lLogUi.setText(loadDatas().c_str());
        lResult = lLogUi.exec();
        clearMap();
    }
    return lResult;
}
//===============================================
int GLog::showLogs(QWidget* _parent) {
    int lResult = 0;
    if(hasLogs() && !hasDatas() && !hasLogs()) {
        GLogUi lLogUi(_parent);
        lLogUi.setParent(_parent);
        lLogUi.setIcon(QMessageBox::Information);
        lLogUi.setWindowTitle("Logs");
        lLogUi.setText(loadLogs().c_str());
        lResult = lLogUi.exec();
        clearMap();
    }
    return lResult;
}
//===============================================
int GLog::showLogsA(QWidget* _parent) {
    int lResult = 0;
    if(size()) {
        GLogUi lLogUi(_parent);
        lLogUi.setParent(_parent);
        lLogUi.setIcon(QMessageBox::Information);
        lLogUi.setWindowTitle("Messages");
        lLogUi.setText(loadLogsA().c_str());
        lResult = lLogUi.exec();
        clearMap();
    }
    return lResult;
}
//===============================================
int GLog::showLogsX(QWidget* _parent) {
    showErrors(_parent);
    showDatas(_parent);
    showLogs(_parent);
    return 0;
}
//===============================================
void GLog::print() const {
    for(int i = 0; i < size(); i++) {
        GLog* lObj = m_map[i];
        printf("[%-5s] : %s\n", lObj->m_type.c_str(), lObj->m_msg.c_str());
    }
}
//===============================================
GString GLog::serialize(const GString& _code) const {
    GCode lDom;
    lDom.createDoc();
    lDom.addData(_code, "type", m_type);
    lDom.addData(_code, "side", m_side);
    lDom.addData(_code, "msg", m_msg.toUtf8().toBase64());
    lDom.addLog(_code, m_map);
    return lDom.toString();
}
//===============================================
void GLog::deserialize(const GString& _data, const GString& _code) {
    GCode lDom;
    lDom.loadXml(_data);
    m_type = lDom.getData(_code, "type");
    m_side = lDom.getData(_code, "side");
    m_msg = lDom.getData(_code, "msg").fromBase64();
    lDom.getLog(_code, m_map, this);
}
//===============================================
