//===============================================
#include "G7SegRun3.h"
#include "G7Seg3.h"
//===============================================
static uint gData = 123;
//===============================================
void G7SegRun3_init() {
    G7Seg3_write(gData);
}
//===============================================
void G7SegRun3_update() {
    G7Seg3_write(gData);
    gData += 1000;
    if(gData > 9999) gData = 123;
}
//===============================================