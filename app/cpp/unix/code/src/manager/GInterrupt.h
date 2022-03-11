//===============================================
#ifndef _GInterrupt_
#define _GInterrupt_
//===============================================
#include "GObject.h"
//===============================================
class GInterrupt : public GObject {
public:
    typedef void (*GINTERRUPT_CB)(int _signo);

public:
    GInterrupt();
    ~GInterrupt();
    void setCallback(void* _onInterrupt);
    //
    static void onInterrupt(int _signo);

private:
    struct sigaction m_sigaction;
};
//==============================================
#endif
//==============================================
