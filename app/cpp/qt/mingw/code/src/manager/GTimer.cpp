//===============================================
#include "GTimer.h"
//===============================================
GTimer* GTimer::m_instance = 0;
//===============================================
GTimer::GTimer() : GObject() {

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
void GTimer::setTimer(onTimerCB _onTimer, int _ms) {
    SetTimer(0, 0, _ms, _onTimer);
}
//===============================================
void GTimer::pause() {
    MSG lMsg;
    while(GetMessage(&lMsg, NULL, 0, 0)) {
        TranslateMessage(&lMsg);
        DispatchMessage(&lMsg);
    }
}
//===============================================
