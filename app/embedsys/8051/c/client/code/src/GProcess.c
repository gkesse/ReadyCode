//===============================================
#include "GProcess.h"
#include "GSchTask.h"
#include "GSch.h"
#include "GSeos.h"
#include "GSeosTask.h"
#include "GDelay.h"
#include "GPort.h"
#include "GLedFlash2.h"
//===============================================
static uchar gAction;
//===============================================
static void GProcess_initSch();
static void GProcess_runSch();
static void GProcess_initSeos();
static void GProcess_runSeos();
static void GProcess_initSuperLoop();
static void GProcess_runSuperLoop();
//===============================================
static void GProcess_initLedFlash();
static void GProcess_runLedFlash();
//===============================================
// Public
//===============================================
void GProcess_init() {
	gAction = 0;
    if(gAction == 0) GProcess_initSch();
    else if(gAction == 1) GProcess_initSeos();
    else if(gAction == 2) GProcess_initSuperLoop();
    else if(gAction == 3) GProcess_initLedFlash();
}
//===============================================
void GProcess_run() {
    if(gAction == 0) GProcess_runSch();
    else if(gAction == 1) GProcess_runSeos();
    else if(gAction == 2) GProcess_runSuperLoop();
    else if(gAction == 3) GProcess_runLedFlash();
}
//===============================================
// Sch
//===============================================
static void GProcess_initSch() {
    GSch_init(1);
    GSchTask_init();
    GSch_start();
}
//===============================================
static void GProcess_runSch() {
    GSch_dispatchTasks();
}
//===============================================
// Seos
//===============================================
static void GProcess_initSeos() {
    GSeos_init(10);
    GSeosTask_init();
    GSeos_start();
}
//===============================================
static void GProcess_runSeos() {
    GSeos_goToSleep();
}
//===============================================
// Super Loop
//===============================================
static void GProcess_initSuperLoop() {
    GLedFlash2_init();
}
//===============================================
static void GProcess_runSuperLoop() {
    GLedFlash2_update();
    GDelay_ms(10);
}
//===============================================
// LedFlash (boucle infinie)
//===============================================
static void GProcess_initLedFlash() {
    GLedFlash2_init(); 
}
//===============================================
static void GProcess_runLedFlash() {
    GPort_writePin(1, 0, 0);
    GDelay_ms(500);
    GPort_writePin(1, 0, 1);
    GDelay_ms(500);
}
//===============================================
