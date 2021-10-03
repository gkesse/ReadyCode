//===============================================
#ifndef _GSocketUi_
#define _GSocketUi_
//===============================================
#include "GInclude.h"
//===============================================
class GSocketUi {
public:
    GSocketUi();
    virtual ~GSocketUi();
    static GSocketUi* Create(const std::string& key);
    virtual void run(int argc, char** argv);
};
//==============================================
#endif
//==============================================
