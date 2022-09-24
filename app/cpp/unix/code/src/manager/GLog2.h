//===============================================
#ifndef _GLog2_
#define _GLog2_
//===============================================
#include "GObject2.h"
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
#define eGLOG   8, __FILE__, __LINE__, __PRETTY_FUNCTION__
//===============================================
#define GLOGI GLog2::Instance()
#define GERROR_ADD(x, ...)  GLOGI->addError(#x, x, sformat(__VA_ARGS__))
#define GLOG_ADD(x, ...)    GLOGI->addLog(#x, x, sformat(__VA_ARGS__))
#define GERROR_LOAD(x, y)   GLOGI->loadErrors(#x, x, y)
#define GLOGT(x, ...)       GLOGI->traceLog(#x, x, sformat(__VA_ARGS__))
#define GLOGW(x, ...)       GLOGI->writeLog(#x, x, sformat(__VA_ARGS__))
#define GSTRC               GLOGI->toString
//===============================================
class GLog2 : public GObject2 {
public:
    GLog2();
    ~GLog2();
    static GLog2* Instance();
    //
    GString2 serialize(const GString2& _code = "logs") const;
    bool deserialize(const GString2& _data, const GString2& _code = "logs");
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
    void addError(const char* _name, int _level, const char* _file, int _line, const char* _func, const GString2& _error);
    void addLog(const char* _name, int _level, const char* _file, int _line, const char* _func, const GString2& _error);
    void showErrors();
    void showErrors(bool _isDebug, bool _isFileLog);
    bool hasErrors() const;
    bool hasLogs() const;
    void clearErrors();
    void clearLogs();
    void loadErrors(const char* _name, int _level, const char* _file, int _line, const char* _func, const GString2& _data);
    //
    void writeLog(const char* _name, int _level, const char* _file, int _line, const char* _func, const GString2& _log);
    void writeLog(const char* _name, int _level, const char* _file, int _line, const char* _func, bool _isDebug, bool _isFileLog, const GString2& _log);
    void traceLog(const char* _name, int _level, const char* _file, int _line, const char* _func, const GString2& _data = "");
    void traceLog(const char* _name, int _level, const char* _file, int _line, const char* _func, bool _isDebug, bool _isFileLog, const GString2& _data = "");
    //
    const char* toString(bool _data) const;
    const char* toString(const GString2& _data) const;
    GString2 toString(const std::vector<GString2>& _data) const;
    GString2 toString(const std::vector<std::vector<GString2>>& _data) const;

private:
    static GLog2* m_instance;
    //
    GString2 m_type;
    GString2 m_side;
    GString2 m_msg;
    std::vector<GObject2*> m_map;
    //
    FILE* m_file;
};
//==============================================
#endif
//==============================================
