//===============================================
#ifndef _GQtLog_
#define _GQtLog_
//===============================================
#include "GQtObject.h"
//===============================================
#define GQTLOG GQtLog::Instance()
//===============================================
enum eGLog {
    eGMSG,
    eGWAR,
    eGERR,
    eGFAT,
    eGCRI
};
//===============================================
#define GLEVEL(x) #x
//===============================================
#define GMSG GLEVEL(eGMSG), __FILE__, __LINE__, __FUNCTION__
#define GWAR GLEVEL(eGWAR), __FILE__, __LINE__, __FUNCTION__
#define GERR GLEVEL(eGERR), __FILE__, __LINE__, __FUNCTION__
#define GFAT GLEVEL(eGFAT), __FILE__, __LINE__, __FUNCTION__
#define GCRI GLEVEL(eGCRI), __FILE__, __LINE__, __FUNCTION__
//===============================================
class GQtLog : public GQtObject {
    Q_OBJECT

public:
    GQtLog(QObject* _parent = 0);
    ~GQtLog();
    static GQtLog* Instance();
    void write(const char* _level, const char* _file, int _line, const char* _func);
    void write(const char* _level, const char* _file, int _line, const char* _func, const QString& _data);
    void addError(const QString& _data);
    void addErrorIn(const std::string& _data);
    void addErrorIn(const QString& _data);
    bool hasError();
    void showError();
    void showErrorQt(QWidget* _parent);

private:
    static GQtLog* m_instance;
    QVector<QString> m_errors;
};
//==============================================
#endif
//==============================================
