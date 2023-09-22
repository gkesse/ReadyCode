//===============================================
#include "G7Seg2.h"
//===============================================
#define DATA_PORT   P1
#define CMD_PORT    P2
//===============================================
sbit CMD_PIN_0      = CMD_PORT^0;
sbit CMD_PIN_1      = CMD_PORT^1;
//===============================================
static uchar gCmdSelect = 0;
static uchar gDataValue = 0;
//===============================================
static void G7Seg2_writeOff();
static void G7Seg2_writeCmd(uchar _cmd);
static void G7Seg2_writeData(uchar _cmd, uchar _data);
//===============================================
static code uchar gDigitMap[] = {
    0x3F, 0x06, 0x5B,0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F
};
//===============================================
static void G7Seg2_writeOff() {
    CMD_PIN_0 = 0;
    CMD_PIN_1 = 0;
}
//===============================================
static void G7Seg2_writeCmd(uchar _cmd) {
    if(_cmd == 0) {
        CMD_PIN_0 = 1;
    }
    else if(_cmd == 1) {
        CMD_PIN_1 = 1;
    }
}
//===============================================
static void G7Seg2_writeData(uchar _cmd, uchar _data) {
    uchar lPort = DATA_PORT;
    uchar lData = ~gDigitMap[_data];
    G7Seg2_writeOff();
    lPort &= 0x80;
    lData &= 0x7F;
    lPort |= lData;
    DATA_PORT = lPort;
    G7Seg2_writeCmd(_cmd);
}
//===============================================
void G7Seg2_write(uchar _data) {
    gDataValue = _data;
}
//===============================================
void G7Seg2_update() {
    uchar lData = gDataValue;
    if(gCmdSelect == 0) {
        lData = lData%10;
        G7Seg2_writeData(1, lData);
        gCmdSelect = 1;
    }
    else if(gCmdSelect == 1) {
        lData = (lData/10)%10;
        G7Seg2_writeData(0, lData);
        gCmdSelect = 0;
    }
}
//===============================================
