//===============================================
#include "GTest.h"
#include "GSch.h"
#include "GLedFlash.h"
//===============================================
static uchar gAction;
//===============================================
static void GTest_initLedFlash();
//===============================================
// Public
//===============================================
void GTest_init() {
	gAction = 0;
    if(gAction == 0) GTest_initLedFlash();
}
//===============================================
// LedFlash
//===============================================
static void GTest_initLedFlash() {
    GSch_addTask(GLedFlash_updateOn, 0, 1000);
    GSch_addTask(GLedFlash_updateOff, 500, 1000);
}
//===============================================
