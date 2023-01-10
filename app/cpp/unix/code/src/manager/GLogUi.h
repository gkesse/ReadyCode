//===============================================
#ifndef _GLogUi_
#define _GLogUi_
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
#define eGLogUi   8, __FILE__, __LINE__, __PRETTY_FUNCTION__
//===============================================
#define GLOGI               GLogUi::Instance()
#define GERROR_ADD(x, ...)  GLOGI->addError(#x, x, GFORMAT(__VA_ARGS__))
#define GLOG_ADD(x, ...)    GLOGI->addLog(#x, x, GFORMAT(__VA_ARGS__))
#define GERROR_LOAD(x, y)   GLOGI->loadErrors(#x, x, y)
#define GLOGT(x, ...)       GLOGI->traceLog(#x, x, GFORMAT(__VA_ARGS__))
#define GLOGW(x, ...)       GLOGI->writeLog(#x, x, GFORMAT(__VA_ARGS__))
#define GSTRC               GLOGI->toString
//===============================================
class GLogUi {
public:
    GLogUi();
    ~GLogUi();
    static GLogUi* Instance();
    void initLog();

    FILE* getOutput();
    FILE* getOutputFile();

    void closeLogFile();
    void catLogFile();
    void tailLogFile(bool _isTestEnv);

    void addError(const char* _name, int _level, const char* _file, int _line, const char* _func, const GString& _log);
    void writeLog(const char* _name, int _level, const char* _file, int _line, const char* _func, const GString& _log);
    void traceLog(const char* _name, int _level, const char* _file, int _line, const char* _func, const GString& _data = "");

private:
    static GLogUi* m_instance;

    FILE* m_file;

    bool m_isTestEnv;
    bool m_isTestLog;
    bool m_isProdLog;
    bool m_isTestFile;
    bool m_isProdFile;
    bool m_isDebug;
    bool m_isFileLog;

    GString m_tmpPath;
    GString m_currentDate;
    GString m_logTestFile;
    GString m_logProdFile;
    GString m_logFilename;
};
//==============================================
#endif
//==============================================
