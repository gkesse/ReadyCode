//===============================================
#include "GLog.h"
#include "GCode.h"
#include "GFormat.h"
#include "GDate.h"
#include "GEnv.h"
#include "GFile.h"
#include "GPath.h"
//===============================================
GLog* GLog::m_instance = 0;
//===============================================
GLog::GLog() : GObject() {
    createDoms();
    m_file = 0;
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
void GLog::createDoms() {
    m_dom.reset(new GXml);
    m_dom->loadXmlFile(GRES("xml", "pad.xml"));
    m_dom->createXPath();
}
//===============================================
bool GLog::isDebug() const {
    if(GEnv().isProdEnv()) {
        if(isProdLog()) return true;
    }
    else {
        if(isTestLog()) return true;
    }
    return false;
}
//===============================================
bool GLog::isFileLog() const {
    bool lFileOn = (getItem("log", "file_on") == "1");
    return lFileOn;
}
//===============================================
bool GLog::isTestLog() const {
    bool lLogOn = (getItem("log", "test_on") == "1");
    return lLogOn;
}
//===============================================
bool GLog::isProdLog() const {
    bool lLogOn = (getItem("log", "prod_on") == "1");
    return lLogOn;
}
//===============================================
FILE* GLog::getOutput(bool _isFileLog) {
    FILE* lFile = stdout;
    if(_isFileLog) lFile = getOutputFile();
    return lFile;
}
//===============================================
FILE* GLog::getOutputFile() {
    FILE* lFile = GFile().openLogFile();
    m_file = lFile;
    return lFile;
}
//===============================================
void GLog::closeLogFile() {
    if(!m_file) return;
    GFile().closeFile(m_file);
}
//===============================================
void GLog::showLogFile() {
    std::string lLogFile = GFile().getLogFile();
    GFile lFileObj(lLogFile);
    std::string lData = sformat("Erreur le fichier log n'existe pas.\n"
            "- fichier.....: %s", lLogFile.c_str());
    if(lFileObj.existFile()) {
        std::string lData = lFileObj.getContent();
    }
    printf("%s\n", lData.c_str());
}
//===============================================
void GLog::addError(const std::string& _error) {
    m_errors.push_back(_error);
}
//===============================================
void GLog::showError() {
    showError(isDebug(), isFileLog());
}
//===============================================
void GLog::showError(bool _isDebug, bool _isFileLog) {
    if(!_isDebug) return;
    if(!hasError()) return;
    std::string lErrors = "";
    for(int i = 0; i < m_errors.size(); i++) {
        lErrors += m_errors.at(i);
        lErrors += "\n";
    }
    fprintf(getOutput(_isFileLog), "%s", lErrors.c_str());
    m_errors.clear();
    closeLogFile();
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
    writeLog(isDebug(), isFileLog(), _log);
}
//===============================================
void GLog::writeLog(bool _isDebug, bool _isFileLog, const std::string _log) {
    if(!_isDebug) return;
    fprintf(getOutput(_isFileLog), "===>\n");
    fprintf(getOutput(_isFileLog), "%s\n", _log.c_str());
    closeLogFile();
}
//===============================================
void GLog::traceLog(const char* _name, int _level, const char* _file, int _line, const char* _func, const std::string& _data) {
    traceLog(_name, _level, _file, _line, _func, isDebug(), isFileLog(), _data);
}
//===============================================
void GLog::traceLog(const char* _name, int _level, const char* _file, int _line, const char* _func, bool _isDebug, bool _isFileLog, const std::string& _data) {
    if(!_isDebug) return;
    std::string lDate = GDate().getDate(GDate().getDateTimeLogFormat());
    if(_data == "") {
        fprintf(getOutput(_isFileLog), "===> [%-10s] : %d : %s : %s : %d : %s :\n", _name, _level, lDate.c_str(), _file, _line, _func);
    }
    else {
        fprintf(getOutput(_isFileLog), "===> [%-10s] : %d : %s : %s : %d : %s :\n%s\n", _name, _level, lDate.c_str(), _file, _line, _func, _data.c_str());
    }
    closeLogFile();
}
//===============================================
