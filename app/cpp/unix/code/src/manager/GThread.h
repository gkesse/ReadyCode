//===============================================
#ifndef _GThread_
#define _GThread_
//===============================================
#include "GObject.h"
//===============================================
class GThread : public GObject {
public:
    typedef void* (*GThread2_CB)(void* _params);

public:
    GThread();
    ~GThread();
    void setThreadCB(void* _threadCB);
    void setParams(void* _params);
    bool run();
    void join();

private:
    pthread_t m_thread;
    void* m_threadCB;
    void* m_params;
};
//===============================================
#endif
//===============================================
