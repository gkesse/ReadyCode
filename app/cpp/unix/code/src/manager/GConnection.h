//===============================================
#ifndef _GConnection_
#define _GConnection_
//===============================================
#include "GModule2.h"
//===============================================
class GServer;
//===============================================
class GConnection : public GModule2 {
public:
    GConnection();
    GConnection(GModule2* _module);
    virtual ~GConnection();

    GObject2* clone() const;

    GString2 serialize(const GString2& _code = "connection") const;
    bool deserialize(const GString2& _data, const GString2& _code = "connection");

    bool onModule();
    bool onRunConnection();

protected:
    int m_id;
    GString2 m_pseudo;
    GString2 m_password;
    bool m_isConnect;
};
//==============================================
#endif
//==============================================
