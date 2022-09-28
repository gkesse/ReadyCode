//===============================================
#include "GLog2.h"
#include "GMessageBox.h"
#include "GCode2.h"
#include "GDate2.h"
#include "GEnv2.h"
#include "GFile2.h"
#include "GPath2.h"
#include "GShell2.h"
//===============================================
GLog2* GLog2::m_instance = 0;
//===============================================
GLog2::GLog2()
: GObject2() {
    createDoms();
    m_type = "";
    m_side = "";
    m_msg = "";
    m_file = 0;
    m_isConnectionError = false;
    m_isClientSide = true;

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
GObject2* GLog2::clone() const {
    return new GLog2;
}
//===============================================
GString GLog2::serialize(const GString& _code) const {
    GCode2 lDom;
    lDom.createDoc();
    lDom.addData(_code, "type", m_type);
    lDom.addData(_code, "side", m_side);
    lDom.addData(_code, "msg", m_msg);
    lDom.addData(_code, m_map);
    return lDom.toString();
}
//===============================================
bool GLog2::deserialize(const GString& _data, const GString& _code) {
    GCode2 lDom;
    lDom.loadXml(_data);
    m_type = lDom.getData(_code, "type");
    m_side = lDom.getData(_code, "side");
    m_msg = lDom.getData(_code, "msg");
    lDom.getData(_code, m_map, this);
    return true;
}
//===============================================
bool GLog2::isDebug() const {
    return isDebug(GEnv2().isTestEnv());
}
//===============================================
bool GLog2::isDebug(bool _isTestEnv) const {
    if(_isTestEnv) return isTestLog();
    return isProdLog();
}
//===============================================
bool GLog2::isFileLog() const {
    return isFileLog(GEnv2().isTestEnv());
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
bool GLog2::isConnectionError() const {
    return m_isConnectionError;
}
//===============================================
void GLog2::setConnectionError(bool _isConnectionError) {
    m_isConnectionError = _isConnectionError;
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
    GString lLogFile = GFile2().getLogFullname();
    GFile2 lFileObj(lLogFile);
    GString lData = GFORMAT("Le fichier log n'existe pas :\n(%s)", lLogFile.c_str());
    if(lFileObj.existFile()) {
        lData = lFileObj.getContent();
    }
    printf("%s\n", lData.c_str());
}
//===============================================
void GLog2::tailLogFile(bool _isTestEnv) {
    GString lLogFile = GFile2().getLogFullname(_isTestEnv);
    GFile2 lFileObj(lLogFile);
    GString lData = GFORMAT("Le fichier log n'existe pas :\n(%1)", lLogFile.c_str());
    if(lFileObj.existFile()) {
        GShell2().tailFile(lLogFile);
    }
    else {
        printf("%s\n", lData.c_str());
    }
}
//===============================================
void GLog2::addError(const char* _name, int _level, const char* _file, int _line, const char* _func, const GString& _error) {
    traceLog(_name, _level, _file, _line, _func, _error);
    GLog2* lLog = new GLog2;
    lLog->m_type = "error";
    lLog->m_side = "client";
    lLog->m_msg = _error;
    m_map.push_back(lLog);
}
//===============================================
void GLog2::showErrors(const char* _name, int _level, const char* _file, int _line, const char* _func) {
    showErrors(_name, _level, _file, _line, _func, isDebug(), isFileLog());
}
//===============================================
void GLog2::showLogs(const char* _name, int _level, const char* _file, int _line, const char* _func) {
    showLogs(_name, _level, _file, _line, _func, isDebug(), isFileLog());
}
//===============================================
void GLog2::showErrors(const char* _name, int _level, const char* _file, int _line, const char* _func, bool _isDebug, bool _isFileLog) {
    if(!_isDebug) return;
    if(!hasErrors()) return;
    GString lErrors = "";
    for(int i = 0; i < (int)m_map.size(); i++) {
        GLog2* lLog = (GLog2*)m_map.at(i);
        if(lLog->m_type == "error") {
            if(i != 0) lErrors += "\n";
            lErrors += lLog->m_msg;
        }
    }
    traceLog(_name, _level, _file, _line, _func, _isDebug, _isFileLog, lErrors);
}
//===============================================
void GLog2::showLogs(const char* _name, int _level, const char* _file, int _line, const char* _func, bool _isDebug, bool _isFileLog) {
    if(!_isDebug) return;
    if(!hasLogs()) return;
    GString lLogs = "";
    for(int i = 0; i < (int)m_map.size(); i++) {
        GLog2* lLog = (GLog2*)m_map.at(i);
        if(lLog->m_type == "log") {
            if(i != 0) lLogs += "\n";
            lLogs += lLog->m_msg;
        }
    }
    traceLog(_name, _level, _file, _line, _func, _isDebug, _isFileLog, lLogs);
}
//===============================================
void GLog2::showErrors(const char* _name, int _level, const char* _file, int _line, const char* _func, QWidget* _parent) {
    if(!hasErrors()) return;
    GString lErrors = toStringError();
    GMessageBox* lMsgBox = new GMessageBox(_parent);
    lMsgBox->setWindowTitle("Erreurs");
    if(m_isClientSide) {
        lMsgBox->setIcon(QMessageBox::Warning);
    }
    else {
        lMsgBox->setIcon(QMessageBox::Critical);
    }
    lMsgBox->setText(lErrors.toQString());
    lMsgBox->exec();
    clearErrors();
}
//===============================================
void GLog2::showLogs(const char* _name, int _level, const char* _file, int _line, const char* _func, QWidget* _parent) {
    if(!hasLogs()) return;
    GString lLogs = toStringLog();
    GMessageBox* lMsgBox = new GMessageBox(_parent);
    lMsgBox->setWindowTitle("Informations");
    if(m_isClientSide) {
        lMsgBox->setIcon(QMessageBox::Information);
    }
    else {
        lMsgBox->setIcon(QMessageBox::Information);
    }
    lMsgBox->setText(lLogs.toQString());
    lMsgBox->exec();
    clearLogs();
}
//===============================================
void GLog2::loadErrors(const char* _name, int _level, const char* _file, int _line, const char* _func, const GString& _data) {
    if(_data == "") return;
    deserialize(_data);
    showErrors(_name, _level, _file, _line, _func);
}
//===============================================
void GLog2::loadLogs(const char* _name, int _level, const char* _file, int _line, const char* _func, const GString& _data) {
    if(_data == "") return;
    deserialize(_data);
    showLogs(_name, _level, _file, _line, _func);
}
//===============================================
void GLog2::writeLog(const char* _name, int _level, const char* _file, int _line, const char* _func, const GString& _log) {
    writeLog(_name, _level, _file, _line, _func, isDebug(), isFileLog(), _log);
}
//===============================================
void GLog2::writeLog(const char* _name, int _level, const char* _file, int _line, const char* _func, bool _isDebug, bool _isFileLog, const GString& _log) {
    if(_level == 0) return;
    if(!_isDebug) return;
    fprintf(getOutput(_isFileLog), "%s\n", _log.c_str());
    closeLogFile();
}
//===============================================
void GLog2::traceLog(const char* _name, int _level, const char* _file, int _line, const char* _func, const GString& _data) {
    traceLog(_name, _level, _file, _line, _func, isDebug(), isFileLog(), _data);
}
//===============================================
void GLog2::traceLog(const char* _name, int _level, const char* _file, int _line, const char* _func, bool _isDebug, bool _isFileLog, const GString& _data) {
    if(_level == 0) return;
    if(!_isDebug) return;
    GString lDate = GDate2().getDate(GDate2().getDateTimeLogFormat());
    fprintf(getOutput(_isFileLog), "===> [%s] : %d : %s : %s : [%d] : %s :\n%s\n", _name, _level, lDate.c_str(), _file, _line, _func, _data.c_str());
    closeLogFile();
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
void GLog2::onErrorKey(const char* _name, int _level, const char* _file, int _line, const char* _func, const GString& _key) {
    addError(_name, _level, _file, _line, _func, GFORMAT(""
            "Erreur la clé (%s) n'existe pas."
            "", _key.c_str())
    );
}
//===============================================
void GLog2::onErrorCategory(const char* _name, int _level, const char* _file, int _line, const char* _func, const GString& _category) {
    addError(_name, _level, _file, _line, _func, GFORMAT(""
            "Erreur la catégorie (%s) n'existe pas."
            "", _category.c_str())
    );
}
//===============================================
void GLog2::onErrorType(const char* _name, int _level, const char* _file, int _line, const char* _func, const GString& _category, const GString& _type) {
    addError(_name, _level, _file, _line, _func, GFORMAT(""
            "Erreur le type (%s : %s) n'existe pas."
            "", _category.c_str(), _type.c_str())
    );
}
//===============================================
GString GLog2::toStringError() {
    if(!hasErrors()) return "";
    m_isClientSide = true;
    GString lErrors = "";
    for(int i = 0; i < (int)m_map.size(); i++) {
        GLog2* lLog = (GLog2*)m_map.at(i);
        if(lLog->m_type == "error") {
            m_isClientSide &= (lLog->m_side == "client");
            if(i != 0) lErrors += "\n";
            lErrors += lLog->m_msg;
        }
    }
    return lErrors;
}
//===============================================
GString GLog2::toStringLog() {
    if(!hasLogs()) return "";
    m_isClientSide = true;
    GString lLogs = "";
    for(int i = 0; i < (int)m_map.size(); i++) {
        GLog2* lLog = (GLog2*)m_map.at(i);
        if(lLog->m_type == "log") {
            m_isClientSide &= (lLog->m_side == "client");
            if(i != 0) lLogs += "\n";
            lLogs += lLog->m_msg;
        }
    }
    return lLogs;
}
//===============================================
GString GLog2::toString(bool _data) const {
    if(_data) return "true";
    return "false";
}
//===============================================
GString GLog2::toString(const std::vector<GString>& _data) const {
    GString lData = "";
    for(int i = 0; i < (int)_data.size(); i++) {
        if(i != 0) lData += "\n";
        lData += _data.at((int)i);
    }
    return lData;
}
//===============================================
GString GLog2::toString(const std::vector<std::vector<GString>>& _data) const {
    GString lData = "";
    for(int i = 0; i < (int)_data.size(); i++) {
        if(i != 0) lData += "\n";
        std::vector<GString> lDataRow = _data.at((int)i);
        for(int j = 0; j < (int)lDataRow.size(); j++) {
            if(j != 0) lData += "\n";
            lData += lDataRow.at((int)j);
        }
    }
    return lData;
}
//===============================================
