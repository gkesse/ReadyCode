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
    GUser(const std::string& _pseudo);
    ~GUser();
    //
    void onModule(GSocket* _client);
    void onHasUser(GSocket* _client);
    void onHasUserPassword(GSocket* _client);
    void onCreateUser(GSocket* _client);
    //
    std::string serialize() const;
    void deserialize(const std::string& _data);
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
    std::string m_pseudo;
    std::string m_password;
    std::string m_group;
    std::string m_active;
};
//==============================================
#endif
//==============================================
