//===============================================
#include "G7SegRun.h"
#include "G7Seg.h"
//===============================================
static uchar gData = 0;
//===============================================
void G7SegRun_init() {
    G7Seg_write(gData);
}
//===============================================
void G7SegRun_update() {
    G7Seg_write(gData);
    if(++gData > 9) gData = 0;
}
//===============================================