//===============================================
#ifndef _GChat_
#define _GChat_
//===============================================
#include "GObject.h"
//===============================================
#define GCHAT GChat::Instance()
//===============================================
class GChat : public GObject {
public:
    GChat();
    ~GChat();
    static GChat* Instance();
    //
    void createConnection();
    std::string readId();
    std::string readPseudo();
    //
    void createChat();
    //
    void setId(const std::string& _id);
    void setPseudo(const std::string& _pseudo);
    //
    void onModule(GSocket* _client);
    void onConnectClient(GSocket* _client);
    void onSendMessageClient(GSocket* _client);

private:
    static GChat* m_instance;
    //
    std::string m_id;
    std::string m_pseudo;
};
//==============================================
#endif
//==============================================
