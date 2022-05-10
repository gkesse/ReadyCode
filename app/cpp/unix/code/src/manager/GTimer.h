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
    bool isRunning() const;
    void setRunning(bool _running);
    void stopTimer();
    void pauseTimer();
    //
    static void onTimer(int _signo);

private:
    struct sigaction m_sigaction;
    struct itimerval m_timer;
    //
    bool m_running;
};
//==============================================
#endif
//==============================================
