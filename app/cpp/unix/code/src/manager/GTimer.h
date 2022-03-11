//===============================================
#ifndef _GTimer_
#define _GTimer_
//===============================================
#include "GObject.h"
//===============================================
class GTimer : public GObject {
public:
    typedef void (*GSIGNAL_CB)(int _signo);

public:
    GTimer();
    ~GTimer();
    void setCallback(void* _onTimer, int _ms);
    //
    static void onTimer(int _signo);

private:
    struct sigaction m_sigaction;
    struct itimerval m_timer;
};
//==============================================
#endif
//==============================================
