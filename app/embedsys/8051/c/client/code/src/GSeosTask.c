//===============================================
#include "GSeosTask.h"
#include "GLedFlash3.h"
//===============================================
static uchar gAction;
//===============================================
static void GSeosTask_initLedFlash();
static void GSeosTask_updateLedFlash();
//===============================================
// Public
//===============================================
void GSeosTask_init() {
    gAction = 0;
    if(gAction == 0) GSeosTask_initLedFlash();
}
//===============================================
void GSeosTask_update() {
    if(gAction == 0) GSeosTask_updateLedFlash();
}
//===============================================
// LedFlash
//===============================================
static void GSeosTask_initLedFlash() {
    GLedFlash3_init();
}
//===============================================
static void GSeosTask_updateLedFlash() {
    GLedFlash3_update();
}
//===============================================
