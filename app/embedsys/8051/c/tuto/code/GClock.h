//===============================================
#ifndef _GClock_
#define _GClock_
//===============================================
#include "GInclude.h"
//===============================================
void GClock_setHour(uchar _hour);
void GClock_setMinute(uchar _minute);
void GClock_setSecond(uchar _second);
void GClock_update();
void GClock_updateDP();
void GClock_updateSecond();
//===============================================
#endif
//===============================================
