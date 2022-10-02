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

    GObject* clone() const;

    GString serialize(const GString& _code = "request") const;
    bool deserialize(const GString& _data, const GString& _code = "request");

    void setClient(GSocket2* _client);
    void setModule(const GString& _module);
    void setMethod(const GString& _method);

protected:
    GString m_module;
    GString m_method;
    GSocket2* m_server;
};
//==============================================
#endif
//==============================================
