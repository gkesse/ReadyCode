//===============================================
#ifndef _GProcess_
#define _GProcess_
//===============================================
#include "GObject.h"
//===============================================
#define GPROCESS GProcess::Instance()
//===============================================
class GChat;
class GConsole;
class GTimer;
//===============================================
class GProcess : public GObject {
private:
    GProcess();
    
public:
    ~GProcess();
    static GProcess* Instance();
    //
    void run(int _argc, char** _argv);
    void runTest(int _argc, char** _argv);
    void runStudio(int _argc, char** _argv);
    void runSpreadsheet(int _argc, char** _argv);
    void runSocketServer(int _argc, char** _argv);
    void runSocketClient(int _argc, char** _argv);
    void runMaster(int _argc, char** _argv);
    void runSQLite(int _argc, char** _argv);
    void runTimer(int _argc, char** _argv);
    void runOpenCV(int _argc, char** _argv);
    void runOpenCVUi(int _argc, char** _argv);
    //
    void createDoms();
    std::string getName(int _argc, char** _argv) const;
    std::string getName() const;
    bool getNameUse() const;
    bool getProcShow() const;
    bool getArgShow() const;
    //
    static DWORD WINAPI onSocketServer(LPVOID _params);
    static DWORD WINAPI onSocketServerThread(LPVOID _params);
    static void CALLBACK onSocketServerTimer(HWND hwnd, UINT uMsg, UINT_PTR timerId, DWORD dwTime);
    static void CALLBACK onSocketClientTimer(HWND hwnd, UINT uMsg, UINT_PTR timerId, DWORD dwTime);
    static void CALLBACK onSocketClientDispatcher(HWND hwnd, UINT uMsg, UINT_PTR timerId, DWORD dwTime);
    static void CALLBACK onTimer(HWND hwnd, UINT uMsg, UINT_PTR timerId, DWORD dwTime);
    //
    static void onModuleChat(GSocket* _client);

private:
    static GProcess* m_instance;
    static GProcess* m_process;
    //
    GConsole* m_console;
    GTimer* m_timer;
    GSocket* m_server;
    GSocket* m_client;
};
//==============================================
#endif
//==============================================
