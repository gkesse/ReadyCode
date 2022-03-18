//===============================================
#ifndef _GConsole_
#define _GConsole_
//===============================================
#include "GObject.h"
//===============================================
#define GCONSOLE GConsole::Instance()
#define console GCONSOLE->printData
#define consoles(...) GCONSOLE->printData(sformat(__VA_ARGS__))
//===============================================
class GConsole : public GObject {
public:
    GConsole();
    ~GConsole();
    static GConsole* Instance();
    GConsole& printData(bool _data);
    GConsole& printData(int _data);
    GConsole& printData(const char* _data);
    GConsole& printData(const std::string& _data);
    GConsole& printData(const std::vector<std::string>& _data);

private:
    static GConsole* m_instance;
};
//===============================================
#endif
//===============================================
