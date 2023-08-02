//===============================================
#include "GLedFlash3.h"
#include "GPort2.h"
//===============================================
static uchar gPort = 1;
static uchar gPin = 0;
static uchar gTime = 0;
static ubit gFlash = 1;
//===============================================
void GLedFlash3_init() {
    GPort2_writePort(gPort, 0xFF);
}
//===============================================
void GLedFlash3_update() {
    if(++gTime >= 50) {
        gFlash = !gFlash;
        GPort2_writePin(gPort, gPin, gFlash);
        gTime = 0;
    }
}
//===============================================
