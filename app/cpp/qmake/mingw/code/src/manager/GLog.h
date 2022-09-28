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
#define GLOGT(x, y)         GLOGI->traceLog(#x, x, y)
#define GLOGW(x, y)         GLOGI->writeLog(#x, x, y)
#define GSTRC               GLOGI->toString
//===============================================
class GLog : public GObject {
public:
    GLog();
    ~GLog();
    static GLog* Instance();
    GObject* clone();
    QString serialize(const QString& _code = "logs") const;
    void deserialize(const QString& _data, const QString& _code = "logs");
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
    void addError(const char* _name, int _level, const char* _file, int _line, const char* _func, const QString& _error);
    void showErrors(const char* _name, int _level, const char* _file, int _line, const char* _func);
    void showLogs(const char* _name, int _level, const char* _file, int _line, const char* _func);
    void showErrors(const char* _name, int _level, const char* _file, int _line, const char* _func, QWidget* _parent);
    void showLogs(const char* _name, int _level, const char* _file, int _line, const char* _func, QWidget* _parent);
    void showErrors(const char* _name, int _level, const char* _file, int _line, const char* _func, bool _isDebug, bool _isFileLog);
    void showLogs(const char* _name, int _level, const char* _file, int _line, const char* _func, bool _isDebug, bool _isFileLog);
    void loadErrors(const char* _name, int _level, const char* _file, int _line, const char* _func, const QString& _data);
    void loadLogs(const char* _name, int _level, const char* _file, int _line, const char* _func, const QString& _data);
    //
    void writeLog(const char* _name, int _level, const char* _file, int _line, const char* _func, const QString& _log);
    void writeLog(const char* _name, int _level, const char* _file, int _line, const char* _func, bool _isDebug, bool _isFileLog, const QString& _log);
    void traceLog(const char* _name, int _level, const char* _file, int _line, const char* _func, const QString& _data = "");
    void traceLog(const char* _name, int _level, const char* _file, int _line, const char* _func, bool _isDebug, bool _isFileLog, const QString& _data = "");
    //
    bool hasErrors() const;
    bool hasLogs() const;
    void clearErrors();
    void clearLogs();
    //
    QString toStringError();
    QString toStringLog();
    QString toString(bool _data) const;
    QString toString(const QVector<QString>& _data) const;
    QString toString(const QVector<QVector<QString>>& _data) const;

private:
    static GLog* m_instance;
    //
    QString m_type;
    QString m_side;
    QString m_msg;
    QVector<GObject*> m_map;
    //
    FILE* m_file;
    bool m_isConnectionError;
    bool m_isClientSide;
};
//==============================================
#endif
//==============================================
