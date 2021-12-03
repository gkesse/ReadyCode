//===============================================
#include "GLog.h"
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
void GQtLog::showMsg(const char* _level, const char* _file, int _line, const char* _func) {
    fprintf(stdout, "[ %s ] [ %s ] [ %d ] [ %s() ]\n", _level, _file, _line, _func);
}
//===============================================
void GQtLog::showMsg(const char* _level, const char* _file, int _line, const char* _func, const char* _format, ...) {
    char lBuffer[BUFFER_SIZE + 1];
    va_list lArgs;
    va_start(lArgs, _format);
    vsprintf(lBuffer, _format, lArgs);
    va_end(lArgs);
    fprintf(stdout, "[ %s ] [ %s ] [ %d ] [ %s() ] : %s\n", _level, _file, _line, _func, lBuffer);
}
//===============================================
void GQtLog::addError(const char* _level, const char* _file, int _line, const char* _func, const char* _format, ...) {
    char lBuffer[BUFFER_SIZE + 1];
    va_list lArgs;
    va_start(lArgs, _format);
    vsprintf(lBuffer, _format, lArgs);
    va_end(lArgs);
    m_errors.push_back(lBuffer);
    fprintf(stdout, "[ %s ] [ %s ] [ %d ] [ %s() ] : %s\n", _level, _file, _line, _func, lBuffer);
}
//===============================================
void GQtLog::addError(const char* _level, const char* _file, int _line, const char* _func, const std::string& _data) {
    m_errors.push_back(_data);
    fprintf(stdout, "[ %s ] [ %s ] [ %d ] [ %s() ] : %s\n", _level, _file, _line, _func, _data.c_str());
}
//===============================================
bool GQtLog::hasError() {
    return (m_errors.size() != 0);
}
//===============================================
void GQtLog::showError() {
    for(size_t i = 0; i < m_errors.size(); i++) {
        std::string lError = m_errors.at(i);
        fprintf(stdout, "%s\n", lError.c_str());
    }
}
//===============================================
