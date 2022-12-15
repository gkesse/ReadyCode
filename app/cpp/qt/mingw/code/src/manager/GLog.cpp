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
void GLog::showErrors() {
    if(!hasErrors()) return;
    std::string lErrors = "";
    for(size_t i = 0; i < m_errors.size(); i++) {
        if(i != 0) lErrors += "\n";
        lErrors += m_errors.at(i);
    }
    fprintf(stdout, "%s\n", lErrors.c_str());
}
//===============================================
bool GLog::hasErrors() {
    bool lError = !m_errors.empty();
    return lError;
}
//===============================================
