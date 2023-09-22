//===============================================
#include "GSchTask.h"
#include "GSch.h"
#include "GLed.h"
#include "G7Seg.h"
#include "G7SegRun.h"
#include "GUart.h"
//===============================================
static uchar gAction;
//===============================================
static void GSchTask_initLedFlash();
static void GSchTask_init7Seg();
static void GSchTask_initUart();
static void GSchTask_initUartReadWrite();
//===============================================
void GSchTask_init() {
    gAction = 3;
    if(gAction == 0) GSchTask_initLedFlash();
    else if(gAction == 1) GSchTask_init7Seg();
    else if(gAction == 2) GSchTask_initUart();
    else if(gAction == 3) GSchTask_initUartReadWrite();
}
//===============================================
// LED
//===============================================
static void GSchTask_initLedFlash() {
    GLed_init();
    GSch_addTask(GLed_update, 0, 500);
}
//===============================================
// 7segment
//===============================================
static void GSchTask_init7Seg() {
    G7SegRun_init();
    GSch_addTask(G7SegRun_update, 0, 500);
}
//===============================================
// UART
//===============================================
static void GSchTask_initUart() {
    GUart_init(9600);
    GUart_writeChar("12345678");
    GSch_addTask(GUart_updateWrite, 0, 10);
}
//===============================================
static void GSchTask_initUartReadWrite() {
    GUart_init(9600);
    GSch_addTask(GUart_updateRead, 0, 200);
    GSch_addTask(GUart_updateReadWrite, 1, 200);
}
//===============================================
