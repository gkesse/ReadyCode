//===============================================
#ifndef _GAsync_
#define _GAsync_
//===============================================
#include "GObject.h"
//===============================================
class GThread;
class GSocket;
//===============================================
class GAsync : public GObject {
public:
    GAsync();
    ~GAsync();
    //
    std::string serialize() const;
    void deserialize(const std::string& _req);
    //
    void setTitle(const std::string& _title);
    void setStatus(const std::string& _status);
    void setData(const std::string& _data);
    void addData(const std::string& _data);
    void setSocket(GSocket* _socket);
    GSocket* getSocket();
    //
    void onMajAsync();
    //
    void saveData();
    void insertData();
    void updateData();
    //
    void start(void* _onThreadCB, void* _params);
    void maj(const std::string& _status);
    void finish();

private:
    int m_id;
    int m_uid;
    std::string m_title;
    std::string m_status;
    std::string m_data;
    //
    GThread* m_thread;
    GSocket* m_socket;
};
//==============================================
#endif
//==============================================
