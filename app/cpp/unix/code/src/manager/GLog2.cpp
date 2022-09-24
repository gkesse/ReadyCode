//===============================================
#include "GLog2.h"
#include "GCode2.h"
#include "GDate.h"
#include "GEnv.h"
#include "GFile2.h"
#include "GPath.h"
#include "GShell2.h"
//===============================================
GLog2* GLog2::m_instance = 0;
//===============================================
GLog2::GLog2()
: GObject() {
    createDoms();
    m_file = 0;
}
//===============================================
GLog2::~GLog2() {

}
//===============================================
GLog2* GLog2::Instance() {
    if(m_instance == 0) {
        m_instance = new GLog2;
    }
    return m_instance;
}
//===============================================
GString2 GLog2::serialize(const GString2& _code) const {
    GCode2 lDom;
    lDom.createDoc();
    lDom.addData(_code, "type", m_type);
    lDom.addData(_code, "side", m_side);
    lDom.addData(_code, "msg", m_msg);
    lDom.addData(_code, m_map);
    return lDom.toString();
}
//===============================================
void GLog2::deserialize(const GString2& _data, const GString2& _code) {
    clearMap(m_map);
    GCode2 lDom;
    lDom.loadXml(_data);
    m_type = lDom.getData(_code, "type");
    m_side = lDom.getData(_code, "side");
    m_msg = lDom.getData(_code, "msg");
    lDom.getData(_code, m_map, this);
}
//===============================================
bool GLog2::isDebug() const {
    return isDebug(GEnv().isTestEnv());
}
//===============================================
bool GLog2::isDebug(bool _isTestEnv) const {
    if(_isTestEnv) return isTestLog();
    return isProdLog();
}
//===============================================
bool GLog2::isFileLog() const {
    return isFileLog(GEnv().isTestEnv());
}
//===============================================
bool GLog2::isFileLog(bool _isTestEnv) const {
    if(_isTestEnv) return isTestFileLog();
    return isProdFileLog();
}
//===============================================
bool GLog2::isTestFileLog() const {
    bool lFileOn = (m_dom->getData("log", "test_file_on") == "1");
    return lFileOn;
}
//===============================================
bool GLog2::isProdFileLog() const {
    bool lFileOn = (m_dom->getData("log", "prod_file_on") == "1");
    return lFileOn;
}
//===============================================
bool GLog2::isTestLog() const {
    bool lLogOn = (m_dom->getData("log", "test_on") == "1");
    return lLogOn;
}
//===============================================
bool GLog2::isProdLog() const {
    bool lLogOn = (m_dom->getData("log", "prod_on") == "1");
    return lLogOn;
}
//===============================================
FILE* GLog2::getOutput(bool _isFileLog) {
    FILE* lFile = stdout;
    if(_isFileLog) lFile = getOutputFile();
    return lFile;
}
//===============================================
FILE* GLog2::getOutputFile() {
    FILE* lFile = GFile2().openLogFile();
    m_file = lFile;
    return lFile;
}
//===============================================
void GLog2::closeLogFile() {
    if(!m_file) return;
    GFile2().closeFile(m_file);
    m_file = 0;
}
//===============================================
void GLog2::catLogFile() {
    GString2 lLogFile = GFile2().getLogFullname();
    GFile2 lFileObj(lLogFile);
    GString2 lData = sformat(""
            "Erreur le fichier log n'existe pas.\n"
            "fichier......: (%s)\n"
            "", lLogFile.c_str());
    if(lFileObj.existFile()) {
        lData = lFileObj.getContent();
    }
    printf("%s\n", lData.c_str());
}
//===============================================
void GLog2::tailLogFile(bool _isTestEnv) {
    GString2 lLogFile = GFile2().getLogFullname(_isTestEnv);
    GFile2 lFileObj(lLogFile);
    GString2 lData = sformat(""
            "Erreur le fichier log n'existe pas.\n"
            "fichier......: (%s)\n"
            "", lLogFile.c_str());
    if(lFileObj.existFile()) {
        GShell2().tailFile(lLogFile);
    }
    else {
        printf("%s\n", lData.c_str());
    }
}
//===============================================
void GLog2::addError(const char* _name, int _level, const char* _file, int _line, const char* _func, const GString2& _error) {
    traceLog(_name, _level, _file, _line, _func, _error);
    GLog2* lLog = new GLog2;
    lLog->m_type = "error";
    lLog->m_side = "server";
    lLog->m_msg = _error;
    m_map.push_back(lLog);
}
//===============================================
void GLog2::addLog(const char* _name, int _level, const char* _file, int _line, const char* _func, const GString2& _log) {
    traceLog(_name, _level, _file, _line, _func, _log);
    GLog2* lLog = new GLog2;
    lLog->m_type = "log";
    lLog->m_side = "server";
    lLog->m_msg = _log;
    m_map.push_back(lLog);
}
//===============================================
void GLog2::showErrors() {
    showErrors(isDebug(), isFileLog());
}
//===============================================
void GLog2::showErrors(bool _isDebug, bool _isFileLog) {
    if(!_isDebug) return;
    if(!hasErrors()) return;
    GString2 lErrors = "";
    for(int i = 0; i < (int)m_map.size(); i++) {
        GLog2* lLog = (GLog2*)m_map.at(i);
        if(lLog->m_type == "error") {
            if(i != 0) lErrors += "\n";
            lErrors += lLog->m_msg;
        }
    }
    GLOGT(eGERR, "%s", lErrors.c_str());
}
//===============================================
bool GLog2::hasErrors() const {
    for(int i = 0; i < (int)m_map.size(); i++) {
        GLog2* lLog = (GLog2*)m_map.at(i);
        if(lLog->m_type == "error") {
            return true;
        }
    }
    return false;
}
//===============================================
bool GLog2::hasLogs() const {
    for(int i = 0; i < (int)m_map.size(); i++) {
        GLog2* lLog = (GLog2*)m_map.at(i);
        if(lLog->m_type == "log") {
            return true;
        }
    }
    return false;
}
//===============================================
void GLog2::clearErrors() {
    for(int i = 0; i < (int)m_map.size(); i++) {
        GLog2* lLog = (GLog2*)m_map.at(i);
        if(lLog->m_type == "error") {
            delete lLog;
            m_map.erase (m_map.begin() + i);
        }
    }
}
//===============================================
void GLog2::clearLogs() {
    for(int i = 0; i < (int)m_map.size(); i++) {
        GLog2* lLog = (GLog2*)m_map.at(i);
        if(lLog->m_type == "log") {
            delete lLog;
            m_map.erase (m_map.begin() + i);
        }
    }
}
//===============================================
void GLog2::loadErrors(const char* _name, int _level, const char* _file, int _line, const char* _func, const GString2& _data) {
    deserialize(_data);
    showErrors();
}
//===============================================
void GLog2::writeLog(const char* _name, int _level, const char* _file, int _line, const char* _func, const GString2& _log) {
    writeLog(_name, _level, _file, _line, _func, isDebug(), isFileLog(), _log);
}
//===============================================
void GLog2::writeLog(const char* _name, int _level, const char* _file, int _line, const char* _func, bool _isDebug, bool _isFileLog, const GString2& _log) {
    if(_level == 0) return;
    if(!_isDebug) return;
    fprintf(getOutput(_isFileLog), "%s\n", _log.c_str());
    closeLogFile();
}
//===============================================
void GLog2::traceLog(const char* _name, int _level, const char* _file, int _line, const char* _func, const GString2& _data) {
    traceLog(_name, _level, _file, _line, _func, isDebug(), isFileLog(), _data);
}
//===============================================
void GLog2::traceLog(const char* _name, int _level, const char* _file, int _line, const char* _func, bool _isDebug, bool _isFileLog, const GString2& _data) {
    if(_level == 0) return;
    if(!_isDebug) return;
    GString2 lDate = GDate().getDate(GDate().getDateTimeLogFormat());
    fprintf(getOutput(_isFileLog), "===> [%s] : %d : %s : %s : [%d] : %s :\n%s\n", _name, _level, lDate.c_str(), _file, _line, _func, _data.c_str());
    closeLogFile();
}
//===============================================
const char* GLog2::toString(bool _data) const {
    if(_data) return "true";
    return "false";
}
//===============================================
const char* GLog2::toString(const GString2& _data) const {
    return _data.c_str();
}
//===============================================
GString2 GLog2::toString(const std::vector<GString2>& _data) const {
    GString2 lData = "";
    for(size_t i = 0; i < _data.size(); i++) {
        if(i != 0) lData += "\n";
        lData += _data.at((int)i);
    }
    return lData;
}
//===============================================
GString2 GLog2::toString(const std::vector<std::vector<GString2>>& _data) const {
    GString2 lData = "";
    for(size_t i = 0; i < _data.size(); i++) {
        if(i != 0) lData += "\n";
        std::vector<GString2> lDataRow = _data.at((int)i);
        for(size_t j = 0; j < lDataRow.size(); j++) {
            if(j != 0) lData += "\n";
            lData += lDataRow.at((int)j);
        }
    }
    return lData;
}
//===============================================
