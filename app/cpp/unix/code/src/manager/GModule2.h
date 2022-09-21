//===============================================
#ifndef _GModule2_
#define _GModule2_
//===============================================
#include "GObject.h"
//===============================================
class GSocket2;
//===============================================
class GModule2 : public GObject {
public:
    GModule2();
    virtual ~GModule2();

    GString2 serialize(const GString2& _code = "request") const;
    bool deserialize(const GString2& _data, const GString2& _code = "request");

    void setClient(GSocket2* _client);
    void setModule(const GString2& _module);
    void setMethod(const GString2& _method);

    void print() const;

protected:
    GString2 m_module;
    GString2 m_method;

    GSocket2* m_client;
};
//==============================================
#endif
//==============================================
