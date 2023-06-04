//===============================================
#ifndef _GConnection_
#define _GConnection_
//===============================================
#include "GManager.h"
//===============================================
class GServer;
//===============================================
class GConnection : public GManager {
public:
    GConnection();
    ~GConnection();

    GObject* clone() const;

    GString serialize(const GString& _code = "connection");
    void deserialize(const GString& _data, const GString& _code = "manager");

    bool loadUserPseudo();
    bool loadUserPassword();
    bool loadUser();
    bool computePassword();
    bool saveUser();
    bool insertUser();
    bool updateUser();
    bool updateConnection();

    void print();

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
