//===============================================
#ifndef _GThread_
#define _GThread_
//===============================================
#include "GObject.h"
//===============================================
class GThread : public GObject {
public:
    typedef void* (*GTHREAD_CB)(void* _params);

public:
    GThread();
    ~GThread();
    void createThread(void* _onThread, void* _params);

private:
    pthread_t m_thread;
};
//===============================================
#endif
//===============================================
