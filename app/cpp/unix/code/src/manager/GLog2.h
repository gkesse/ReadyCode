//===============================================
#ifndef _GLog2_
#define _GLog2_
//===============================================
#include "GObject2.h"
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
#define GLOGI2 GLog2::Instance()
#define GERROR_ADD2(x, ...) GLOGI2->addError(#x, x, GFORMAT(__VA_ARGS__))
#define GLOG_ADD2(x, ...)   GLOGI2->addLog(#x, x, GFORMAT(__VA_ARGS__))
#define GERROR_LOAD2(x, y)  GLOGI2->loadErrors(#x, x, y)
#define GLOGT2(x, ...)      GLOGI2->traceLog(#x, x, GFORMAT(__VA_ARGS__))
#define GLOGW2(x, ...)      GLOGI2->writeLog(#x, x, GFORMAT(__VA_ARGS__))
#define GSTRC2              GLOGI2->toString
//===============================================
class GLog2 : public GObject2 {
public:
    GLog2();
    ~GLog2();
    static GLog2* Instance();
    //
    GString serialize(const GString& _code = "logs") const;
    bool deserialize(const GString& _data, const GString& _code = "logs");
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
    void catLogFile();
    void tailLogFile(bool _isTestEnv);
    //
    void addError(const char* _name, int _level, const char* _file, int _line, const char* _func, const GString& _error);
    void addLog(const char* _name, int _level, const char* _file, int _line, const char* _func, const GString& _error);
    void showErrors();
    void showErrors(bool _isDebug, bool _isFileLog);
    bool hasErrors() const;
    bool hasLogs() const;
    void clearMaps();
    void clearErrors();
    void clearLogs();
    void loadErrors(const char* _name, int _level, const char* _file, int _line, const char* _func, const GString& _data);
    //
    void writeLog(const char* _name, int _level, const char* _file, int _line, const char* _func, const GString& _log);
    void writeLog(const char* _name, int _level, const char* _file, int _line, const char* _func, bool _isDebug, bool _isFileLog, const GString& _log);
    void traceLog(const char* _name, int _level, const char* _file, int _line, const char* _func, const GString& _data = "");
    void traceLog(const char* _name, int _level, const char* _file, int _line, const char* _func, bool _isDebug, bool _isFileLog, const GString& _data = "");
    //
    const char* toString(bool _data) const;
    const char* toString(const GString& _data) const;
    GString toString(const std::vector<GString>& _data) const;
    GString toString(const std::vector<std::vector<GString>>& _data) const;

private:
    static GLog2* m_instance;
    //
    GString m_type;
    GString m_side;
    GString m_msg;
    std::vector<GObject2*> m_map;
    //
    FILE* m_file;
};
//==============================================
#endif
//==============================================
