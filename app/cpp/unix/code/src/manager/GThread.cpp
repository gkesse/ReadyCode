//===============================================
#include "GThread.h"
//===============================================
GThread::GThread() : GObject() {
    m_thread = 0;
}
//===============================================
GThread::~GThread() {

}
//===============================================
void GThread::createThread(void* _onThread, void* _params) {
    pthread_create(&m_thread, 0, (GTHREAD_CB)_onThread, _params);
}
//===============================================
void GThread::joinThread(void** _params) {
    pthread_join(m_thread, _params);
}
//===============================================
