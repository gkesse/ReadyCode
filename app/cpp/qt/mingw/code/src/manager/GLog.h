//===============================================
#ifndef _GLog_
#define _GLog_
//===============================================
#include "GObject.h"
//===============================================
#define GERROR_ADD GLog::Instance()
//===============================================
class GLog : public GObject {
public:
    GLog();
    ~GLog();
    static GLog* Instance();
    void addError(const std::string& _error);
    void showErrors();
    bool hasErrors();

private:
    static GLog* m_instance;
    //
    std::vector<std::string> m_errors;
};
//==============================================
#endif
//==============================================
