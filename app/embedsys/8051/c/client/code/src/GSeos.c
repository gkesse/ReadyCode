//===============================================
#include "GSeos.h"
#include "GSeosTask.h"
//===============================================
#define PRELOAD(ms) (65536 - ((OSC_FREQ * ms) / (OSC_PER_INST * 1000))) 
#define PRELOAD_H(ms) (PRELOAD(ms) / 256)
#define PRELOAD_L(ms) (PRELOAD(ms) % 256)
//===============================================
#define INTERRUPT_TIMER_T0 1
//===============================================
static void GSeos_reload(uchar _ms);
//===============================================
void GSeos_init(uchar _ms) {
    TMOD &= 0xF0;
    TMOD |= 0x01;
    TL0 = PRELOAD_L(_ms);
    TH0 = PRELOAD_H(_ms);
    TF0 = 0;
    ET0 = 1;
    TR0 = 1;
}
//===============================================
static void GSeos_reload(uchar _ms) {
    TF0 = 0;
    TR0 = 0;
    TL0 = PRELOAD_L(_ms);
    TH0 = PRELOAD_H(_ms);
    TR0 = 1;
}
//===============================================
void GSeos_start() {
    EA = 1;
}
//===============================================
static void GSeos_update() interrupt INTERRUPT_TIMER_T0 {
    GSeos_reload(10);
    GSeosTask_update();
}
//===============================================
void GSeos_goToSleep() {
    PCON |= 0x01;
}
//===============================================
