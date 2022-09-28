//===============================================
#include "GThread.h"
//===============================================
GThread::GThread()
: GObject() {
    m_threadID = 0;
    m_handleID = 0;
}
//===============================================
GThread::~GThread() {

}
//===============================================
void GThread::createThread(void* _onThread, void* _params) {
    m_handleID = CreateThread(0, 0, (GTHREAD_CB)_onThread, _params, 0, &m_threadID);
}
//===============================================
DWORD WINAPI GThread::onThread(LPVOID _params) {
    // code source
    return 0;
}
//===============================================
