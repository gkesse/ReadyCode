//===============================================
#include "G7Seg.h"
#include "GPort.h"
//===============================================
static uchar gPort = 1;
//===============================================
static code uchar gDigitMap[] = {
    0x3F, 0x06, 0x5B,0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F
};
//===============================================
void G7Seg_write(uchar _data) {
    if(_data > 9) return;
    GPort_writePort(gPort, ~gDigitMap[_data]);
}
//===============================================
