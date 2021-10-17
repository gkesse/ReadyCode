//===============================================
#ifndef _GOpenCVUi_
#define _GOpenCVUi_
//===============================================
#include "GInclude.h"
//===============================================
class GOpenCVUi {
public:
    GOpenCVUi();
    virtual ~GOpenCVUi();
    static GOpenCVUi* Create(const std::string& key);
    virtual void run(int argc, char** argv);
};
//==============================================
#endif
//==============================================
