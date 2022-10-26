//===============================================
#ifndef _GLog_
#define _GLog_
//===============================================
#include "GObject.h"
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
#define GERROR_ADD(x, y)    GLOGI->addError(#x, x, y)
#define GERROR_LOAD(x, y)   GLOGI->loadErrors(#x, x, y)
#define GLOG_LOAD(x, y)     GLOGI->loadLogs(#x, x, y)
#define GERROR_SHOW(x)      GLOGI->showErrors(#x, x)
#define GLOG_SHOW(x)        GLOGI->showLogs(#x, x)
#define GERROR_SHOWG(x)     GLOGI->showErrors(#x, x, this)
#define GLOG_SHOWG(x)       GLOGI->showLogs(#x, x, this)
#define GLOGT(x, ...)       GLOGI->traceLog(#x, x, GFORMAT(__VA_ARGS__))
#define GLOGW(x, y)         GLOGI->writeLog(#x, x, y)
#define GSTRC               GLOGI->toString
//===============================================
#define GERROR_KEY(x, y)    GLOGI->onErrorKey(#x, x, y)
#define GERROR_CAT(x, y)    GLOGI->onErrorCategory(#x, x, y)
#define GERROR_TYPE(x, y)   GLOGI->onErrorKey(#x, x, y)
//===============================================
class GLog : public GObject {
public:
    GLog(const GString& _code = "logs");
    ~GLog();
    static GLog* Instance();
    GObject* clone() const;
    GString serialize(const GString& _code = "logs");
    bool deserialize(const GString& _data, const GString& _code = "logs");

    void initLog();

    bool isConnectionError() const;
    void setConnectionError(bool _isConnectionError);
    //
    FILE* getOutput();
    FILE* getOutputFile();
    void closeLogFile();
    void catLogFile();
    void tailLogFile();
    //
    void addError(const char* _name, int _level, const char* _file, int _line, const char* _func, const GString& _error);
    void showErrors(const char* _name, int _level, const char* _file, int _line, const char* _func);
    void showLogs(const char* _name, int _level, const char* _file, int _line, const char* _func);
    void showErrors(const char* _name, int _level, const char* _file, int _line, const char* _func, QWidget* _parent);
    void showLogs(const char* _name, int _level, const char* _file, int _line, const char* _func, QWidget* _parent);
    void showLogs(const char* _name, int _level, const char* _file, int _line, const char* _func, bool _isDebug, bool _isFileLog);
    void loadErrors(const char* _name, int _level, const char* _file, int _line, const char* _func, const GString& _data);
    void loadLogs(const char* _name, int _level, const char* _file, int _line, const char* _func, const GString& _data);
    //
    void writeLog(const char* _name, int _level, const char* _file, int _line, const char* _func, const GString& _log);
    void traceLog(const char* _name, int _level, const char* _file, int _line, const char* _func, const GString& _data = "");
    //
    bool hasErrors() const;
    bool hasLogs() const;
    void clearErrors();
    void clearLogs();

    void onErrorKey(const char* _name, int _level, const char* _file, int _line, const char* _func, const GString& _key);
    void onErrorCategory(const char* _name, int _level, const char* _file, int _line, const char* _func, const GString& _category);
    void onErrorType(const char* _name, int _level, const char* _file, int _line, const char* _func, const GString& _category, const GString& _type);

    GString toStringError();
    GString toStringLog();
    GString toString(bool _data) const;
    GString toString(const std::vector<GString>& _data) const;
    GString toString(const std::vector<std::vector<GString>>& _data) const;

    void enableLogs();
    void disableLogs();

private:
    static GLog* m_instance;
    //
    GString m_type;
    GString m_side;
    GString m_msg;
    std::vector<GObject*> m_map;
    //
    FILE* m_file;
    bool m_isConnectionError;
    bool m_isClientSide;
    //
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
