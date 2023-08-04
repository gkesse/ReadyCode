//===============================================
#include "G7Seg3.h"
//===============================================
#define DATA_PORT   P1
#define CMD_PORT    P2
//===============================================
sbit CMD_PIN_0      = CMD_PORT^0;
sbit CMD_PIN_1      = CMD_PORT^1;
sbit CMD_PIN_2      = CMD_PORT^2;
sbit CMD_PIN_3      = CMD_PORT^3;
//===============================================
static uchar gCmdSelect = 0;
static uint gDataValue = 0;
//===============================================
static void G7Seg3_writeOff();
static void G7Seg3_writeCmd(uchar _cmd);
static void G7Seg3_writeData(uchar _cmd, uchar _data);
//===============================================
static code uchar gDigitMap[] = {
    0x3F, 0x06, 0x5B,0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F
};
//===============================================
static void G7Seg3_writeOff() {
    CMD_PIN_0 = 0;
    CMD_PIN_1 = 0;
    CMD_PIN_2 = 0;
    CMD_PIN_3 = 0;
}
//===============================================
static void G7Seg3_writeCmd(uchar _cmd) {
    if(_cmd == 0) {
        CMD_PIN_0 = 1;
    }
    else if(_cmd == 1) {
        CMD_PIN_1 = 1;
    }
    else if(_cmd == 2) {
        CMD_PIN_2 = 1;
    }
    else if(_cmd == 3) {
        CMD_PIN_3 = 1;
    }
}
//===============================================
static void G7Seg3_writeData(uchar _cmd, uchar _data) {
    uchar lPort = DATA_PORT;
    uchar lData = ~gDigitMap[_data];
    G7Seg3_writeOff();
    lPort &= 0x80;
    lData &= 0x7F;
    lPort |= lData;
    DATA_PORT = lPort;
    G7Seg3_writeCmd(_cmd);
}
//===============================================
void G7Seg3_write(uint _data) {
    gDataValue = _data;
}
//===============================================
void G7Seg3_update() {
    uint lData = gDataValue;
    if(gCmdSelect == 0) {
        lData = lData%10;
        G7Seg3_writeData(3, lData);
        gCmdSelect = 1;
    }
    else if(gCmdSelect == 1) {
        lData = (lData/10)%10;
        G7Seg3_writeData(2, lData);
        gCmdSelect = 2;
    }
    else if(gCmdSelect == 2) {
        lData = (lData/100)%10;
        G7Seg3_writeData(1, lData);
        gCmdSelect = 3;
    }
    else if(gCmdSelect == 3) {
        lData = (lData/1000)%10;
        G7Seg3_writeData(0, lData);
        gCmdSelect = 0;
    }
}
//===============================================
