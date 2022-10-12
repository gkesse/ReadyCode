//===============================================
#include "GLog.h"
#include "GShell.h"
#include "GCode.h"
#include "GDate.h"
#include "GEnv.h"
#include "GFile.h"
#include "GPath.h"
//===============================================
GLog* GLog::m_instance = 0;
//===============================================
GLog::GLog()
: GObject() {
    createDoms();
    initLog();
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
GString GLog::serialize() const {
    GCode lDom;
    lDom.createDoc();
    lDom.addData(m_codeName, "type", m_type);
    lDom.addData(m_codeName, "side", m_side);
    lDom.addData(m_codeName, "msg", m_msg);
    lDom.addData(m_codeName, m_map);
    return lDom.toString();
}
//===============================================
bool GLog::deserialize(const GString& _data) {
    clearMap(m_map);
    GCode lDom;
    lDom.loadXml(_data);
    m_type = lDom.getData(m_codeName, "type");
    m_side = lDom.getData(m_codeName, "side");
    m_msg = lDom.getData(m_codeName, "msg");
    lDom.getData(m_codeName, m_map, this);
    return true;
}
//===============================================
void GLog::initLog() {
    m_file = 0;

    m_isTestEnv     = GEnv().isTestEnv();
    m_isTestLog     = (m_dom->getData("log", "test_on") == "1");
    m_isProdLog     = (m_dom->getData("log", "prod_on") == "1");
    m_isTestFile    = (m_dom->getData("log", "test_file_on") == "1");
    m_isProdFile    = (m_dom->getData("log", "prod_file_on") == "1");
    m_isDebug       = (m_isTestEnv ? m_isTestLog : m_isProdLog);
    m_isFileLog     = (m_isTestEnv ? m_isTestFile : m_isProdFile);

    m_tmpPath       = GEnv().getTmpDir();
    m_currentDate   = GDate().getDateFileFormat();
    m_logTestFile   = GFORMAT("%s/log_test_%s.txt", m_tmpPath.c_str(), m_currentDate.c_str());
    m_logProdFile   = GFORMAT("%s/log_prod_%s.txt", m_tmpPath.c_str(), m_currentDate.c_str());
    m_logFilename   = (m_isTestEnv ? m_logTestFile : m_logProdFile);
}
//===============================================
FILE* GLog::getOutput() {
    FILE* lFile = stdout;
    if(m_isFileLog) lFile = getOutputFile();
    return lFile;
}
//===============================================
FILE* GLog::getOutputFile() {
    FILE* lFile = fopen(m_logFilename.c_str(), "a+");
    m_file = lFile;
    return lFile;
}
//===============================================
void GLog::closeLogFile() {
    if(!m_file) return;
    fclose(m_file);
    m_file = 0;
}
//===============================================
void GLog::catLogFile() {
    GFile lFileObj(m_logFilename);
    GString lData = GFORMAT("Le fichier log n'existe pas :\n(%s)", m_logFilename.c_str());
    if(lFileObj.existFile()) {
        lData = lFileObj.getContent();
    }
    printf("%s\n", lData.c_str());
}
//===============================================
void GLog::tailLogFile(bool _isTestEnv) {
    GFile lFileObj(m_logFilename);
    GString lData = GFORMAT("Le fichier log n'existe pas :\n(%1)", m_logFilename.c_str());
    if(lFileObj.existFile()) {
        GShell().tailFile(m_logFilename);
    }
    else {
        printf("%s\n", lData.c_str());
    }
}
//===============================================
void GLog::addError(const char* _name, int _level, const char* _file, int _line, const char* _func, const GString& _error) {
    traceLog(_name, _level, _file, _line, _func, _error);
    GLog* lLog = new GLog;
    lLog->m_type = "error";
    lLog->m_side = "server";
    lLog->m_msg = _error;
    m_map.push_back(lLog);
}
//===============================================
void GLog::addLog(const char* _name, int _level, const char* _file, int _line, const char* _func, const GString& _log) {
    traceLog(_name, _level, _file, _line, _func, _log);
    GLog* lLog = new GLog;
    lLog->m_type = "log";
    lLog->m_side = "server";
    lLog->m_msg = _log;
    m_map.push_back(lLog);
}
//===============================================
void GLog::showErrors() {
    if(!m_isDebug) return;
    if(!hasErrors()) return;
    GString lErrors = "";
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
void GLog::clearMaps() {
    clearMap(m_map);
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
void GLog::loadErrors(const char* _name, int _level, const char* _file, int _line, const char* _func, const GString& _data) {
    deserialize(_data);
    showErrors();
}
//===============================================
void GLog::writeLog(const char* _name, int _level, const char* _file, int _line, const char* _func, const GString& _log) {
    if(_level == 0) return;
    if(!m_isDebug) return;
    fprintf(getOutput(), "%s\n", _log.c_str());
    closeLogFile();
}
//===============================================
void GLog::traceLog(const char* _name, int _level, const char* _file, int _line, const char* _func, const GString& _data) {
    if(_level == 0) return;
    if(!m_isDebug) return;
    GString lDate = GDate().getDate(GDate().getDateTimeLogFormat());
    fprintf(getOutput(), "===> [%s] : %d : %s : %s : [%d] : %s :\n%s\n", _name, _level, lDate.c_str(), _file, _line, _func, _data.c_str());
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
GString GLog::toString(const std::vector<GString>& _data) const {
    GString lData = "";
    for(size_t i = 0; i < _data.size(); i++) {
        if(i != 0) lData += "\n";
        lData += _data.at((int)i);
    }
    return lData;
}
//===============================================
GString GLog::toString(const std::vector<std::vector<GString>>& _data) const {
    GString lData = "";
    for(size_t i = 0; i < _data.size(); i++) {
        if(i != 0) lData += "\n";
        std::vector<GString> lDataRow = _data.at((int)i);
        for(size_t j = 0; j < lDataRow.size(); j++) {
            if(j != 0) lData += "\n";
            lData += lDataRow.at((int)j);
        }
    }
    return lData;
}
//===============================================
