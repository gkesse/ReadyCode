//===============================================
#ifndef _GThread_
#define _GThread_
//===============================================
#include "GObject.h"
//===============================================
class GThread : public GObject {
public:
    typedef LPTHREAD_START_ROUTINE onThreadCB;

public:
    GThread();
    ~GThread();
    static GThread* Instance();
    void createThread(onThreadCB _onThread, void* _params);
    
private:
    static GThread* m_instance;
    HANDLE m_handleID;
    DWORD m_threadID;
};
//==============================================
#endif
//==============================================
