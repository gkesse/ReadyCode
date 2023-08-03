//===============================================
#include "GSchTask.h"
#include "GSch.h"
#include "GLedFlash.h"
#include "GChenillard.h"
#include "G7SegCount.h"
//===============================================
static uchar gAction;
//===============================================
static void GSchTask_initLedFlash();
static void GSchTask_initLedChenillard();
static void GSchTask_init7SegCount();
//===============================================
// Public
//===============================================
void GSchTask_init() {
    gAction = 2;
    if(gAction == 0) GSchTask_initLedFlash();
    else if(gAction == 1) GSchTask_initLedChenillard();
    else if(gAction == 2) GSchTask_init7SegCount();
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
// 7SegCount
//===============================================
static void GSchTask_init7SegCount() {
    G7SegCount_init();
    GSch_addTask(G7SegCount_update, 1, 500);
}
//===============================================
