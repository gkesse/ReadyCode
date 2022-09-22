//===============================================
#include "GLog.h"
#include "GCode.h"
#include "GDate.h"
#include "GEnv.h"
#include "GFile.h"
#include "GPath.h"
#include "GShell.h"
#include "GString.h"
//===============================================
GLog* GLog::m_instance = 0;
//===============================================
GLog::GLog()
: GObject() {
    createDoms();
    m_file = 0;
    m_type = "";
    m_side = "";
    m_msg = "";
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
std::string GLog::serialize(const std::string& _code) const {
    GCode lDom;
    lDom.createDoc();
    lDom.addData(_code, "type", m_type);
    lDom.addData(_code, "side", m_side);
    lDom.addData(_code, "msg", m_msg);
    lDom.addData(_code, m_map);
    return lDom.toStringData();
}
//===============================================
void GLog::deserialize(const std::string& _data, const std::string& _code) {
    clearMap(m_map);
    GCode lDom;
    lDom.loadXml(_data);
    m_type = lDom.getItem(_code, "type");
    m_side = lDom.getItem(_code, "side");
    m_msg = lDom.getItem(_code, "msg");
    lDom.getItem(_code, m_map, this);
}
//===============================================
void GLog::createDoms() {
    m_dom.reset(new GCode);
    m_dom->loadFile(GRES("xml", "pad.xml"));
}
//===============================================
bool GLog::isDebug() const {
    return isDebug(GEnv().isTestEnv());
}
//===============================================
bool GLog::isDebug(bool _isTestEnv) const {
    if(_isTestEnv) return isTestLog();
    return isProdLog();
}
//===============================================
bool GLog::isFileLog() const {
    return isFileLog(GEnv().isTestEnv());
}
//===============================================
bool GLog::isFileLog(bool _isTestEnv) const {
    if(_isTestEnv) return isTestFileLog();
    return isProdFileLog();
}
//===============================================
bool GLog::isTestFileLog() const {
    bool lFileOn = (getItem("log", "test_file_on") == "1");
    return lFileOn;
}
//===============================================
bool GLog::isProdFileLog() const {
    bool lFileOn = (getItem("log", "prod_file_on") == "1");
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
    m_file = 0;
}
//===============================================
void GLog::catLogFile() {
    std::string lLogFile = GFile().getLogFullname();
    GFile lFileObj(lLogFile);
    std::string lData = sformat(""
            "Erreur le fichier log n'existe pas.\n"
            "fichier......: (%s)\n"
            "", lLogFile.c_str());
    if(lFileObj.existFile()) {
        lData = lFileObj.getContent();
    }
    printf("%s\n", lData.c_str());
}
//===============================================
void GLog::tailLogFile(bool _isTestEnv) {
    std::string lLogFile = GFile().getLogFullname(_isTestEnv);
    GFile lFileObj(lLogFile);
    std::string lData = sformat(""
            "Erreur le fichier log n'existe pas.\n"
            "fichier......: (%s)\n"
            "", lLogFile.c_str());
    if(lFileObj.existFile()) {
        GShell().tailFile(lLogFile);
    }
    else {
        printf("%s\n", lData.c_str());
    }
}
//===============================================
void GLog::addError(const char* _name, int _level, const char* _file, int _line, const char* _func, const std::string& _error) {
    traceLog(_name, _level, _file, _line, _func, _error);
    GLog* lLog = new GLog;
    lLog->m_type = "error";
    lLog->m_side = "server";
    lLog->m_msg = _error;
    m_map.push_back(lLog);
}
//===============================================
void GLog::addLog(const char* _name, int _level, const char* _file, int _line, const char* _func, const std::string& _log) {
    traceLog(_name, _level, _file, _line, _func, _log);
    GLog* lLog = new GLog;
    lLog->m_type = "log";
    lLog->m_side = "server";
    lLog->m_msg = _log;
    m_map.push_back(lLog);
}
//===============================================
void GLog::showErrors() {
    showErrors(isDebug(), isFileLog());
}
//===============================================
void GLog::showErrors(bool _isDebug, bool _isFileLog) {
    if(!_isDebug) return;
    if(!hasErrors()) return;
    std::string lErrors = "";
    for(int i = 0; i < (int)m_map.size(); i++) {
        GLog* lLog = (GLog*)m_map.at(i);
        if(lLog->m_type == "error") {
            if(i != 0) lErrors += "\n";
            lErrors += lLog->m_msg;
        }
    }
    GLOGT(eGERR, "%s", lErrors.c_str());
}
//===============================================
bool GLog::hasErrors() const {
    for(int i = 0; i < (int)m_map.size(); i++) {
        GLog* lLog = (GLog*)m_map.at(i);
        if(lLog->m_type == "error") {
            return true;
        }
    }
    return false;
}
//===============================================
bool GLog::hasLogs() const {
    for(int i = 0; i < (int)m_map.size(); i++) {
        GLog* lLog = (GLog*)m_map.at(i);
        if(lLog->m_type == "log") {
            return true;
        }
    }
    return false;
}
//===============================================
void GLog::clearErrors() {
    for(int i = 0; i < (int)m_map.size(); i++) {
        GLog* lLog = (GLog*)m_map.at(i);
        if(lLog->m_type == "error") {
            delete lLog;
            m_map.erase (m_map.begin() + i);
        }
    }
}
//===============================================
void GLog::clearLogs() {
    for(int i = 0; i < (int)m_map.size(); i++) {
        GLog* lLog = (GLog*)m_map.at(i);
        if(lLog->m_type == "log") {
            delete lLog;
            m_map.erase (m_map.begin() + i);
        }
    }
}
//===============================================
void GLog::loadErrors(const char* _name, int _level, const char* _file, int _line, const char* _func, const std::string& _data) {
    deserialize(_data);
    showErrors();
}
//===============================================
void GLog::writeLog(const char* _name, int _level, const char* _file, int _line, const char* _func, const std::string& _log) {
    writeLog(_name, _level, _file, _line, _func, isDebug(), isFileLog(), _log);
}
//===============================================
void GLog::writeLog(const char* _name, int _level, const char* _file, int _line, const char* _func, bool _isDebug, bool _isFileLog, const std::string& _log) {
    if(_level == 0) return;
    if(!_isDebug) return;
    fprintf(getOutput(_isFileLog), "%s\n", _log.c_str());
    closeLogFile();
}
//===============================================
void GLog::traceLog(const char* _name, int _level, const char* _file, int _line, const char* _func, const std::string& _data) {
    traceLog(_name, _level, _file, _line, _func, isDebug(), isFileLog(), _data);
}
//===============================================
void GLog::traceLog(const char* _name, int _level, const char* _file, int _line, const char* _func, bool _isDebug, bool _isFileLog, const std::string& _data) {
    if(_level == 0) return;
    if(!_isDebug) return;
    std::string lDate = GDate().getDate(GDate().getDateTimeLogFormat());
    fprintf(getOutput(_isFileLog), "===> [%s] : %d : %s : %s : [%d] : %s :\n%s\n", _name, _level, lDate.c_str(), _file, _line, _func, _data.c_str());
    closeLogFile();
}
//===============================================
const char* GLog::toString(bool _data) const {
    if(_data) return "true";
    return "false";
}
//===============================================
const char* GLog::toString(const GString& _data) const {
    return _data.c_str();
}
//===============================================
std::string GLog::toString(const std::vector<std::string>& _data) const {
    std::string lData = "";
    for(size_t i = 0; i < _data.size(); i++) {
        if(i != 0) lData += "\n";
        lData += _data.at((int)i);
    }
    return lData;
}
//===============================================
std::string GLog::toString(const std::vector<std::vector<std::string>>& _data) const {
    std::string lData = "";
    for(size_t i = 0; i < _data.size(); i++) {
        if(i != 0) lData += "\n";
        std::vector<std::string> lDataRow = _data.at((int)i);
        for(size_t j = 0; j < lDataRow.size(); j++) {
            if(j != 0) lData += "\n";
            lData += lDataRow.at((int)j);
        }
    }
    return lData;
}
//===============================================
