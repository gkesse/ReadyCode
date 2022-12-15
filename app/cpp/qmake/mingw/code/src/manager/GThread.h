//===============================================
#ifndef _GThread_
#define _GThread_
//===============================================
#include "GObject.h"
//===============================================
class GThread : public GObject {
public:
    typedef LPTHREAD_START_ROUTINE GTHREAD_CB;

public:
    GThread();
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
