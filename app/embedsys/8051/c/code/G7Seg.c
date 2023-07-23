//===============================================
#include "G7Seg.h"
//===============================================
#define DATA_PORT   P1
//===============================================
static code uchar g_digit_map[] = {
    0x3f, 0x06, 0x5b,0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6F
};
//===============================================
void G7Seg_Digit_Write(uchar d) {
    DATA_PORT = ~g_digit_map[d];
}
//===============================================
