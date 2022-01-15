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
    void saveXmlMessage(GObject* _request);
    int getMessageId() const;
    void saveMessageId(int _id) const;
    //
    void run(int _argc, char** _argv);
    //
    static DWORD WINAPI onThread(LPVOID _params);
    static DWORD WINAPI onServerTcp(LPVOID _params);
    static void CALLBACK onTimer(HWND hwnd, UINT uMsg, UINT_PTR timerId, DWORD dwTime);
    //
    static void onModuleServer(GObject* _request, GSocket* _client);
    static void onStopServer(GObject* _request, GSocket* _client);
    static void onModuleOpenCV(GObject* _request, GSocket* _client);

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
