//===============================================
#ifndef _GConsole_
#define _GConsole_
//===============================================
#include "GObject.h"
//===============================================
#define GCONSOLEI GConsole::Instance()
#define console GCONSOLEI->print
//===============================================
class GConsole : public GObject {
public:
    GConsole();
    ~GConsole();
    static GConsole* Instance();
    GConsole& print(const std::string& _data);
    GConsole& print(const std::vector<std::string>& _data);

private:
    static GConsole* m_instance;
};
//===============================================
#endif
//===============================================
