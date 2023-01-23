//===============================================
#ifndef _GLogTrace_
#define _GLogTrace_
//===============================================
#include "GLog.h"
//===============================================
#define eGOFF   0, __FILE__, __LINE__, __PRETTY_FUNCTION__
#define eGFUN   1, __FILE__, __LINE__, __PRETTY_FUNCTION__
#define eGINF   2, __FILE__, __LINE__, __PRETTY_FUNCTION__
#define eGMSG   3, __FILE__, __LINE__, __PRETTY_FUNCTION__
#define eGWAR   4, __FILE__, __LINE__, __PRETTY_FUNCTION__
#define eGERR   5, __FILE__, __LINE__, __PRETTY_FUNCTION__
#define eGCRI   6, __FILE__, __LINE__, __PRETTY_FUNCTION__
#define eGFAT   7, __FILE__, __LINE__, __PRETTY_FUNCTION__
#define eGLogTrace   8, __FILE__, __LINE__, __PRETTY_FUNCTION__
//===============================================
#define GLOGTI              GLogTrace::Instance()
#define GLOGT(x, ...)       GLOGTI->run(#x, x, GFORMAT(__VA_ARGS__))
//===============================================
class GLogTrace {
public:
    GLogTrace();
    ~GLogTrace();
    static GLogTrace* Instance();
    void initLogTrace();
    void setHasDebug(bool _hasDebug);
    void setHasFileLog(bool _hasFileLog);
    void setLogFilename(const GString& _logFilename);
    bool run(const char* _name, int _level, const char* _file, int _line, const char* _func, const GString& _data = "");

private:
    static GLogTrace* m_instance;
    GString m_logFilename;
    bool m_hasDebug;
    bool m_hasFileLog;
    GLog m_logs;
};
//==============================================
#endif
//==============================================
