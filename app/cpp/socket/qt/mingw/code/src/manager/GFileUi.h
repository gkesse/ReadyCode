//===============================================
#ifndef _GFileUi_
#define _GFileUi_
//===============================================
#include "GInclude.h"
//===============================================
class GFileUi {
public:
    GFileUi();
    virtual ~GFileUi();
    static GFileUi* Create(const QString& _key);
    virtual void run(int _argc, char** _argv);
};
//==============================================
#endif
//==============================================
