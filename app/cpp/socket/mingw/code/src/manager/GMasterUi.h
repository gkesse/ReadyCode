//===============================================
#ifndef _GMasterUi_
#define _GMasterUi_
//===============================================
#include "GInclude.h"
//===============================================
class GMasterUi {
public:
    GMasterUi();
    virtual ~GMasterUi();
    static GMasterUi* Create(const std::string& key);
    virtual void run(int _argc, char** _argv);
};
//==============================================
#endif
//==============================================
