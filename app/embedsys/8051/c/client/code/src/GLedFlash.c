//===============================================
#include "GLedFlash.h"
#include "GPort.h"
//===============================================
static uchar gPort = 1;
static uchar gPin = 0;
static ubit gFlash = 1;
//===============================================
void GLedFlash_init() {
    GPort_writePort(gPort, 0xFF);
}
//===============================================
void GLedFlash_update() {
    gFlash = !gFlash;
    GPort_writePin(gPort, gPin, gFlash);
}
//===============================================
