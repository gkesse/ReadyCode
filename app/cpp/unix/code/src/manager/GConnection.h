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

    GString serialize(const GString& _code = "connection") const;
    bool deserialize(const GString& _data, const GString& _code = "connection");

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

    void print() const;

protected:
    int m_id;
    GString m_pseudo;
    GString m_password;
    GString m_passwordMd5;
    GString m_email;
    GString m_group;
    char m_active;
    bool m_isConnect;
};
//==============================================
#endif
//==============================================
