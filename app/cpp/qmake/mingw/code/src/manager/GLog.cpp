//===============================================
#include "GLog.h"
#include "GCode.h"
#include "GDate.h"
#include "GEnv.h"
#include "GFile.h"
#include "GPath.h"
#include "GShell.h"
#include "GError.h"
//===============================================
GLog* GLog::m_instance = 0;
//===============================================
GLog::GLog() : GObject() {
    createDoms();
    // file
    m_file = 0;
    // errors
    m_errors.reset(new GError);
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
    QString lLogFile = GFile().getLogFullname();
    GFile lFileObj(lLogFile);
    QString lData = QString("Erreur le fichier log n'existe pas.\n"
            "- fichier.....: %1").arg(lLogFile);
    if(lFileObj.existFile()) {
        lData = lFileObj.getContent();
    }
    printf("%s\n", lData.toStdString().c_str());
}
//===============================================
void GLog::tailLogFile(bool _isTestEnv) {
    QString lLogFile = GFile().getLogFullname(_isTestEnv);
    GFile lFileObj(lLogFile);
    QString lData = QString("Erreur le fichier log n'existe pas.\n"
            "- fichier.....: %1").arg(lLogFile);
    if(lFileObj.existFile()) {
        GShell().tailFile(lLogFile);
    }
    else {
        printf("%s\n", lData.toStdString().c_str());
    }
}
//===============================================
void GLog::addError(const QString& _error) {
    m_errors->addError(_error);
}
//===============================================
void GLog::showError() {
    showError(isDebug(), isFileLog());
}
//===============================================
void GLog::showError(QWidget* _parent) {
    if(!hasError()) return;
    QString lErrors = m_errors->toString();
    QMessageBox::critical(_parent, "Messages d'erreurs", lErrors);
    m_errors.clear();
}
//===============================================
void GLog::showError(bool _isDebug, bool _isFileLog) {
    if(!_isDebug) return;
    if(!hasError()) return;
    GLOGT(eGERR, m_errors->toString());
    m_errors->clearErrors();
}
//===============================================
bool GLog::hasError() {
    return m_errors->hasErrors();
}
//===============================================
void GLog::clearErrors() {
    m_errors->clearErrors();
}
//===============================================
void GLog::loadErrors(const QString& _res) {
    m_errors->loadErrors(_res);
}
//===============================================
QVector<QString>& GLog::getErrors() {
    return m_errors->getErrors();
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
    if(_data == "") {
        fprintf(getOutput(_isFileLog), "===> [%s] : %d : %s : %s : [%d] : %s :\n", _name, _level, lDate.toStdString().c_str(), _file, _line, _func);
    }
    else {
        fprintf(getOutput(_isFileLog), "===> [%s] : %d : %s : %s : [%d] : %s :\n%s\n", _name, _level, lDate.toStdString().c_str(), _file, _line, _func, _data.toStdString().c_str());
    }
    closeLogFile();
}
//===============================================
QString GLog::toString(bool _data) const {
    if(_data) return "true";
    return "false";
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
