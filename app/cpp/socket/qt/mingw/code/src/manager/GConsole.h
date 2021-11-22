//===============================================
#ifndef _GConsole_
#define _GConsole_
//===============================================
#include "GInclude.h"
//===============================================
#define GCONSOLE GConsole::Instance()
//===============================================
class GConsole {
public:
    GConsole();
    ~GConsole();
    static GConsole* Instance();
    void showData(const std::string& _data);
    void showData(const std::vector<std::string>& _data);
    void showData(const std::vector<std::vector<std::string>>& _data);

private:
    static GConsole* m_instance;
};
//==============================================
#endif
//==============================================
