//===============================================
#include "GSchTask.h"
#include "GSch.h"
#include "GLedFlash.h"
#include "GChenillard.h"
//===============================================
static uchar gAction;
//===============================================
static void GSchTask_initLedFlash();
static void GSchTask_initLedChenillard();
//===============================================
// Public
//===============================================
void GSchTask_init() {
    gAction = 1;
    if(gAction == 0) GSchTask_initLedFlash();
    else if(gAction == 1) GSchTask_initLedChenillard();
}
//===============================================
// LedFlash
//===============================================
static void GSchTask_initLedFlash() {
    GLedFlash_init();
    GSch_addTask(GLedFlash_update, 0, 500);
}
//===============================================
// LedChenillard
//===============================================
static void GSchTask_initLedChenillard() {
    GChenillard_init();
    GSch_addTask(GChenillard_update, 1, 500);
}
//===============================================
