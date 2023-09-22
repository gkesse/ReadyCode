//===============================================
#include "GChenillard.h"
//===============================================
#define DATA_PORT   P1
//===============================================
static uchar gCount = 0;
static uchar gData = 0;
//===============================================
static void GChenillard_updateM0();
static void GChenillard_updateM1();
static void GChenillard_updateM2();
static void GChenillard_updateM3();
//===============================================
void GChenillard_init() {
    DATA_PORT = 0xFF;
}
//===============================================
void GChenillard_update() {
    if(gCount <= 7) GChenillard_updateM0();
    else if(gCount <= 16) GChenillard_updateM1();
    else if(gCount <= 26) GChenillard_updateM2();
    else if(gCount <= 36) GChenillard_updateM3();
}
//===============================================
static void GChenillard_updateM0() {
    if(gCount == 0) {gData = 0x01; gCount = 1;}
    else if(gCount == 1) {gData = 0x02; gCount = 2;}
    else if(gCount == 2) {gData = 0x04; gCount = 3;}
    else if(gCount == 3) {gData = 0x08; gCount = 4;}
    else if(gCount == 4) {gData = 0x10; gCount = 5;}
    else if(gCount == 5) {gData = 0x20; gCount = 6;}
    else if(gCount == 6) {gData = 0x40; gCount = 7;}
    else if(gCount == 7) {gData = 0x80; gCount = 8;}
    DATA_PORT = ~gData;
}
//===============================================
static void GChenillard_updateM1() {
    if(gCount == 8) {gData = 0x01; gCount = 9;}
    else if(gCount == 9) {gData = 0x03; gCount = 10;}
    else if(gCount == 10) {gData = 0x06; gCount = 11;}
    else if(gCount == 11) {gData = 0x0C; gCount = 12;}
    else if(gCount == 12) {gData = 0x18; gCount = 13;}
    else if(gCount == 13) {gData = 0x30; gCount = 14;}
    else if(gCount == 14) {gData = 0x60; gCount = 15;}
    else if(gCount == 15) {gData = 0xC0; gCount = 16;}
    else if(gCount == 16) {gData = 0x80; gCount = 17;}
    DATA_PORT = ~gData;
}
//===============================================
static void GChenillard_updateM2() {
    if(gCount == 17) {gData = 0x01; gCount = 18;}
    else if(gCount == 18) {gData = 0x03; gCount = 19;}
    else if(gCount == 19) {gData = 0x07; gCount = 20;}
    else if(gCount == 20) {gData = 0x0E; gCount = 21;}
    else if(gCount == 21) {gData = 0x1C; gCount = 22;}
    else if(gCount == 22) {gData = 0x38; gCount = 23;}
    else if(gCount == 23) {gData = 0x70; gCount = 24;}
    else if(gCount == 24) {gData = 0xE0; gCount = 25;}
    else if(gCount == 25) {gData = 0xC0; gCount = 26;}
    else if(gCount == 26) {gData = 0x80; gCount = 27;}
    DATA_PORT = ~gData;
}
//===============================================
static void GChenillard_updateM3() {
    if(gCount == 27) {gData = 0x01; gCount = 28;}
    else if(gCount == 28) {gData = 0x03; gCount = 29;}
    else if(gCount == 29) {gData = 0x07; gCount = 30;}
    else if(gCount == 30) {gData = 0x0F; gCount = 31;}
    else if(gCount == 31) {gData = 0x1E; gCount = 32;}
    else if(gCount == 32) {gData = 0x3C; gCount = 33;}
    else if(gCount == 33) {gData = 0xF0; gCount = 34;}
    else if(gCount == 34) {gData = 0xE0; gCount = 35;}
    else if(gCount == 35) {gData = 0xC0; gCount = 36;}
    else if(gCount == 36) {gData = 0x80; gCount = 0;}
    DATA_PORT = ~gData;
}
//===============================================
