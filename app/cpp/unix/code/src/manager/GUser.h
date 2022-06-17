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
    std::string serialize(const std::string& _code = "user") const;
    void deserialize(const std::string& _data, const std::string& _code = "user");
    //
    bool onModule(GSocket* _client);
    void onCreateUser(GSocket* _client);
    void onRunConnection(GSocket* _client);
    //
    bool runConnection();
    //
    bool loadUserPseudo();
    bool loadUserPassword();
    bool loadUser();
    bool computePassword();
    void saveData();
    void insertData();
    void updateData();

private:
    int m_id;
    std::string m_mode;
    std::string m_email;
    std::string m_pseudo;
    std::string m_password;
    std::string m_passwordMd5;
    std::string m_group;
    std::string m_active;
};
//==============================================
#endif
//==============================================
