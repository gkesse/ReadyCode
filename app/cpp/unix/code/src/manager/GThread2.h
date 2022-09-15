//===============================================
#ifndef _GThread2_
#define _GThread2_
//===============================================
#include "GObject.h"
//===============================================
class GThread2 : public GObject {
public:
    typedef void* (*GThread2_CB)(void* _params);

public:
    GThread2();
    ~GThread2();
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
