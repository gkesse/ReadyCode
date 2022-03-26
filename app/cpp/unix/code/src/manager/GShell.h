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
    void runSystem(const std::string& _command);
};
//==============================================
#endif
//==============================================
