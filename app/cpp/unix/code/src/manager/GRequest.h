//===============================================
#ifndef _GRequest_
#define _GRequest_
//===============================================
#include "GModule.h"
//===============================================
class GSocket;
//===============================================
class GRequest : public GModule {
public:
    GRequest();
    GRequest(const std::string& _msg);
    ~GRequest();
    void onModule(GSocket* _client);
    void onGetRequest(GSocket* _client);
    void loadObj();
    void loadId();
    void loadRequest();
    void saveData();
    void insertData();
    void updateData();

private:
    int m_id;
    int m_uid;
    std::string m_module;
    std::string m_method;
    std::string m_msg;
};
//==============================================
#endif
//==============================================
