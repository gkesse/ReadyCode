//===============================================
#ifndef _GCppUi_
#define _GCppUi_
//===============================================
#include "GInclude.h"
//===============================================
class GCppUi {
public:
    GCppUi();
    virtual ~GCppUi();
    static GCppUi* Create(const std::string& key);
    virtual void run(int _argc, char** _argv);
};
//==============================================
#endif
//==============================================
