//===============================================
#include "GSchTask.h"
#include "GSch.h"
#include "G7Seg2.h"
#include "G7Seg3.h"
#include "GClock.h"
//===============================================
#include "GLedFlash.h"
#include "GChenillard.h"
#include "G7SegCount.h"
#include "G7SegCount2.h"
#include "G7SegCount3.h"
//===============================================
static uchar gAction;
//===============================================
static void GSchTask_initLedFlash();
static void GSchTask_initLedChenillard();
static void GSchTask_init7SegCount();
static void GSchTask_init7SegCount2();
static void GSchTask_init7SegCount3();
static void GSchTask_initClock();
//===============================================
// Public
//===============================================
void GSchTask_init() {
    gAction = 5;
    if(gAction == 0) GSchTask_initLedFlash();
    else if(gAction == 1) GSchTask_initLedChenillard();
    else if(gAction == 2) GSchTask_init7SegCount();
    else if(gAction == 3) GSchTask_init7SegCount2();
    else if(gAction == 4) GSchTask_init7SegCount3();
    else if(gAction == 5) GSchTask_initClock();
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
// 7SegCount : 0 - 9
//===============================================
static void GSchTask_init7SegCount() {
    G7SegCount_init();
    GSch_addTask(G7SegCount_update, 1, 500);
}
//===============================================
// 7SegCount2 : 0 - 99
//===============================================
static void GSchTask_init7SegCount2() {
    G7SegCount2_init();
    GSch_addTask(G7Seg2_update, 0, 10);
    GSch_addTask(G7SegCount2_update, 1, 500);
}
//===============================================
// 7SegCount3 : 0 - 9999
//===============================================
static void GSchTask_init7SegCount3() {
    G7SegCount3_init();
    GSch_addTask(G7Seg3_update, 0, 10);
    GSch_addTask(G7SegCount3_update, 1, 500);
}
//===============================================
// Clock
//===============================================
static void GSchTask_initClock() {
    GClock_setHour(20);
    GClock_setMinute(30);
    GClock_setSecond(55);
    GSch_addTask(GClock_update, 0, 10);
    GSch_addTask(GClock_updateDP, 1, 500);
    GSch_addTask(GClock_updateSecond, 3, 1000);
}
//===============================================
