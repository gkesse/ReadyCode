//===============================================
#ifndef _GShell_
#define _GShell_
//===============================================
#include "GObject.h"
//===============================================
class GShell : public GObject {
public:
    GShell();
    ~GShell();
    void runSystem(const GString& _cmd);
    GString runCmd(const GString& _cmd);

private:
    static const int BUFFER_MAX = 1*1024; // 1Ko
};
//===============================================
#endif
//===============================================
