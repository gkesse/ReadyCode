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
#define SCH_MAX_TASKS (2)
//===============================================
typedef struct _sGTask sGTask;
//===============================================
struct _sGTask {
    void (*pTask)();
    uint delay;
    uint period;
    uchar run_me;
};
//===============================================
sGTask g_task_map[SCH_MAX_TASKS];
//===============================================
static void GSch_Go_To_Sleep();
static void GSch_Delete_Task(uchar index);
//===============================================
void GSch_Init(uchar ms) {
    uchar l_index;
    for(l_index = 0; l_index < SCH_MAX_TASKS; l_index++) {
        GSch_Delete_Task(l_index);
    }
    T2CON = 0x00; 
    TH2 = PRELOAD_H(ms); 
    TL2 = PRELOAD_L(ms); 
    RCAP2H = PRELOAD_H(ms); 
    RCAP2L = PRELOAD_L(ms);
    TF2 = 0;
    ET2 = 1;
    TR2 = 1;
}
//===============================================
void GSch_Add_Task(void (*pTask)(), const uint delay, const uint period) {
    uchar l_index = 0;
    while((g_task_map[l_index].pTask != 0) && (l_index < SCH_MAX_TASKS)) l_index++;
    if(l_index == SCH_MAX_TASKS) return;
    g_task_map[l_index].pTask = pTask;
    g_task_map[l_index].delay = delay;
    g_task_map[l_index].period = period;
    g_task_map[l_index].run_me = 0;
}
//===============================================
void GSch_Start() {
    EA = 1;
}
//===============================================
static void GSch_Update() interrupt INTERRUPT_TIMER_T2 {
    uchar l_index;
    TF2 = 0;
    for(l_index = 0; l_index < SCH_MAX_TASKS; l_index++) {
        if(g_task_map[l_index].pTask != 0) {
            if(g_task_map[l_index].delay == 0) {
                g_task_map[l_index].run_me += 1;
                if(g_task_map[l_index].period != 0) {
                    g_task_map[l_index].delay = g_task_map[l_index].period;
                }
            }
            else {
                g_task_map[l_index].delay -= 1;
            }
        }
    }
}
//===============================================
void GSch_Dispatch_Tasks() {
    uchar l_index;
    for(l_index = 0; l_index < SCH_MAX_TASKS; l_index++) {
        if(g_task_map[l_index].run_me > 0) {
            (*g_task_map[l_index].pTask)();
            g_task_map[l_index].run_me -= 1;
            if(g_task_map[l_index].period == 0) {
                GSch_Delete_Task(l_index);
            }
        }
    }
    GSch_Go_To_Sleep();
}
//===============================================
static void GSch_Delete_Task(uchar index) {
    g_task_map[index].pTask = 0x0000;
    g_task_map[index].delay = 0;
    g_task_map[index].period = 0;
    g_task_map[index].run_me = 0;
}
//===============================================
static void GSch_Go_To_Sleep() {
    PCON |= 0x01;
}
//===============================================