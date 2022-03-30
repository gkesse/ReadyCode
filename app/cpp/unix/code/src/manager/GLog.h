//===============================================
#ifndef _GLog_
#define _GLog_
//===============================================
#include "GObject.h"
//===============================================
#define eGINFO       0, __FILE__, __LINE__, __PRETTY_FUNCTION__
#define eGWARNING    1, __FILE__, __LINE__, __PRETTY_FUNCTION__
#define eGERROR      2, __FILE__, __LINE__, __PRETTY_FUNCTION__
#define eGCRITICAL   3, __FILE__, __LINE__, __PRETTY_FUNCTION__
#define eGFATAL      4, __FILE__, __LINE__, __PRETTY_FUNCTION__
//===============================================
#define GLOGI GLog::Instance()
#define GERROR(...) GLOGI->addError(sformat(__VA_ARGS__))
#define GLOG(...) GLOGI->writeLog(sformat(__VA_ARGS__))
#define GLOG2(x) GLOGI->writeLog2(#x, x)
#define GLOG3(x, ...) GLOGI->writeLog2(#x, x, sformat(__VA_ARGS__))
//===============================================
class GLog : public GObject {
public:
    GLog();
    ~GLog();
    static GLog* Instance();
    //
    bool isDebug() const;
    FILE* getOutput() const;
    FILE* getFileOutput() const;
    //
    void addError(const std::string& _error);
    void showError();
    bool hasError();
    void clearErrors();
    void loadErrors(const std::string& _res);
    std::vector<std::string>& getErrors();
    //
    void writeLog(const std::string _log);
    void writeLog2(const char* _name, int _level, const char* _file, int _line, const char* _func, const std::string& _data = "");

private:
    static GLog* m_instance;
    //
    std::vector<std::string> m_errors;
};
//==============================================
#endif
//==============================================
