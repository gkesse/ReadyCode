//===============================================
#ifndef _GFacade_
#define _GFacade_
//===============================================
#include "GObject.h"
//===============================================
class GFacade : public GObject {
public:
    GFacade();
    ~GFacade();
    void setFacade(const GString& _expression);
    GString serialize(const GString& _code = "facade") const;
    void deserialize(const GString& _data, const GString& _code = "facade");

protected:
    GString m_facade;
};
//===============================================
#endif
//===============================================
