//===============================================
#include "GLog.h"
#include "GCode.h"
#include "GFormat.h"
#include "GDate.h"
#include "GEnv.h"
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
bool GLog::isDebug() const {
    GEnv lEnvObj;
    if(!lEnvObj.isTestEnv()) return false;
    return true;
}
//===============================================
FILE* GLog::getOutput() const {
    return stdout;
}
//===============================================
FILE* GLog::getFileOutput() const {
    char* lFilename =
    FILE* lFile = fopen()
    return stdout;
}
//===============================================
void GLog::addError(const std::string& _error) {
    m_errors.push_back(_error);
}
//===============================================
void GLog::showError() {
    if(!isDebug()) return;
    if(!hasError()) return;
    std::string lErrors = "";
    for(int i = 0; i < m_errors.size(); i++) {
        lErrors += m_errors.at(i);
        lErrors += "\n";
    }
    fprintf(getOutput(), "%s", lErrors.c_str());
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
    if(!isDebug()) return;
    fprintf(getOutput(), "===>\n");
    fprintf(getOutput(), "%s\n", _log.c_str());
}
//===============================================
void GLog::writeLog2(const char* _name, int _level, const char* _file, int _line, const char* _func, const std::string& _data) {
    GDate lDateObj;
    if(!isDebug()) return;
    std::string lDate = lDateObj.getDate(lDateObj.getDateTimeLogFormat());
    if(_data == "") {
        fprintf(getOutput(), "===> [%-10s] : %d : %s : %s : %d : %s :\n", _name, _level, lDate.c_str(), _file, _line, _func);
    }
    else {
        fprintf(getOutput(), "===> [%-10s] : %d : %s : %s : %d : %s :\n%s\n", _name, _level, lDate.c_str(), _file, _line, _func, _data.c_str());
    }
}
//===============================================
