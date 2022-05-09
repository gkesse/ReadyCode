//===============================================
#ifndef _GThread_
#define _GThread_
//===============================================
#include "GObject.h"
//===============================================
#define GTHREAD GThread::Instance()
//===============================================
class GThread : public GObject {
public:
    typedef LPTHREAD_START_ROUTINE GTHREAD_CB;

public:
    GThread();
    ~GThread();
    static GThread* Instance();
    void createThread(GTHREAD_CB _onThread, void* _params);
    
private:
    static GThread* m_instance;
    HANDLE m_handleID;
    DWORD m_threadID;
};
//==============================================
#endif
//==============================================
