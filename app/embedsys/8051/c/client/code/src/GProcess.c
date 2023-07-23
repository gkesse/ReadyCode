//===============================================
#include "GProcess.h"
#include "GTest.h"
#include "GSch.h"
#include "GDelay.h"
#include "GPort.h"
//===============================================
static uchar gAction;
//===============================================
static void GProcess_initSch();
static void GProcess_runSch();
//===============================================
static void GProcess_initLedFlash();
static void GProcess_runLedFlash();
//===============================================
// Public
//===============================================
void GProcess_init() {
	gAction = 0;
    if(gAction == 0) GProcess_initSch();
    else if(gAction == 1) GProcess_initLedFlash();
}
//===============================================
void GProcess_run() {
    if(gAction == 0) GProcess_runSch();
    else if(gAction == 1) GProcess_runLedFlash();
}
//===============================================
// Sch
//===============================================
static void GProcess_initSch() {
    GSch_init(1);
    GTest_init();
    GSch_start();
}
//===============================================
static void GProcess_runSch() {
    GSch_dispatchTasks();
}
//===============================================
// LedFlash
//===============================================
static void GProcess_initLedFlash() {
    GPort_writePort(1, 0xFF); 
}
//===============================================
static void GProcess_runLedFlash() {
    GPort_writePin(1, 1, 0);
    GDelay_ms(500);
    GPort_writePin(1, 1, 1);
    GDelay_ms(500);
}
//===============================================
