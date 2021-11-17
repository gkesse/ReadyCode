//===============================================
#include "GThread.h"
//===============================================
GThread::GThread() {
    m_threadID = 0;
    m_handleID = 0;
}
//===============================================
GThread::~GThread() {

}
//===============================================
void GThread::createThread(onThreadCB _onThread, void* _params) {
    m_handleID = CreateThread(0, 0, _onThread, _params, 0, &m_threadID);
}
//===============================================
