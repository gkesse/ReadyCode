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

    bool loadUserPseudo();
    bool loadUserPassword();
    bool loadUser();
    bool computePassword();
    bool saveUser();
    bool insertUser();
    bool updateUser();
    bool updateConnection();

protected:
    int m_id;
    GString2 m_pseudo;
    GString2 m_password;
    GString2 m_passwordMd5;
    GString2 m_email;
    GString2 m_group;
    char m_active;
    bool m_isConnect;
};
//==============================================
#endif
//==============================================
