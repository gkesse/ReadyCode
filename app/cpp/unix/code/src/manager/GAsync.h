//===============================================
#ifndef _GAsync_
#define _GAsync_
//===============================================
#include "GModule.h"
//===============================================
class GSocket;
//===============================================
class GAsync : public GModule {
public:
    GAsync();
    ~GAsync();
    //
    std::string serialize(const std::string& _code = "async") const;
    void deserialize(const std::string& _req, const std::string& _code = "async");
    //
    void setTitle(const std::string& _title);
    void setStatus(const std::string& _status);
    void setData(const std::string& _data);
    void addData(const std::string& _data);
    void setClient(GSocket* _socket);
    GSocket* getClient();
    //
    void onMajAsync();
    //
    void saveData();
    void insertData();
    void updateData();
    //
    void exec(void* _onThreadCB, void* _params);
    void maj(const std::string& _status);
    void finish();

private:
    int m_id;
    std::string m_title;
    std::string m_status;
    std::string m_data;
    //
    GSocket* m_client;
    bool m_running;
};
//==============================================
#endif
//==============================================
