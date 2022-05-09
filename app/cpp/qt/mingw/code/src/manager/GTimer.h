//===============================================
#ifndef _GTimer_
#define _GTimer_
//===============================================
#include "GObject.h"
//===============================================
#define GTIMER GTimer::Instance()
//===============================================
class GTimer : public GObject {
public:
    typedef TIMERPROC GTIMER_CB;

public:
    GTimer();
    ~GTimer();
    static GTimer* Instance();
    //
    void setTimer(GTIMER_CB _onTimer, int _ms);
    void pauseTimer();
    //
    void stopTimer();
    bool isRunning() const;
    
private:
    static GTimer* m_instance;
    //
    bool m_running;
};
//==============================================
#endif
//==============================================
