//===============================================
#ifndef _GMaster_
#define _GMaster_
//===============================================
#include "GObject.h"
//===============================================
#define GMASTER GMaster::Instance()
//===============================================
class GSocket;
class GTimer;
//===============================================
class GMaster : public GObject {
public:
    GMaster();
    ~GMaster();
    static GMaster* Instance();
    //
    void createDoms();
    int getTimer() const;
    //
    void insertXmlMessage(const std::string& _request) const;
    void updateXmlMessage(const std::string& _request) const;
    int countXmlMessage(const std::string& _request) const;
    void clearXmlMessage() const;
    void loadXmlMessageModule(GSocket* _client) const;
    int getMessageId() const;
    void saveMessageId(int _id) const;
    void incMessageId() const;
    //
    void run(int _argc, char** _argv);
    //
    static DWORD WINAPI onThread(LPVOID _params);
    static DWORD WINAPI onServerTcp(LPVOID _params);
    static void CALLBACK onTimer(HWND hwnd, UINT uMsg, UINT_PTR timerId, DWORD dwTime);
    //
    static void onModuleMaster(const std::string& _request, GSocket* _client);
    static void onStopServer(const std::string& _request, GSocket* _client);
    static void onSaveXmlMessages(const std::string& _request, GSocket* _client);
    static void onClearXmlMessages(const std::string& _request, GSocket* _client);
    static void onLoadXmlMessages(const std::string& _request, GSocket* _client);
    //
    static void onModuleOpenCV(const std::string& _request, GSocket* _client);

private:
    static GMaster* m_instance;
    //
    static GSocket* m_server;
    static GTimer* m_timer;
    //
    static std::queue<std::string> m_dataIn;
    static std::queue<GSocket*> m_clientIn;
};
//==============================================
#endif
//==============================================
