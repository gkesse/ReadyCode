//===============================================
#include "GLog.h"
#include "GMessageBox.h"
#include "GCode.h"
#include "GDate.h"
#include "GEnv.h"
#include "GFile.h"
#include "GPath.h"
#include "GShell.h"
//===============================================
GLog* GLog::m_instance = 0;
//===============================================
GLog::GLog(QObject* _parent)
: GObject(_parent) {
    createDoms();
    m_type = "";
    m_side = "";
    m_msg = "";
    m_file = 0;
    m_isConnectionError = false;
    m_isClientSide = true;

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
GObject* GLog::clone() {
    return new GLog;
}
//===============================================
QString GLog::serialize(const QString& _code) const {
    GCode lDom;
    lDom.createDoc();
    lDom.addData(_code, "type", m_type);
    lDom.addData(_code, "side", m_side);
    lDom.addData(_code, "msg", m_msg);
    lDom.addData(_code, m_map);
    return lDom.toStringData();
}
//===============================================
void GLog::deserialize(const QString& _data, const QString& _code) {
    clearMap(m_map);
    GCode lDom;
    lDom.loadXml(_data);
    m_type = lDom.getItem(_code, "type");
    m_side = lDom.getItem(_code, "side");
    m_msg = lDom.getItem(_code, "msg");
    lDom.getItem(_code, m_map, this);
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
bool GLog::isConnectionError() const {
    return m_isConnectionError;
}
//===============================================
void GLog::setConnectionError(bool _isConnectionError) {
    m_isConnectionError = _isConnectionError;
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
    QString lLogFile = GFile().getLogFullname();
    GFile lFileObj(lLogFile);
    QString lData = QString(""
            "Erreur le fichier log n'existe pas.\n"
            "fichier......: (%1)\n").arg(lLogFile);
    if(lFileObj.existFile()) {
        lData = lFileObj.getContent();
    }
    printf("%s\n", lData.toStdString().c_str());
}
//===============================================
void GLog::tailLogFile(bool _isTestEnv) {
    QString lLogFile = GFile().getLogFullname(_isTestEnv);
    GFile lFileObj(lLogFile);
    QString lData = QString(""
            "Erreur le fichier log n'existe pas.\n"
            "fichier......: (%1)\n"
            "").arg(lLogFile);
    if(lFileObj.existFile()) {
        GShell().tailFile(lLogFile);
    }
    else {
        printf("%s\n", lData.toStdString().c_str());
    }
}
//===============================================
void GLog::addError(const char* _name, int _level, const char* _file, int _line, const char* _func, const QString& _error) {
    traceLog(_name, _level, _file, _line, _func, _error);
    GLog* lLog = new GLog;
    lLog->m_type = "error";
    lLog->m_side = "client";
    lLog->m_msg = _error;
    m_map.push_back(lLog);
}
//===============================================
void GLog::showErrors(const char* _name, int _level, const char* _file, int _line, const char* _func) {
    showErrors(_name, _level, _file, _line, _func, isDebug(), isFileLog());
}
//===============================================
void GLog::showErrors(const char* _name, int _level, const char* _file, int _line, const char* _func, bool _isDebug, bool _isFileLog) {
    if(!_isDebug) return;
    if(!hasErrors()) return;
    QString lErrors = "";
    for(int i = 0; i < (int)m_map.size(); i++) {
        GLog* lLog = (GLog*)m_map.at(i);
        if(lLog->m_type == "error") {
            if(i != 0) lErrors += "\n";
            lErrors += lLog->m_msg;
        }
    }
    traceLog(_name, _level, _file, _line, _func, _isDebug, _isFileLog, lErrors);
}
//===============================================
void GLog::showErrors(const char* _name, int _level, const char* _file, int _line, const char* _func, QWidget* _parent) {
    if(!hasErrors()) return;
    QString lErrors = toString();
    GMessageBox* lMsgBox = new GMessageBox(_parent);
    lMsgBox->setWindowTitle("Messages d'erreurs");
    if(m_isClientSide) {
        lMsgBox->setIcon(QMessageBox::Warning);
    }
    else {
        lMsgBox->setIcon(QMessageBox::Critical);
    }
    lMsgBox->setText(lErrors);
    lMsgBox->exec();
    clearErrors();
}
//===============================================
void GLog::loadErrors(const char* _name, int _level, const char* _file, int _line, const char* _func, const QString& _data) {
    if(_data == "") return;
    deserialize(_data);
    showErrors(_name, _level, _file, _line, _func);
}
//===============================================
void GLog::writeLog(const char* _name, int _level, const char* _file, int _line, const char* _func, const QString& _log) {
    writeLog(_name, _level, _file, _line, _func, isDebug(), isFileLog(), _log);
}
//===============================================
void GLog::writeLog(const char* _name, int _level, const char* _file, int _line, const char* _func, bool _isDebug, bool _isFileLog, const QString& _log) {
    if(_level == 0) return;
    if(!_isDebug) return;
    fprintf(getOutput(_isFileLog), "%s\n", _log.toStdString().c_str());
    closeLogFile();
}
//===============================================
void GLog::traceLog(const char* _name, int _level, const char* _file, int _line, const char* _func, const QString& _data) {
    traceLog(_name, _level, _file, _line, _func, isDebug(), isFileLog(), _data);
}
//===============================================
void GLog::traceLog(const char* _name, int _level, const char* _file, int _line, const char* _func, bool _isDebug, bool _isFileLog, const QString& _data) {
    if(_level == 0) return;
    if(!_isDebug) return;
    QString lDate = GDate().getDate(GDate().getDateTimeLogFormat());
    fprintf(getOutput(_isFileLog), "===> [%s] : %d : %s : %s : [%d] : %s :\n%s\n", _name, _level, lDate.toStdString().c_str(), _file, _line, _func, _data.toStdString().c_str());
    closeLogFile();
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
QString GLog::toString(bool _data) const {
    if(_data) return "true";
    return "false";
}
//===============================================
QString GLog::toString() {
    if(!hasErrors()) return "";
    m_isClientSide = true;
    QString lErrors = "";
    for(int i = 0; i < (int)m_map.size(); i++) {
        GLog* lLog = (GLog*)m_map.at(i);
        if(lLog->m_type == "error") {
            m_isClientSide &= (lLog->m_side == "client");
            if(i != 0) lErrors += "\n";
            lErrors += lLog->m_msg;
        }
    }
    return lErrors;
}
//===============================================
QString GLog::toString(const QVector<QString>& _data) const {
    QString lData = "";
    for(int i = 0; i < _data.size(); i++) {
        if(i != 0) lData += "\n";
        lData += _data.at((int)i);
    }
    return lData;
}
//===============================================
QString GLog::toString(const QVector<QVector<QString>>& _data) const {
    QString lData = "";
    for(int i = 0; i < _data.size(); i++) {
        if(i != 0) lData += "\n";
        QVector<QString> lDataRow = _data.at((int)i);
        for(int j = 0; j < lDataRow.size(); j++) {
            if(j != 0) lData += "\n";
            lData += lDataRow.at((int)j);
        }
    }
    return lData;
}
//===============================================
