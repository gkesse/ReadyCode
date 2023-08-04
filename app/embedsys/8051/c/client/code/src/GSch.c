//===============================================
#include "GSch.h"
//===============================================
#define OSC_FREQ (12000000UL)
#define OSC_PER_INST (12) 
//===============================================
#define PRELOAD(ms) (65536 - ((OSC_FREQ * ms) / (OSC_PER_INST * 1000))) 
#define PRELOAD_H(ms) (PRELOAD(ms) / 256)
#define PRELOAD_L(ms) (PRELOAD(ms) % 256)
//===============================================
#define INTERRUPT_TIMER_T2 5
//===============================================
#define SCH_MAX_TASKS (3)
//===============================================
typedef struct _sGTask sGTask;
//===============================================
struct _sGTask {
    void (*m_pTask)();
    uint m_delay;
    uint m_period;
    uchar m_runMe;
};
//===============================================
sGTask gTaskMap[SCH_MAX_TASKS];
//===============================================
static void GSch_goToSleep();
static void GSch_deleteTask(uchar index);
//===============================================
void GSch_init(uchar _ms) {
    uchar lIndex;
    for(lIndex = 0; lIndex < SCH_MAX_TASKS; lIndex++) {
        GSch_deleteTask(lIndex);
    }
    T2CON = 0x00; 
    TH2 = PRELOAD_H(_ms); 
    TL2 = PRELOAD_L(_ms); 
    RCAP2H = PRELOAD_H(_ms); 
    RCAP2L = PRELOAD_L(_ms);
    TF2 = 0;
    ET2 = 1;
    TR2 = 1;
}
//===============================================
void GSch_addTask(void (*_pTask)(), const uint _delay, const uint _period) {
    uchar lIndex = 0;
    while((gTaskMap[lIndex].m_pTask != 0) && (lIndex < SCH_MAX_TASKS)) lIndex++;
    if(lIndex == SCH_MAX_TASKS) return;
    gTaskMap[lIndex].m_pTask = _pTask;
    gTaskMap[lIndex].m_delay = _delay;
    gTaskMap[lIndex].m_period = _period;
    gTaskMap[lIndex].m_runMe = 0;
}
//===============================================
void GSch_start() {
    EA = 1;
}
//===============================================
static void GSch_update() interrupt INTERRUPT_TIMER_T2 {
    uchar lIndex;
    TF2 = 0;
    for(lIndex = 0; lIndex < SCH_MAX_TASKS; lIndex++) {
        if(gTaskMap[lIndex].m_pTask != 0) {
            if(gTaskMap[lIndex].m_delay == 0) {
                gTaskMap[lIndex].m_runMe += 1;
                if(gTaskMap[lIndex].m_period != 0) {
                    gTaskMap[lIndex].m_delay = gTaskMap[lIndex].m_period;
                }
            }
            else {
                gTaskMap[lIndex].m_delay -= 1;
            }
        }
    }
}
//===============================================
void GSch_dispatchTasks() {
    uchar lIndex;
    for(lIndex = 0; lIndex < SCH_MAX_TASKS; lIndex++) {
        if(gTaskMap[lIndex].m_runMe > 0) {
            (*gTaskMap[lIndex].m_pTask)();
            gTaskMap[lIndex].m_runMe -= 1;
            if(gTaskMap[lIndex].m_period == 0) {
                GSch_deleteTask(lIndex);
            }
        }
    }
    GSch_goToSleep();
}
//===============================================
static void GSch_deleteTask(uchar _index) {
    gTaskMap[_index].m_pTask = 0x0000;
    gTaskMap[_index].m_delay = 0;
    gTaskMap[_index].m_period = 0;
    gTaskMap[_index].m_runMe = 0;
}
//===============================================
static void GSch_goToSleep() {
    PCON |= 0x01;
}
//===============================================