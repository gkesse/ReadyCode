//===============================================
#include "GLedFlash2.h"
#include "GPort.h"
//===============================================
static uchar gPort = 1;
static uchar gPin = 0;
static uchar gTime = 0;
static ubit gFlash = 1;
//===============================================
void GLedFlash2_init() {
    GPort_writePort(gPort, 0xFF);
}
//===============================================
void GLedFlash2_update() {
    if(++gTime >= 50) {
        gFlash = !gFlash;
        GPort_writePin(gPort, gPin, gFlash);
        gTime = 0;
    }
}
//===============================================
