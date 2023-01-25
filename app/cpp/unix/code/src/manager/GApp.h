//===============================================
#ifndef _GApp_
#define _GApp_
//===============================================
#include "GCode.h"
//===============================================
#define GAPP    GApp::Instance()
//===============================================
class GApp : public GCode {
private:
    GApp();

public:
    ~GApp();
    static GApp* Instance();

private:
    static GApp* m_instance;
};
//==============================================
#endif
//==============================================
