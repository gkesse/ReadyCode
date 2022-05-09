//===============================================
#ifndef _GTimer_
#define _GTimer_
//===============================================
#include "GObject.h"
//===============================================
class GTimer : public GObject {
    Q_OBJECT

public:
    typedef TIMERPROC GTIMER_CB;

public:
    GTimer(GObject* _parent = 0);
    ~GTimer();
    //
    void setTimer(void* _onTimer, int _ms);
    void pauseTimer();
    bool& getRunning();
    static VOID CALLBACK onTimer(HWND, UINT, UINT_PTR, DWORD);

private:
    bool m_running;
};
//==============================================
#endif
//==============================================
