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
void GLog::addError(const char* _format, ...) {
    va_list lArgs;
    va_start (lArgs, _format);
    int lSize = vsprintf(m_buffer, _format, lArgs);
    va_end(lArgs);
    if(lSize >= BUFFER_SIZE) {
        m_errors.push_back("Erreur la methode (addError) a echoue.");
    }
    m_errors.push_back(m_buffer);
}
//===============================================
void GLog::showError() {
    if(!hasError()) return;
    std::string lErrors = "";
    for(size_t i = 0; i < m_errors.size(); i++) {
        if(i != 0) lErrors += "\n";
        lErrors += m_errors.at(i);
    }
    fprintf(stdout, "%s\n", lErrors.c_str());
}
//===============================================
bool GLog::hasError() {
    bool lError = !m_errors.empty();
    return lError;
}
//===============================================
