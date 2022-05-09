//===============================================
#ifndef _GThread_
#define _GThread_
//===============================================
#include "GObject.h"
//===============================================
class GThread : public GObject {
    Q_OBJECT

public:
    typedef LPTHREAD_START_ROUTINE GTHREAD_CB;

public:
    GThread(QObject* _parent = 0);
    ~GThread();
    void createThread(void* _onThread, void* _params);
    static DWORD WINAPI onThread(LPVOID _params);

private:
    HANDLE m_handleID;
    DWORD m_threadID;
};
//==============================================
#endif
//==============================================
