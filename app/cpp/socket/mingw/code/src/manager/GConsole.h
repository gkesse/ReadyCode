//===============================================
#ifndef _GConsole_
#define _GConsole_
//===============================================
#include "GInclude.h"
//===============================================
class GConsole {
public:
    GConsole();
    ~GConsole();
    void showData(const std::string& _data);
    void showData(int _data);
    void showFormat(const char* _format, ...);

private:
    static const int BUFFER_SIZE = 1024;
};
//===============================================
#endif
//===============================================
