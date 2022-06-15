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
    void onModule(GSocket* _client);
    void onHasUser(GSocket* _client);
    void onHasUserPassword(GSocket* _client);
    void onCreateUser(GSocket* _client);
    void onRunConnection(GSocket* _client);
    //
    bool runConnection();
    bool runConnectionEmail();
    bool runConnectionPseudo();
    bool loadUserEmail();
    int countMode(const std::string& _mode);
    //
    int getId() const;
    void loadId();
    void loadIdPassword();
    void loadUser();
    void computePassword();
    void saveData();
    void insertData();
    void updateData();

private:
    int m_id;
    std::string m_mode;
    std::string m_email;
    std::string m_pseudo;
    std::string m_password;
    std::string m_group;
    std::string m_active;
};
//==============================================
#endif
//==============================================
