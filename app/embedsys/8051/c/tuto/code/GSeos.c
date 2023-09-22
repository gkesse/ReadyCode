//===============================================
#include "GSeos.h"
#include "GLed.h"
//===============================================
#define PRELOAD(ms) (65536 - ((OSC_FREQ * ms) / (OSC_PER_INST * 1000))) 
#define PRELOAD_H(ms) (PRELOAD(ms) / 256)
#define PRELOAD_L(ms) (PRELOAD(ms) % 256)
//===============================================
void GSeos_init(uchar _ms) {
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
void GSeos_start() {
    EA = 1;
}
//===============================================
void GSeos_goToSleep() {
    PCON |= 0x01;
}
//===============================================
static void GSeos_update() interrupt 5 {
    TF2 = 0;
    GLed_update();
}
//===============================================
