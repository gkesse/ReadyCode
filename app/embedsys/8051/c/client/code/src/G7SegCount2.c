//===============================================
#include "G7SegCount2.h"
#include "G7Seg2.h"
//===============================================
static uchar gData = 0;
//===============================================
void G7SegCount2_init() {
    G7Seg2_write(gData);
}
//===============================================
void G7SegCount2_update() {
    G7Seg2_write(gData);
    gData += 10;
    if(gData > 99) gData = 0;
}
//===============================================
