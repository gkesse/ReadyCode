//===============================================
#ifndef _GLog_
#define _GLog_
//===============================================
#include "GObject.h"
//===============================================
class GString;
//===============================================
#define eGOFF   0, __FILE__, __LINE__, __PRETTY_FUNCTION__
#define eGFUN   1, __FILE__, __LINE__, __PRETTY_FUNCTION__
#define eGINF   2, __FILE__, __LINE__, __PRETTY_FUNCTION__
#define eGMSG   3, __FILE__, __LINE__, __PRETTY_FUNCTION__
#define eGWAR   4, __FILE__, __LINE__, __PRETTY_FUNCTION__
#define eGERR   5, __FILE__, __LINE__, __PRETTY_FUNCTION__
#define eGCRI   6, __FILE__, __LINE__, __PRETTY_FUNCTION__
#define eGFAT   7, __FILE__, __LINE__, __PRETTY_FUNCTION__
//===============================================
#define GLOGI GLog::Instance()
#define GERROR(x, ...)      GLOGI->addError(#x, x, sformat(__VA_ARGS__))
#define GERROR_LOAD(x, y)   GLOGI->loadErrors(#x, x, y)
#define GLOGT(x, ...)       GLOGI->traceLog(#x, x, sformat(__VA_ARGS__))
#define GLOGW(x, ...)       GLOGI->writeLog(#x, x, sformat(__VA_ARGS__))
#define GSTRC               GLOGI->toString
//===============================================
class GLog : public GObject {
public:
    GLog();
    ~GLog();
    static GLog* Instance();
    //
    std::string serialize(const std::string& _code = "logs") const;
    void deserialize(const std::string& _data, const std::string& _code = "logs");
    //
    void createDoms();
    bool isDebug() const;
    bool isDebug(bool _isTestEnv) const;
    bool isFileLog() const;
    bool isFileLog(bool _isTestEnv) const;
    bool isTestFileLog() const;
    bool isProdFileLog() const;
    bool isTestLog() const;
    bool isProdLog() const;
    FILE* getOutput(bool _isFileLog);
    FILE* getOutputFile();
    void closeLogFile();
    void catLogFile();
    void tailLogFile(bool _isTestEnv);
    //
    void addError(const char* _name, int _level, const char* _file, int _line, const char* _func, const std::string& _error);
    void showErrors();
    void showErrors(bool _isDebug, bool _isFileLog);
    bool hasErrors() const;
    void clearErrors();
    void loadErrors(const char* _name, int _level, const char* _file, int _line, const char* _func, const std::string& _data);
    //
    void writeLog(const char* _name, int _level, const char* _file, int _line, const char* _func, const std::string& _log);
    void writeLog(const char* _name, int _level, const char* _file, int _line, const char* _func, bool _isDebug, bool _isFileLog, const std::string& _log);
    void traceLog(const char* _name, int _level, const char* _file, int _line, const char* _func, const std::string& _data = "");
    void traceLog(const char* _name, int _level, const char* _file, int _line, const char* _func, bool _isDebug, bool _isFileLog, const std::string& _data = "");
    //
    const char* toString(bool _data) const;
    const char* toString(const GString& _data) const;
    std::string toString(const std::vector<std::string>& _data) const;
    std::string toString(const std::vector<std::vector<std::string>>& _data) const;

private:
    static GLog* m_instance;
    //
    std::string m_type;
    std::string m_msg;
    //
    FILE* m_file;
    std::vector<GObject*> m_logs;
};
//==============================================
#endif
//==============================================
