//===============================================
#ifndef _GUser_
#define _GUser_
//===============================================
#include "GModule.h"
//===============================================
class GSocket;
//===============================================
class GUser : public GModule {
public:
    GUser();
    ~GUser();
    //
    GString serialize(const GString& _code = "user") const;
    void deserialize(const GString& _data, const GString& _code = "user");
    //
    bool onModule(GSocket* _client);
    void onCreateAccount(GSocket* _client);
    void onRunConnection(GSocket* _client);
    void onRunDisconnection(GSocket* _client);
    //
    bool runConnection();
    bool createAccount();
    bool runDisconnection();
    //
    bool loadUserPseudo();
    bool loadUserPassword();
    bool loadUser();
    bool computePassword();
    bool saveUser();
    bool insertUser();
    bool updateUser();
    bool updateConnection();

private:
    int m_id;
    GString m_mode;
    GString m_pseudo;
    GString m_password;
    GString m_email;
    GString m_group;
    GString m_active;
    bool m_isConnect;
    //
    GString m_passwordMd5;
};
//==============================================
#endif
//==============================================
