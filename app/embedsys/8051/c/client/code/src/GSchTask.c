//===============================================
#include "GSchTask.h"
#include "GSch.h"
#include "GLedFlash.h"
//===============================================
static uchar gAction;
//===============================================
static void GSchTask_initLedFlash();
//===============================================
// Public
//===============================================
void GSchTask_init() {
	gAction = 0;
    if(gAction == 0) GSchTask_initLedFlash();
}
//===============================================
// LedFlash
//===============================================
static void GSchTask_initLedFlash() {
    GLedFlash_init();
    GSch_addTask(GLedFlash_update, 0, 500);
}
//===============================================
