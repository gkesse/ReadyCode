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
//===============================================
#define GLOGI GLog::Instance()
#define GERROR(x, y)        GLOGI->addError(#x, x, y)
#define GERROR_OBJ(x, y)    m_errors->addError(#x, x, y)
#define GERROR_LOAD(x, y)   GLOGI->loadErrors(#x, x, y)
#define GERROR_SHOW(x)      GLOGI->showErrors(#x, x)
#define GERROR_SHOWG(x)     GLOGI->showErrors(#x, x, this)
#define GLOGT(x, y)         GLOGI->traceLog(#x, x, y)
#define GLOGW(x, y)         GLOGI->writeLog(#x, x, y)
#define GSTRC               GLOGI->toString
//===============================================
class GLog : public GObject {
public:
    GLog(QObject* _parent = 0);
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
    void catLogFile();
    void tailLogFile(bool _isTestEnv);
    //
    void addError(const char* _name, int _level, const char* _file, int _line, const char* _func, const QString& _error);
    void showErrors(const char* _name, int _level, const char* _file, int _line, const char* _func);
    void showErrors(const char* _name, int _level, const char* _file, int _line, const char* _func, QWidget* _parent);
    void showErrors(const char* _name, int _level, const char* _file, int _line, const char* _func, bool _isDebug, bool _isFileLog);
    bool hasErrors();
    void clearErrors();
    void loadErrors(const char* _name, int _level, const char* _file, int _line, const char* _func, const QString& _res);
    QVector<QString>& getErrors();
    //
    void writeLog(const char* _name, int _level, const char* _file, int _line, const char* _func, const QString& _log);
    void writeLog(const char* _name, int _level, const char* _file, int _line, const char* _func, bool _isDebug, bool _isFileLog, const QString& _log);
    void traceLog(const char* _name, int _level, const char* _file, int _line, const char* _func, const QString& _data = "");
    void traceLog(const char* _name, int _level, const char* _file, int _line, const char* _func, bool _isDebug, bool _isFileLog, const QString& _data = "");
    //
    QString toString(bool _data) const;
    QString toString(const QVector<QString>& _data) const;
    QString toString(const QVector<QVector<QString>>& _data) const;

private:
    static GLog* m_instance;
    FILE* m_file;
};
//==============================================
#endif
//==============================================
