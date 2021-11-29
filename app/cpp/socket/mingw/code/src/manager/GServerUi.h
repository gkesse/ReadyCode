//===============================================
#ifndef _GServerUi_
#define _GServerUi_
//===============================================
#include "GInclude.h"
//===============================================
class GServerUi {
public:
    GServerUi();
    virtual ~GServerUi();
    static GServerUi* Create(const std::string& key);
    virtual void run(int _argc, char** _argv);
};
//==============================================
#endif
//==============================================
