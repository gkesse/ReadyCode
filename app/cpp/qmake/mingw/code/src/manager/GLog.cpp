//===============================================
#include "GLog.h"
#include "GConsole.h"
//===============================================
GLog* GLog::m_instance = 0;
//===============================================
GLog::GLog(QObject* _parent) : GObject(_parent) {

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
void GLog::addError(const QString& _error) {
    m_errors.push_back(_error);
}
//===============================================
void GLog::showError() {
    if(!hasError()) return;
    QString lErrors = "";
    for(int i = 0; i < m_errors.size(); i++) {
        if(i != 0) lErrors += "\n";
        lErrors += m_errors.at(i);
    }
    console(lErrors);
    m_errors.clear();
}
//===============================================
void GLog::showError(QWidget* _parent) {
    if(!hasError()) return;
    QString lErrors = "";
    for(int i = 0; i < m_errors.size(); i++) {
        if(i != 0) lErrors += "\n";
        lErrors += m_errors.at(i);
    }
    QMessageBox::critical(_parent, "Messages d'erreurs", lErrors);
    m_errors.clear();
}
//===============================================
bool GLog::hasError() {
    bool lError = !m_errors.empty();
    return lError;
}
//===============================================
