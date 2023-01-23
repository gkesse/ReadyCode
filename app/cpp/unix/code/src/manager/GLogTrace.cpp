//===============================================
#include "GLogTrace.h"
#include "GDate.h"
//===============================================
GLogTrace* GLogTrace::m_instance = 0;
//===============================================
GLogTrace::GLogTrace() {
    m_hasFileLog = false;
    m_hasDebug = false;
}
//===============================================
GLogTrace::~GLogTrace() {

}
//===============================================
GLogTrace* GLogTrace::Instance() {
    if(m_instance == 0) {
        m_instance = new GLogTrace;
        m_instance->initLogTrace();
    }
    return m_instance;
}
//===============================================
void GLogTrace::initLogTrace() {
    setHasDebug(true);
    setHasFileLog(false);
    setLogFilename("/home/gkesse/.readydev/data/logs.txt");
}
//===============================================
void GLogTrace::setHasDebug(bool _hasDebug) {
    m_hasDebug = _hasDebug;
}
//===============================================
void GLogTrace::setHasFileLog(bool _hasFileLog) {
    m_hasFileLog = _hasFileLog;
}
//===============================================
void GLogTrace::setLogFilename(const GString& _logFilename) {
    m_logFilename = _logFilename;
}
//===============================================
bool GLogTrace::run(const char* _name, int _level, const char* _file, int _line, const char* _func, const GString& _data) {
    if(m_logFilename.isEmpty()) {
        m_logs.addError("Le fichier log est obligatoire.");
        return false;
    }
    if(_level == 0) return true;
    if(!m_hasDebug) return true;

    FILE* lFile = stdout;
    if(m_hasFileLog) {
        lFile = fopen(m_logFilename.c_str(), "a+");
        if(!lFile) {
            m_logs.addError("Le fichier log n'est pas accessible.");
            return false;
        }
    }

    GDate lDate;
    lDate.setFormat(GDate::DATETIME_LOGTRACE);
    lDate.run();
    m_logs.addLogs(lDate.getLogs());

    fprintf(lFile, "===> [%s] : %d : %s : %s : [%d] : %s :\n%s\n", _name, _level, lDate.getDate().c_str(), _file, _line, _func, _data.c_str());

    if(m_hasFileLog) {
        fclose(lFile);
    }

    return !m_logs.hasErrors();
}
//===============================================
