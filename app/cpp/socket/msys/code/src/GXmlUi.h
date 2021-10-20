//===============================================
#ifndef _GXmlUi_
#define _GXmlUi_
//===============================================
#include "GInclude.h"
//===============================================
class GXmlUi {
public:
    GXmlUi();
    virtual ~GXmlUi();
    static GXmlUi* Create(const std::string& key);
    virtual void run(int argc, char** argv);
};
//==============================================
#endif
//==============================================
