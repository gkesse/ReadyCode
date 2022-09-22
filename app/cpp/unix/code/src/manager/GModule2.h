//===============================================
#ifndef _GModule2_
#define _GModule2_
//===============================================
#include "GObject2.h"
//===============================================
class GSocket2;
//===============================================
class GModule2 : public GObject2 {
public:
    GModule2();
    virtual ~GModule2();

    GObject2* clone() const;

    GString2 serialize(const GString2& _code = "request") const;
    bool deserialize(const GString2& _data, const GString2& _code = "request");

    void setModule(const GString2& _module);
    void setMethod(const GString2& _method);

protected:
    GString2 m_module;
    GString2 m_method;
};
//==============================================
#endif
//==============================================
