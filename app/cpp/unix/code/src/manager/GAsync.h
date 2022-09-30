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
    GString serialize(const GString& _code = "async") const;
    void deserialize(const GString& _req, const GString& _code = "async");
    //
    void setTitle(const GString& _title);
    void setStatus(const GString& _status);
    void setData(const GString& _data);
    void addData(const GString& _data);
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
    void maj(const GString& _status);
    void finish();

private:
    int m_id;
    GString m_title;
    GString m_status;
    GString m_data;
    //
    GSocket* m_client;
    bool m_running;
};
//==============================================
#endif
//==============================================
