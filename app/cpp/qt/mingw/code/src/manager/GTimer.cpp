//===============================================
#include "GTimer.h"
//===============================================
GTimer* GTimer::m_instance = 0;
//===============================================
GTimer::GTimer() : GObject() {
    m_running = true;
}
//===============================================
GTimer::~GTimer() {

}
//===============================================
GTimer* GTimer::Instance() {
    if(m_instance == 0) {
        m_instance = new GTimer;
    }
    return m_instance;
}
//===============================================
void GTimer::setTimer(GTIMER_CB _onTimer, int _ms) {
    SetTimer(0, 0, _ms, _onTimer);
}
//===============================================
void GTimer::pauseTimer() {
    MSG lMsg;
    while(GetMessage(&lMsg, NULL, 0, 0) && m_running) {
        TranslateMessage(&lMsg);
        DispatchMessage(&lMsg);
    }
}
//===============================================
void GTimer::stopTimer() {
    m_running = false;
}
//===============================================
bool GTimer::isRunning() const {
    return m_running;
}
//===============================================
