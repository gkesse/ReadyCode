//===============================================
#include "GQtLog.h"
#include "GObject.h"
//===============================================
GQtLog* GQtLog::m_instance = 0;
//===============================================
GQtLog::GQtLog() {

}
//===============================================
GQtLog::~GQtLog() {

}
//===============================================
GQtLog* GQtLog::Instance() {
    if(m_instance == 0) {
        m_instance = new GQtLog;
    }
    return m_instance;
}
//===============================================
void GQtLog::write(const char* _level, const char* _file, int _line, const char* _func) {
    fprintf(stdout, "[ %s ] [ %s ] [ %d ] [ %s() ]\n", _level, _file, _line, _func);
}
//===============================================
void GQtLog::write(const char* _level, const char* _file, int _line, const char* _func, const QString& _data) {
    fprintf(stdout, "[ %s ] [ %s ] [ %d ] [ %s() ] : %s\n", _level, _file, _line, _func, _data.toStdString().c_str());
}
//===============================================
void GQtLog::addError(const QString& _data) {
    m_errors.push_back(_data);
}
//===============================================
void GQtLog::addErrorIn(const QString& _data) {
    GObject lDom;
    lDom.loadDom(_data.toStdString());
    for(int i = 0; i < lDom.countErrors(); i++) {
        std::string lErrors = lDom.getErrors(i);
        m_errors.push_back(lErrors.c_str());
    }
}
//===============================================
bool GQtLog::hasError() {
    return !m_errors.empty();
}
//===============================================
void GQtLog::showError() {
    if(!hasError()) return;
    QString lErrors = "";
    for(int i = 0; i < m_errors.size(); i++) {
        if(i != 0) lErrors += "\n";
        lErrors += m_errors.at(i);
    }
    fprintf(stdout, "%s\n", lErrors.toStdString().c_str());
}
//===============================================
void GQtLog::showErrorQt(QWidget* _parent) {
    if(!hasError()) return;
    QString lError = "";
    for(int i = 0; i < m_errors.size(); i++) {
        if(i != 0) lError += "\n";
        lError += m_errors.at(i);
    }
    QMessageBox::critical(_parent, "Messages d'erreurs", lError);
    m_errors.clear();
}
//===============================================
