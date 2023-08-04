//===============================================
#include "GClock.h"
//===============================================
#define DATA_PORT   P1
#define CMD_PORT    P2
//===============================================
sbit CMD_PIN_0      = CMD_PORT^0;
sbit CMD_PIN_1      = CMD_PORT^1;
sbit CMD_PIN_2      = CMD_PORT^2;
sbit CMD_PIN_3      = CMD_PORT^3;
sbit DP_PIN         = DATA_PORT^7;
//===============================================
typedef struct _sGData sGData;
//===============================================
struct _sGData {
    uchar m_hour;
    uchar m_minute;
    uchar m_second;
    uchar m_update;
};
//===============================================
static sGData gData= {0, 0, 0, 0};
//===============================================
static void GClock_writeOff();
static void GClock_writeCmd(uchar _cmd);
static void GClock_writeData(uchar _cmd, uchar _data);
//===============================================
static code uchar gDigitMap[] = {
    0x3F, 0x06, 0x5B,0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F
};
//===============================================
// private
//===============================================
static void GClock_writeOff() {
    CMD_PIN_0 = 0;
    CMD_PIN_1 = 0;
    CMD_PIN_2 = 0;
    CMD_PIN_3 = 0;
}
//===============================================
static void GClock_writeCmd(uchar _cmd) {
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
static void GClock_writeData(uchar _cmd, uchar _data) {
    uchar lPort = DATA_PORT;
    uchar lData = ~gDigitMap[_data];
    GClock_writeOff();
    lPort &= 0x80;
    lData &= 0x7F;
    lPort |= lData;
    DATA_PORT = lPort;
    GClock_writeCmd(_cmd);
}
//===============================================
// public
//===============================================
void GClock_setHour(uchar _hour) {
    gData.m_hour = _hour;
}
//===============================================
void GClock_setMinute(uchar _minute) {
    gData.m_minute = _minute;
}
//===============================================
void GClock_setSecond(uchar _second) {
    gData.m_second = _second;
}
//===============================================
void GClock_update() {
    uchar lData;
    if(gData.m_update == 0) {
        lData = (gData.m_hour/10)%10;
        GClock_writeData(0, lData);
        gData.m_update = 1;
    }
    else if(gData.m_update == 1) {
        lData = gData.m_hour%10;
        GClock_writeData(1, lData);
        gData.m_update = 2;
    }
    else if(gData.m_update == 2) {
        lData = (gData.m_minute/10)%10;
        GClock_writeData(2, lData);
        gData.m_update = 3;
    }
    else if(gData.m_update == 3) {
        lData = gData.m_minute%10;
        GClock_writeData(3, lData);
        gData.m_update = 0;
    }
}
//===============================================
void GClock_updateDP() {
    DP_PIN = !DP_PIN;
}
//===============================================
void GClock_updateSecond() {
    gData.m_second++;
    if(gData.m_second == 60) {
        gData.m_second = 0;
        gData.m_minute++;
    }
    if(gData.m_minute == 60) {
        gData.m_minute = 0;
        gData.m_hour++;
    }
    if(gData.m_hour == 24) {
        gData.m_hour = 0;
    }
}
//===============================================
