//===============================================
#include "GThread2.h"
//===============================================
GThread2::GThread2()
: GObject() {
    m_thread = 0;
    m_threadCB = 0;
    m_params = 0;
}
//===============================================
GThread2::~GThread2() {

}
//===============================================
void GThread2::setThreadCB(void* _threadCB) {
    m_threadCB = _threadCB;
}
//===============================================
void GThread2::setParams(void* _params) {
    m_params = _params;
}
//===============================================
bool GThread2::run() {
    if(m_threadCB == 0) return false;
    if(m_params == 0) return false;
    pthread_create(&m_thread, 0, (GThread2_CB)m_threadCB, m_params);
    return true;
}
//===============================================
