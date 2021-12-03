//===============================================
#ifndef _GQtLog_
#define _GQtLog_
//===============================================
#include "GInclude.h"
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
#define GLEVEL(_x) #_x
//===============================================
#define GMSG GLEVEL(eGMSG), __FILE__, __LINE__, __FUNCTION__
#define GWAR GLEVEL(eGWAR), __FILE__, __LINE__, __FUNCTION__
#define GERR GLEVEL(eGERR), __FILE__, __LINE__, __FUNCTION__
#define GFAT GLEVEL(eGFAT), __FILE__, __LINE__, __FUNCTION__
#define GCRI GLEVEL(eGCRI), __FILE__, __LINE__, __FUNCTION__
//===============================================
class GQtLog {
public:
    GQtLog();
    ~GQtLog();
    static GQtLog* Instance();
    void showMsg(const char* _level, const char* _file, int _line, const char* _func);
    void showMsg(const char* _level, const char* _file, int _line, const char* _func, const QString& _data);
    void addError(const QString& _data);
    bool hasError();
    void showError();
    void showErrorQt(QWidget* _parent);

private:
    static const int BUFFER_SIZE = 1024;
    static GQtLog* m_instance;
    std::vector<QString> m_errors;
};
//==============================================
#endif
//==============================================
