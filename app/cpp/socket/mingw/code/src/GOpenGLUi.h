//===============================================
#ifndef _GOpenGLUi_
#define _GOpenGLUi_
//===============================================
#include "GInclude.h"
//===============================================
class GOpenGLUi {
public:
    GOpenGLUi();
    virtual ~GOpenGLUi();
    static GOpenGLUi* Create(const std::string& key);
    virtual void run(int argc, char** argv);
};
//==============================================
#endif
//==============================================
