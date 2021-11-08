//===============================================
#ifndef _GQXmlUi_
#define _GQXmlUi_
//===============================================
#include "GInclude.h"
//===============================================
class GQXmlUi {
public:
    GQXmlUi();
    virtual ~GQXmlUi();
    static GQXmlUi* Create(const QString& key);
    virtual void run(int _argc, char** _argv);
};
//==============================================
#endif
//==============================================
