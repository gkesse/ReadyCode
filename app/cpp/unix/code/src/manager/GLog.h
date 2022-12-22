//===============================================
#ifndef _GLog_
#define _GLog_
//===============================================
#include "GInclude.h"
//===============================================
#define eGOFF   0, __FILE__, __LINE__, __PRETTY_FUNCTION__
#define eGFUN   1, __FILE__, __LINE__, __PRETTY_FUNCTION__
#define eGINF   2, __FILE__, __LINE__, __PRETTY_FUNCTION__
#define eGMSG   3, __FILE__, __LINE__, __PRETTY_FUNCTION__
#define eGWAR   4, __FILE__, __LINE__, __PRETTY_FUNCTION__
#define eGERR   5, __FILE__, __LINE__, __PRETTY_FUNCTION__
#define eGCRI   6, __FILE__, __LINE__, __PRETTY_FUNCTION__
#define eGFAT   7, __FILE__, __LINE__, __PRETTY_FUNCTION__
#define eGLOG   8, __FILE__, __LINE__, __PRETTY_FUNCTION__
//===============================================
#define GLOGI               GLog::Instance()
#define GERROR_ADD(x, ...)  GLOGI->addError(#x, x, GFORMAT(__VA_ARGS__))
#define GLOG_ADD(x, ...)    GLOGI->addLog(#x, x, GFORMAT(__VA_ARGS__))
#define GERROR_LOAD(x, y)   GLOGI->loadErrors(#x, x, y)
#define GLOGT(x, ...)       GLOGI->traceLog(#x, x, GFORMAT(__VA_ARGS__))
#define GLOGW(x, ...)       GLOGI->writeLog(#x, x, GFORMAT(__VA_ARGS__))
#define GSTRC               GLOGI->toString
//===============================================
class GLog {
public:
    GLog(const GString& _code = "logs");
    ~GLog();
    static GLog* Instance();
    GLog* clone() const;

    GString serialize(const GString& _code = "logs") const;
    bool deserialize(const GString& _data, const GString& _code = "logs");

    FILE* getOutput();
    FILE* getOutputFile();
    GString getCodeName() const;

    void closeLogFile();
    void catLogFile();
    void tailLogFile(bool _isTestEnv);

    void addError(const GString& _error);
    void addError(const char* _name, int _level, const char* _file, int _line, const char* _func, const GString& _error);
    void addLog(const GString& _log);
    void addLog(const char* _name, int _level, const char* _file, int _line, const char* _func, const GString& _log);
    void showErrors();
    bool hasErrors();
    bool hasLogs();
    void clearErrors();
    void clearLogs();
    void clearMap();
    void loadErrors(const char* _name, int _level, const char* _file, int _line, const char* _func, const GString& _data);

    void writeLog(const char* _name, int _level, const char* _file, int _line, const char* _func, const GString& _log);
    void traceLog(const char* _name, int _level, const char* _file, int _line, const char* _func, const GString& _data = "");

    const char* toString(bool _data) const;
    const char* toString(const GString& _data) const;
    GString toString(const std::vector<GString>& _data) const;
    GString toString(const std::vector<std::vector<GString>>& _data) const;

private:
    void initLog();

private:
    static GLog* m_instance;

    GString m_type;
    GString m_side;
    GString m_msg;

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

    GString m_codeName;
    std::vector<GLog*> m_map;
};
//==============================================
#endif
//==============================================
