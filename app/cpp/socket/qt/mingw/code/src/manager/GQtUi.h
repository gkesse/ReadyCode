//===============================================
#ifndef _GQtUi_
#define _GQtUi_
//===============================================
#include "GInclude.h"
//===============================================
class GQtUi {
public:
    GQtUi();
    virtual ~GQtUi();
    static GQtUi* Create(const QString& key);
    virtual void run(int _argc, char** _argv);
};
//==============================================
#endif
//==============================================
