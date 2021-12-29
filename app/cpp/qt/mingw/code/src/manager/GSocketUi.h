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
    static GSocketUi* Create(const QString& key);
    virtual void run(int _argc, char** _argv);
};
//==============================================
#endif
//==============================================
