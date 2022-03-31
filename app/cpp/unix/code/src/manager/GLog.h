//===============================================
#ifndef _GLog_
#define _GLog_
//===============================================
#include "GObject.h"
//===============================================
#define eGFUNC      1, __FILE__, __LINE__, __PRETTY_FUNCTION__
#define eGINFO      2, __FILE__, __LINE__, __PRETTY_FUNCTION__
#define eGMSG       3, __FILE__, __LINE__, __PRETTY_FUNCTION__
#define eGWARNING   4, __FILE__, __LINE__, __PRETTY_FUNCTION__
#define eGERROR     5, __FILE__, __LINE__, __PRETTY_FUNCTION__
#define eGCRITICAL  6, __FILE__, __LINE__, __PRETTY_FUNCTION__
#define eGFATAL     7, __FILE__, __LINE__, __PRETTY_FUNCTION__
//===============================================
#define GLOGI GLog::Instance()
#define GERROR(...) GLOGI->addError(sformat(__VA_ARGS__))
#define GLOGT(x, ...) GLOGI->traceLog(#x, x, sformat(__VA_ARGS__))
#define GLOGW(...) GLOGI->writeLog(sformat(__VA_ARGS__))
//===============================================
class GLog : public GObject {
public:
    GLog();
    ~GLog();
    static GLog* Instance();
    void createDoms();
    //
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
    void showLogFile();
    //
    void addError(const std::string& _error);
    void showError();
    void showError(bool _isDebug, bool _isFileLog);
    bool hasError();
    void clearErrors();
    void loadErrors(const std::string& _res);
    std::vector<std::string>& getErrors();
    //
    void writeLog(const std::string _log);
    void writeLog(bool _isDebug, bool _isFileLog, const std::string _log);
    void traceLog(const char* _name, int _level, const char* _file, int _line, const char* _func, const std::string& _data = "");
    void traceLog(const char* _name, int _level, const char* _file, int _line, const char* _func, bool _isDebug, bool _isFileLog, const std::string& _data = "");

private:
    static GLog* m_instance;
    std::vector<std::string> m_errors;
    FILE* m_file;
};
//==============================================
#endif
//==============================================
