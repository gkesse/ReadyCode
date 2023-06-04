//===============================================
#include "GTimer.h"
//===============================================
GTimer::GTimer() : GObject() {
    m_isRunning = true;
}
//===============================================
GTimer::~GTimer() {

}
//===============================================
void GTimer::setCallback(void* _onTimer, int _ms) {
    m_sigaction.sa_handler = (GSIGNAL_CB)_onTimer;
    sigemptyset(&m_sigaction.sa_mask);
    m_sigaction.sa_flags = SA_RESTART;
    if(sigaction(SIGALRM, &m_sigaction, NULL) == -1) {GERROR_ADD(eGERR, "Erreur lors de la creation du timer."); return;}
    m_timer.it_interval.tv_sec = 0;
    m_timer.it_interval.tv_usec = _ms * 1000;
    m_timer.it_value.tv_sec = 0;
    m_timer.it_value.tv_usec = _ms * 1000;
    if(setitimer(ITIMER_REAL, &m_timer, NULL) == -1) {GERROR_ADD(eGERR, "Erreur lors de la creation du timer."); return;}
}
//===============================================
bool GTimer::isRunning() const {
    return m_isRunning;
}
//===============================================
void GTimer::setRunning(bool _running) {
    m_isRunning = _running;
}
//===============================================
void GTimer::stopTimer() {
    setRunning(false);
}
//===============================================
void GTimer::pauseTimer() {
    while(isRunning()) {
        pause();
    }
}
//===============================================
void GTimer::onTimer(int _signo) {
    GLOGT(eGINF, "");
}
//===============================================
