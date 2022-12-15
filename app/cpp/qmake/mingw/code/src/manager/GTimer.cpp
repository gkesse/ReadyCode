//===============================================
#include "GTimer.h"
//===============================================
GTimer::GTimer()
: GObject() {
    m_isRunning = true;
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
    while(GetMessage(&lMsg, NULL, 0, 0) && m_isRunning) {
        TranslateMessage(&lMsg);
        DispatchMessage(&lMsg);
    }
}
//===============================================
bool& GTimer::isRunning() {
    return m_isRunning;
}
//===============================================
VOID CALLBACK GTimer::onTimer(HWND, UINT, UINT_PTR, DWORD) {
    // code source
}
//===============================================
