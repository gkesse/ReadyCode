//===============================================
#ifndef _GManager_
#define _GManager_
//===============================================
#include "GFacade.h"
//===============================================
class GManager : public GFacade {
public:
    GManager();
    ~GManager();
    GString serialize(const GString& _code = "manager") const;
    void deserialize(const GString& _data, const GString& _code = "manager");

protected:
    GString m_module;
    GString m_method;
};
//===============================================
#endif
//===============================================
