//===============================================
#include "GTimer.h"
#include "GLog.h"
#include "GFormat.h"
//===============================================
GTimer::GTimer() : GObject() {

}
//===============================================
GTimer::~GTimer() {

}
//===============================================
void GTimer::setCallback(void* _onTimer, int _ms) {
    if(GLOGI->hasError()) return;
    m_sigaction.sa_handler = (GSIGNAL_CB)_onTimer;
    sigemptyset(&m_sigaction.sa_mask);
    m_sigaction.sa_flags = 0;
    sigaction(SIGALRM, &m_sigaction, NULL);
    if (sigaction(SIGALRM, &sa, NULL) == -1) {
        GLOG("Erreur la methode (GTimer::setCallbac) a echoue (2).");
        return;
    }
    //
    m_timer.it_interval.tv_sec = _ms / 1000;
    m_timer.it_interval.tv_usec = 0;
    m_timer.it_value.tv_sec = _ms / 1000;
    m_timer.it_value.tv_usec = 0;

    if (setitimer(ITIMER_REAL, &m_timer, NULL) == -1) {
        GLOG("Erreur la methode (GTimer::setCallbac) a echoue (2).");
        return;
    }
}
//===============================================
void GTimer::onTimer(int _signo) {
    if(GLOGI->hasError()) return;
    printf("=====>\n");
    printf("timer du programme...\n");
}
//===============================================
