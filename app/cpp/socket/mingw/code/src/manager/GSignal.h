//===============================================
#ifndef _GSignal_
#define _GSignal_
//===============================================
#include "GInclude.h"
//===============================================
class GSignal {
public:
    typedef void (*onSignalCB)(int _signal);

public:
    GSignal();
    ~GSignal();
    void setSignal(int _signal, onSignalCB _onSignal);
};
//===============================================
#endif
//===============================================
