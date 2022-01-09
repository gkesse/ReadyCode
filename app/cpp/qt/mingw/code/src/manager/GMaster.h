//===============================================
#ifndef _GMaster_
#define _GMaster_
//===============================================
#include "GObject.h"
//===============================================
#define GMASTER GMaster::Instance()
//===============================================
class GSocket;
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
    void run(int _argc, char** _argv);
    //
    static DWORD WINAPI onThread(LPVOID _params);
    static void CALLBACK onTimer(HWND hwnd, UINT uMsg, UINT_PTR timerId, DWORD dwTime);
    //
    static void onModuleOpenCV(GObject* _request, GSocket* _client);

private:
    static GMaster* m_instance;
    static std::shared_ptr<GObject> m_request;
    static std::shared_ptr<GObject> m_resultOk;
};
//==============================================
#endif
//==============================================
