//===============================================
#ifndef _GTimer_
#define _GTimer_
//===============================================
#include "GObject.h"
//===============================================
class GTimer : public GObject {
public:
    typedef TIMERPROC GTIMER_CB;

public:
    GTimer();
    ~GTimer();
    //
    void setTimer(void* _onTimer, int _ms);
    void pauseTimer();
    bool& isRunning();
    static VOID CALLBACK onTimer(HWND, UINT, UINT_PTR, DWORD);

private:
    bool m_isRunning;
};
//==============================================
#endif
//==============================================
