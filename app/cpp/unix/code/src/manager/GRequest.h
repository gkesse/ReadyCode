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
    ~GRequest();
    //
    std::string serialize() const;
    void deserialize(const std::string& _req);
    //
    void onModule(GSocket* _client);
    void onSaveRequest(GSocket* _client);
    void onGetRequestList(GSocket* _client);
    //
    void loadId();
    void loadRequestList(GSocket* _client);
    void loadRequestCount(GSocket* _client);
    void saveData();
    void insertData();
    void updateData();

private:
    int m_id;
    int m_uid;
    std::string m_module;
    std::string m_method;
    std::string m_msg;
    int m_dataOffset;
    int m_dataSize;
    int m_dataCount;
};
//==============================================
#endif
//==============================================
