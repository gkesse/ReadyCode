//===============================================
#ifndef _GThread_
#define _GThread_
//===============================================
#include "GInclude.h"
//===============================================
class GThread {
public:
    typedef DWORD WINAPI (*onThreadCB)(LPVOID _params);

public:
    GThread();
    ~GThread();
    void createThread(onThreadCB _onThread, void* _params);
    
private:
    HANDLE m_handleID;
    DWORD m_threadID;
};
//==============================================
#endif
//==============================================
