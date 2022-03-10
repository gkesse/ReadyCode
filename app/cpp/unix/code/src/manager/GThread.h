//===============================================
#ifndef _GThread_
#define _GThread_
//===============================================
#include "GObject.h"
//===============================================
class GThread : public GObject {
public:
    GThread();
    ~GThread();
    void createThread(void* _onThread, void* _params);

private:
    std::thread m_thread;
};
//===============================================
#endif
//===============================================
