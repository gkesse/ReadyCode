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

    GString2 serialize(const GString2& _code = "request") const;
    bool deserialize(const GString2& _data, const GString2& _code = "request");

    void setModule(const GString2& _module);
    void setMethod(const GString2& _method);

    bool onModule();
    bool onConnection();

    GModule2& operator=(const GModule2& _module);
    GModule2& operator=(GModule2* _module);
    GModule2& operator=(GServer* _client);

protected:
    GString2 m_module;
    GString2 m_method;
    GServer* m_server;
};
//==============================================
#endif
//==============================================
