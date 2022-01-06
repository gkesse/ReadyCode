//===============================================
#ifndef _GLog_
#define _GLog_
//===============================================
#include "GObject.h"
//===============================================
#define GLOG GLog::Instance()
//===============================================
class GLog : public GObject {
public:
    GLog();
    ~GLog();
    static GLog* Instance();
    void addError(const char* _format, ...);
    void showError();
    bool hasError();

private:
    static const int BUFFER_SIZE = 256;

private:
    static GLog* m_instance;
    std::vector<std::string> m_errors;
    char m_buffer[BUFFER_SIZE + 1];
};
//==============================================
#endif
//==============================================
