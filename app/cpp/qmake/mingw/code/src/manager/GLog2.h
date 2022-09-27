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
#define GLOGI2              GLog2::Instance()
#define GERROR_ADD2(x, y)   GLOGI2->addError(#x, x, y)
#define GERROR_LOAD2(x, y)  GLOGI2->loadErrors(#x, x, y)
#define GLOG_LOAD2(x, y)    GLOGI2->loadLogs(#x, x, y)
#define GERROR_SHOW2(x)     GLOGI2->showErrors(#x, x)
#define GLOG_SHOW2(x)       GLOGI2->showLogs(#x, x)
#define GERROR_SHOWG2(x)    GLOGI2->showErrors(#x, x, this)
#define GLOG_SHOWG2(x)      GLOGI2->showLogs(#x, x, this)
#define GLOGT2(x, y)        GLOGI2->traceLog(#x, x, y)
#define GLOGW2(x, y)        GLOGI2->writeLog(#x, x, y)
#define GSTRC2              GLOGI2->toString
#define GLOG_DESERIALIZE2   GLOGI2->deserialize
//===============================================
class GLog2 : public GObject2 {
public:
    GLog2(QObject* _parent = 0);
    ~GLog2();
    static GLog2* Instance();
    GObject2* clone() const;
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
    bool isConnectionError() const;
    void setConnectionError(bool _isConnectionError);
    //
    FILE* getOutput(bool _isFileLog);
    FILE* getOutputFile();
    void closeLogFile();
    void catLogFile();
    void tailLogFile(bool _isTestEnv);
    //
    void addError(const char* _name, int _level, const char* _file, int _line, const char* _func, const GString& _error);
    void showErrors(const char* _name, int _level, const char* _file, int _line, const char* _func);
    void showLogs(const char* _name, int _level, const char* _file, int _line, const char* _func);
    void showErrors(const char* _name, int _level, const char* _file, int _line, const char* _func, QWidget* _parent);
    void showLogs(const char* _name, int _level, const char* _file, int _line, const char* _func, QWidget* _parent);
    void showErrors(const char* _name, int _level, const char* _file, int _line, const char* _func, bool _isDebug, bool _isFileLog);
    void showLogs(const char* _name, int _level, const char* _file, int _line, const char* _func, bool _isDebug, bool _isFileLog);
    void loadErrors(const char* _name, int _level, const char* _file, int _line, const char* _func, const GString& _data);
    void loadLogs(const char* _name, int _level, const char* _file, int _line, const char* _func, const GString& _data);
    //
    void writeLog(const char* _name, int _level, const char* _file, int _line, const char* _func, const GString& _log);
    void writeLog(const char* _name, int _level, const char* _file, int _line, const char* _func, bool _isDebug, bool _isFileLog, const GString& _log);
    void traceLog(const char* _name, int _level, const char* _file, int _line, const char* _func, const GString& _data = "");
    void traceLog(const char* _name, int _level, const char* _file, int _line, const char* _func, bool _isDebug, bool _isFileLog, const GString& _data = "");
    //
    bool hasErrors() const;
    bool hasLogs() const;
    void clearErrors();
    void clearLogs();
    //
    GString toStringError();
    GString toStringLog();
    GString toString(bool _data) const;
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
    bool m_isConnectionError;
    bool m_isClientSide;
};
//==============================================
#endif
//==============================================
