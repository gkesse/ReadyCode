//===============================================
#include "GLog.h"
#include "GPath.h"
#include "GDate.h"
#include "GCode.h"
#include "GEnv.h"
#include "GFile.h"
#include "GShell.h"
#include "GClient.h"
//===============================================
GLog* GLog::m_instance = 0;
//===============================================
GLog::GLog(const GString& _code)
: GObject(_code) {
    createDoms();
    m_file = 0;
    m_isConnectionError = false;
    m_isClientSide = true;
    initLog();
}
//===============================================
GLog::~GLog() {
    clearMap();
}
//===============================================
GLog* GLog::Instance() {
    if(m_instance == 0) {
        m_instance = new GLog;
    }
    return m_instance;
}
//===============================================
GObject* GLog::clone() const {
    return new GLog;
}
//===============================================
GString GLog::serialize(const GString& _code) {
    GCode lDom;
    lDom.createDoc();
    lDom.addData(_code, "type", m_type);
    lDom.addData(_code, "side", m_side);
    lDom.addData(_code, "msg", m_msg);
    lDom.addData(_code, m_map);
    return lDom.toString();
}
//===============================================
bool GLog::deserialize(const GString& _data, const GString& _code) {
    GCode lDom;
    lDom.loadXml(_data);
    m_type = lDom.getData(_code, "type");
    m_side = lDom.getData(_code, "side");
    m_msg = lDom.getData(_code, "msg");
    lDom.getData(_code, m_map, this);
    return true;
}
//===============================================
void GLog::initLog() {
    m_isTestEnv     = GEnv().isTestEnv();
    m_isTestLog     = m_dom->getData("log", "test_on").toBool();
    m_isProdLog     = m_dom->getData("log", "prod_on").toBool();
    m_isTestFile    = m_dom->getData("log", "test_file_on").toBool();
    m_isProdFile    = m_dom->getData("log", "prod_file_on").toBool();
    m_isDebug       = (m_isTestEnv ? m_isTestLog : m_isProdLog);
    m_isFileLog     = (m_isTestEnv ? m_isTestFile : m_isProdFile);
    m_tmpPath       = GEnv().getTmpDir();
    m_currentDate   = GDate().getDateFileFormat();
    m_logTestFile   = GFORMAT("%s/log_test_%s.txt", m_tmpPath.c_str(), m_currentDate.c_str());
    m_logProdFile   = GFORMAT("%s/log_prod_%s.txt", m_tmpPath.c_str(), m_currentDate.c_str());
    m_logFilename   = (m_isTestEnv ? m_logTestFile : m_logProdFile);
}
//===============================================
bool GLog::isConnectionError() const {
    return m_isConnectionError;
}
//===============================================
void GLog::setConnectionError(bool _isConnectionError) {
    m_isConnectionError = _isConnectionError;
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
void GLog::tailLogFile() {
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
    lLog->m_side = "client";
    lLog->m_msg = _error;
    m_map.push_back(lLog);
}
//===============================================
void GLog::showErrors(const char* _name, int _level, const char* _file, int _line, const char* _func) {
    if(!m_isDebug) return;
    if(!hasErrors()) return;
    GString lErrors = "";
    for(int i = 0; i < size(); i++) {
        GLog* lLog = (GLog*)at(i);
        if(lLog->m_type == "error") {
            if(i != 0) lErrors += "\n";
            lErrors += lLog->m_msg;
        }
    }
    traceLog(_name, _level, _file, _line, _func, lErrors);
}
//===============================================
void GLog::showLogs(const char* _name, int _level, const char* _file, int _line, const char* _func) {
    if(!m_isDebug) return;
    if(!hasLogs()) return;
    GString lLogs = "";
    for(int i = 0; i < size(); i++) {
        GLog* lLog = (GLog*)at(i);
        if(lLog->m_type == "log") {
            if(i != 0) lLogs += "\n";
            lLogs += lLog->m_msg;
        }
    }
    traceLog(_name, _level, _file, _line, _func, lLogs);
}
//===============================================
void GLog::showErrors(const char* _name, int _level, const char* _file, int _line, const char* _func, QWidget* _parent) {
    if(!hasErrors()) return;
    GString lErrors = toStringError();
    QMessageBox* lMsgBox = new QMessageBox(_parent);
    lMsgBox->setWindowTitle("Erreurs");
    if(m_isClientSide) {
        lMsgBox->setIcon(QMessageBox::Warning);
    }
    else {
        lMsgBox->setIcon(QMessageBox::Critical);
    }
    lMsgBox->setText(lErrors.c_str());
    lMsgBox->exec();
    clearErrors();
}
//===============================================
void GLog::showLogs(const char* _name, int _level, const char* _file, int _line, const char* _func, QWidget* _parent) {
    if(!hasLogs()) return;
    GString lLogs = toStringLog();
    QMessageBox* lMsgBox = new QMessageBox(_parent);
    lMsgBox->setWindowTitle("Informations");
    if(m_isClientSide) {
        lMsgBox->setIcon(QMessageBox::Information);
    }
    else {
        lMsgBox->setIcon(QMessageBox::Information);
    }
    lMsgBox->setText(lLogs.c_str());
    lMsgBox->exec();
    clearLogs();
}
//===============================================
void GLog::loadErrors(const char* _name, int _level, const char* _file, int _line, const char* _func, const GString& _data) {
    if(_data == "") return;
    deserialize(_data);
    showErrors(_name, _level, _file, _line, _func);
}
//===============================================
void GLog::loadLogs(const char* _name, int _level, const char* _file, int _line, const char* _func, const GString& _data) {
    if(_data == "") return;
    deserialize(_data);
    showLogs(_name, _level, _file, _line, _func);
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
bool GLog::hasErrors() {
    for(int i = 0; i < size(); i++) {
        GLog* lLog = (GLog*)at(i);
        if(lLog->m_type == "error") {
            return true;
        }
    }
    return false;
}
//===============================================
bool GLog::hasLogs() {
    for(int i = 0; i < size(); i++) {
        GLog* lLog = (GLog*)at(i);
        if(lLog->m_type == "log") {
            return true;
        }
    }
    return false;
}
//===============================================
void GLog::clearErrors() {
    for(int i = 0; i < size(); i++) {
        GLog* lLog = (GLog*)at(i);
        if(lLog->m_type == "error") {
            delete lLog;
            m_map.erase (m_map.begin() + i);
        }
    }
}
//===============================================
void GLog::clearLogs() {
    for(int i = 0; i < size(); i++) {
        GLog* lLog = (GLog*)at(i);
        if(lLog->m_type == "log") {
            delete lLog;
            m_map.erase (m_map.begin() + i);
        }
    }
}
//===============================================
void GLog::onErrorKey(const char* _name, int _level, const char* _file, int _line, const char* _func, const GString& _key) {
    addError(_name, _level, _file, _line, _func, GFORMAT(""
            "Erreur la clé (%s) n'existe pas."
            "", _key.c_str())
    );
}
//===============================================
void GLog::onErrorCategory(const char* _name, int _level, const char* _file, int _line, const char* _func, const GString& _category) {
    addError(_name, _level, _file, _line, _func, GFORMAT(""
            "Erreur la catégorie (%s) n'existe pas."
            "", _category.c_str())
    );
}
//===============================================
void GLog::onErrorType(const char* _name, int _level, const char* _file, int _line, const char* _func, const GString& _category, const GString& _type) {
    addError(_name, _level, _file, _line, _func, GFORMAT(""
            "Erreur le type (%s : %s) n'existe pas."
            "", _category.c_str(), _type.c_str())
    );
}
//===============================================
GString GLog::toStringError() {
    if(!hasErrors()) return "";
    m_isClientSide = true;
    GString lErrors = "";
    for(int i = 0; i < size(); i++) {
        GLog* lLog = (GLog*)at(i);
        if(lLog->m_type == "error") {
            m_isClientSide &= (lLog->m_side == "client");
            if(i != 0) lErrors += "\n";
            lErrors += lLog->m_msg;
        }
    }
    return lErrors;
}
//===============================================
GString GLog::toStringLog() {
    if(!hasLogs()) return "";
    m_isClientSide = true;
    GString lLogs = "";
    for(int i = 0; i < size(); i++) {
        GLog* lLog = (GLog*)at(i);
        if(lLog->m_type == "log") {
            m_isClientSide &= (lLog->m_side == "client");
            if(i != 0) lLogs += "\n";
            lLogs += lLog->m_msg;
        }
    }
    return lLogs;
}
//===============================================
GString GLog::toString(bool _data) const {
    if(_data) return "true";
    return "false";
}
//===============================================
GString GLog::toString(const std::vector<GString>& _data) const {
    GString lData = "";
    for(int i = 0; i < (int)_data.size(); i++) {
        if(i != 0) lData += "\n";
        lData += _data.at((int)i);
    }
    return lData;
}
//===============================================
GString GLog::toString(const std::vector<std::vector<GString>>& _data) const {
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
void GLog::enableLogs() {
    GString lData = serialize();
    lData = GCALL_SERVER("logs", "enable_logs", lData);
    deserialize(lData);
}
//===============================================
void GLog::disableLogs() {
    GString lData = serialize();
    lData = GCALL_SERVER("logs", "disable_logs", lData);
    deserialize(lData);
}
//===============================================
