//===============================================
#ifndef _GModule2_
#define _GModule2_
//===============================================
#include "GObject2.h"
//===============================================
class GServer;
//===============================================
class GModule2 : public GObject2 {
public:
    GModule2();
    GModule2(const GModule2& _module);
    GModule2(GModule2* _module);
    GModule2(GServer* _server);
    virtual ~GModule2();

    GObject2* clone() const;

    GString serialize(const GString& _code = "request") const;
    bool deserialize(const GString& _data, const GString& _code = "request");

    void setModule(const GString& _module);
    void setMethod(const GString& _method);

    bool onModule();
    bool onConnection();

protected:
    GString m_module;
    GString m_method;
    GServer* m_server;
};
//==============================================
#endif
//==============================================
