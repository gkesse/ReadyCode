//===============================================
#include "GTest.h"
#include "GPort.h"
//===============================================
static void GTest_initLedFlash();
static void GTest_runLedFlash();
//===============================================
static uchar gAction = 0;
//===============================================
// public
//===============================================
void GTest_init() {
    gAction = 0;
    if(gAction == 0) GTest_initLedFlash();
}
//===============================================
void GTest_run() {    
    if(gAction == 0) GTest_runLedFlash();
}
//===============================================
// private
//===============================================
static void GTest_initLedFlash() {
    GPort_configPort(1, 0x00);
    GPort_writePort(1, 0xFF);
}
//===============================================
static void GTest_runLedFlash() {
    GPort_writePin(1, 1, 1);
    GDelay_ms(500);
    GPort_writePin(1, 1, 0);
    GDelay_ms(500);
}
//===============================================
