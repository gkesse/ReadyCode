//===============================================
#ifndef _GSQLiteUi_
#define _GSQLiteUi_
//===============================================
#include "GInclude.h"
//===============================================
class GSQLiteUi {
public:
    GSQLiteUi();
    virtual ~GSQLiteUi();
    static GSQLiteUi* Create(const QString& _key);
    virtual void run(int _argc, char** _argv);
};
//==============================================
#endif
//==============================================
