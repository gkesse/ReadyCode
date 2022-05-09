//===============================================
#include "GThread.h"
//===============================================
GThread* GThread::m_instance = 0;
//===============================================
GThread::GThread() : GObject() {
    m_threadID = 0;
    m_handleID = 0;
}
//===============================================
GThread::~GThread() {

}
//===============================================
GThread* GThread::Instance() {
    if(m_instance == 0) {
        m_instance = new GThread;
    }
    return m_instance;
}
//===============================================
void GThread::createThread(GTHREAD_CB _onThread, void* _params) {
    m_handleID = CreateThread(0, 0, _onThread, _params, 0, &m_threadID);
}
//===============================================
