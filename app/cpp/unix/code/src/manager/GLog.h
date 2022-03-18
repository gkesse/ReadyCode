//===============================================
#ifndef _GLog_
#define _GLog_
//===============================================
#include "GObject.h"
//===============================================
#define GLOGI GLog::Instance()
#define GLOG(...) GLOGI->addError(sformat(__VA_ARGS__))
//===============================================
class GLog : public GObject {
public:
    GLog();
    ~GLog();
    static GLog* Instance();
    void addError(const std::string& _error);
    void showError();
    bool hasError();
    void clearErrors();
    void loadErrors(const std::string& _res);
    std::vector<std::string>& getErrors();

private:
    static GLog* m_instance;
    //
    std::vector<std::string> m_errors;
};
//==============================================
#endif
//==============================================
