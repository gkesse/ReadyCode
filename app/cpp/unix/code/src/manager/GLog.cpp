//===============================================
#include "GLog.h"
//===============================================
GLog* GLog::m_instance = 0;
//===============================================
GLog::GLog() : GObject() {

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
void GLog::addError(const std::string& _error) {
    m_errors.push_back(_error);
}
//===============================================
void GLog::showError() {
    if(!hasError()) return;
    std::string lErrors = "";
    for(int i = 0; i < m_errors.size(); i++) {
        lErrors += m_errors.at(i);
        lErrors += "\n";
    }
    printf("%s", lErrors.c_str());
    m_errors.clear();
}
//===============================================
bool GLog::hasError() {
    bool lError = !m_errors.empty();
    return lError;
}
//===============================================
