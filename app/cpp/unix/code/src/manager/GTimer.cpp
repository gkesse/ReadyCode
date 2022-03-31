//===============================================
#include "GTimer.h"
#include "GLog.h"
#include "GFormat.h"
//===============================================
GTimer::GTimer() : GObject() {
    m_running = true;
}
//===============================================
GTimer::~GTimer() {

}
//===============================================
void GTimer::setCallback(void* _onTimer, int _ms) {
    m_sigaction.sa_handler = (GSIGNAL_CB)_onTimer;
    sigemptyset(&m_sigaction.sa_mask);
    m_sigaction.sa_flags = 0;
    if (sigaction(SIGALRM, &m_sigaction, NULL) == -1) {
        GERROR("Erreur la methode (GTimer::setCallback) a echoue (1)\n"
                "- ms.....: (%d).", _ms);
        return;
    }
    //
    m_timer.it_interval.tv_sec = 0;
    m_timer.it_interval.tv_usec = _ms * 1000;
    m_timer.it_value.tv_sec = 0;
    m_timer.it_value.tv_usec = _ms * 1000;

    if (setitimer(ITIMER_REAL, &m_timer, NULL) == -1) {
        GERROR("Erreur la methode (GTimer::setCallback) a echoue (2)\n"
                "- ms.....: (%d).", _ms);
        return;
    }
}
//===============================================
bool GTimer::isRunning() const {
    return m_running;
}
//===============================================
void GTimer::setRunning(bool _running) {
    m_running = _running;
}
//===============================================
void GTimer::onTimer(int _signo) {
    GLOGT(eGINFO, "timer du programme...\n");
}
//===============================================
