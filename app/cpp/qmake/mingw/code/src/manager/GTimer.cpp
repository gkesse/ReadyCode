//===============================================
#include "GTimer.h"
//===============================================
GTimer::GTimer()
: GObject() {
    m_running = true;
}
//===============================================
GTimer::~GTimer() {

}
//===============================================
void GTimer::setTimer(void* _onTimer, int _ms) {
    SetTimer(0, 0, _ms, (GTIMER_CB)_onTimer);
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
bool& GTimer::getRunning() {
    return m_running;
}
//===============================================
VOID CALLBACK GTimer::onTimer(HWND, UINT, UINT_PTR, DWORD) {
    // code source
}
//===============================================
