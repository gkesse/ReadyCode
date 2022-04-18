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
    void onCreateUser(GSocket* _client);
    void onSaveUser(GSocket* _client);
    //
    int getId() const;
    void loadId();
    void saveData();
    void insertData();
    void updateData();

private:
    int m_id;
    std::string m_pseudo;
    std::string m_password;
};
//==============================================
#endif
//==============================================
