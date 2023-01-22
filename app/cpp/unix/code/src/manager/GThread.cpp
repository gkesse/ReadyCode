//===============================================
#include "GThread.h"
//===============================================
GThread::GThread()
: GObject() {
    m_thread = 0;
    m_threadCB = 0;
    m_params = 0;
}
//===============================================
GThread::~GThread() {

}
//===============================================
void GThread::setThreadCB(void* _threadCB) {
    m_threadCB = _threadCB;
}
//===============================================
void GThread::setParams(void* _params) {
    m_params = _params;
}
//===============================================
bool GThread::run() {
    if(m_threadCB == 0) {
        m_logs.addError("Erreur la focntion rappel n'est pas initialisée.");
        return false;
    }

    int lOk = pthread_create(&m_thread, 0, (GTHREAD_CB)m_threadCB, m_params);
    if(lOk == -1) {
        m_logs.addError(GFORMAT("Erreur lors de la création du thread.\n[%d]:%s", errno, strerror(errno)));
    }

    return !m_logs.hasErrors();
}
//===============================================
