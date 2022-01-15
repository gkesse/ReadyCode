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
    typedef TIMERPROC onTimerCB;

public:
    GTimer();
    ~GTimer();
    static GTimer* Instance();
    //
    void setTimer(onTimerCB _onTimer, int _ms);
    void pauseTimer();
    //
    void stopTimer();
    bool isTimerOn() const;
    
private:
    static GTimer* m_instance;
    //
    bool m_timerOn;
};
//==============================================
#endif
//==============================================
