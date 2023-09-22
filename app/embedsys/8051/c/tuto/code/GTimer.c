//===============================================
#include "GTimer.h"
#include "GLed.h"
//===============================================
static void GTimer_reload();
static void GTimer_update();
//===============================================
void GTimer_init() {
    T2CON = 0x00;
    TH2 = 0x4B;
    TL2 = 0xFD;
    RCAP2H = 0x4B;
    RCAP2L = 0xFD;
    TF2 = 0;
    ET2 = 1;
    EA = 1;
    TR2 = 1;
}
//===============================================
static void GTimer_update() interrupt 5 {
    TF2 = 0;
    GLed_update();
}
//===============================================
