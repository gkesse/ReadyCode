//===============================================
#ifndef _GConnection_
#define _GConnection_
//===============================================
#include "GModule.h"
//===============================================
class GServer;
//===============================================
class GConnection : public GModule {
public:
    GConnection();
    ~GConnection();

    GObject* clone() const;

    GString serialize(const GString& _code = "connection") const;
    bool deserialize(const GString& _data, const GString& _code = "connection");

    bool loadUserPseudo();
    bool loadUserPassword();
    bool loadUser();
    bool computePassword();
    bool saveUser();
    bool insertUser();
    bool updateUser();
    bool updateConnection();

    void print() const;

    bool onModule();
    bool onRunConnection();

protected:
    int m_id;
    GString m_pseudo;
    GString m_password;
    GString m_passwordMd5;
    GString m_email;
    GString m_group;
    bool m_active;
    bool m_isConnect;
};
//==============================================
#endif
//==============================================
