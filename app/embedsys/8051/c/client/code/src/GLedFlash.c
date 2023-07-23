//===============================================
#include "GLedFlash.h"
#include "GPort.h"
//===============================================
static uchar gPort = 1;
static uchar gPin = 0;
//===============================================
void GLedFlash_updateOn() {
    GPort_writePin(gPort, gPin, 0);
}
//===============================================
void GLedFlash_updateOff() {
    GPort_writePin(gPort, gPin, 1);
}
//===============================================
