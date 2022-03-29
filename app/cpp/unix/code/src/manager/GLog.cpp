//===============================================
#include "GLog.h"
#include "GCode.h"
#include "GFormat.h"
#include "GDate.h"
//===============================================
GLog* GLog::m_instance = 0;
//===============================================
GLog::GLog() : GObject() {

}
//===============================================
GLog::~GLog() {

}
//===============================================
GLog* GLog::Instance() {
    if(m_instance == 0) {
        m_instance = new GLog;
    }
    return m_instance;
}
//===============================================
void GLog::addError(const std::string& _error) {
    m_errors.push_back(_error);
}
//===============================================
void GLog::showError() {
    if(!hasError()) return;
    std::string lErrors = "";
    for(int i = 0; i < m_errors.size(); i++) {
        lErrors += m_errors.at(i);
        lErrors += "\n";
    }
    printf("%s", lErrors.c_str());
    m_errors.clear();
}
//===============================================
bool GLog::hasError() {
    bool lError = !m_errors.empty();
    return lError;
}
//===============================================
void GLog::clearErrors() {
    m_errors.clear();
}
//===============================================
void GLog::loadErrors(const std::string& _res) {
    GCode lRes;
    lRes.loadXmlData(_res);
    lRes.createXPath();
    int lCount = lRes.countItem("error", "msg");
    for(int i = 0; i < lCount; i++) {
        std::string lError = lRes.getItem("error", i, "msg");
        GERROR("%s", lError.c_str());
    }
}
//===============================================
std::vector<std::string>& GLog::getErrors() {
    return m_errors;
}
//===============================================
void GLog::writeLog(const std::string _log) {
    printf("=====>\n");
    printf("%s\n", _log.c_str());
}
//===============================================
void GLog::writeLog2(const char* _name, int _level, const char* _file, int _line, const char* _func, const std::string& _data) {
    GDate lDateObj;
    const char* lDate = lDateObj.getDate(lDateObj.getDateTimeFormat()).c_str();
    if(_data == "") {
        fprintf(stdout, "=====> [%.-10s] : %d : %s : %d : %s :\n", _name, _level, _file, _line, _func);
    }
    else {
        fprintf(stdout, "=====> [%.-10s] : %d : %s : %d : %s :\n%s\n", _name, _level, _file, _line, _func, _data.c_str());
    }
}
//===============================================
