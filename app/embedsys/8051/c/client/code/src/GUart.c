//===============================================
#include "GUart.h"
//===============================================
#define PRELOAD(baud) (256 - (uchar)((((ulong)OSC_FREQ / 100) * 3125) / ((ulong)baud * OSC_PER_INST * 1000)));
//===============================================
typedef struct _sGData sGData;
//===============================================
#define WRITE_BUFFER_MAX    (8)
#define READ_BUFFER_MAX     (8)
//===============================================
struct _sGData {
    uchar m_writeData[WRITE_BUFFER_MAX];
    uchar m_readData[READ_BUFFER_MAX];
    uchar m_writeIndexIn;
    uchar m_writeIndexOut;
    uchar m_readIndexIn;
    uchar m_readIndexOut;
};
//===============================================
static sGData gData = {0, 0, 0, 0, 0, 0};
//===============================================
static void GUart_writeOff(uchar _max);
static void GUart_readOff(uchar _max);
static void GUart_writeData(uchar _data);
//===============================================
// private
//===============================================
static void GUart_writeOff(uchar _max) {
    uchar i = 0;
    while(1) {
        if(i == WRITE_BUFFER_MAX) break;
        if(i == _max) break;
        gData.m_writeData[i] = '\0';
        i++;
    }
}
//===============================================
static void GUart_readOff(uchar _max) {
    uchar i = 0;
    while(1) {
        if(i == READ_BUFFER_MAX) break;
        if(i == _max) break;
        gData.m_readData[i] = '\0';
        i++;
    }
}
//===============================================
static void GUart_writeData(uchar _data) {
    if(_data == '\n') {_data = 0x0D;}
    SBUF = _data;
    while(TI == 0);
    TI = 0;
}
//===============================================
// public
//===============================================
void GUart_init(uint _baud) {
    GUart_writeOff(WRITE_BUFFER_MAX);
    GUart_readOff(READ_BUFFER_MAX);
    TMOD |= 0x20;
    TL1 = PRELOAD(_baud);
    TH1 = PRELOAD(_baud);
    SCON = 0x50;
    TR1 = 1;
}
//===============================================
void GUart_writeChar(const char* _data) {
    uchar i = 0;
    while(1) {
        if(gData.m_writeIndexIn == WRITE_BUFFER_MAX) break;
        if(_data[i] == '\0') break;
        gData.m_writeData[gData.m_writeIndexIn] = _data[i];
        gData.m_writeIndexIn++;
        i++;
    }
}
//===============================================
void GUart_updateWrite() {
    if(gData.m_writeIndexOut == gData.m_writeIndexIn) {
        if(gData.m_writeIndexOut != 0) {
            GUart_writeOff(gData.m_writeIndexOut);
        }
        gData.m_writeIndexIn = 0;
        gData.m_writeIndexOut = 0;
    }
    else {
        GUart_writeData(gData.m_writeData[gData.m_writeIndexOut]);
        gData.m_writeIndexOut++;
    }
}
//===============================================
void GUart_updateRead() {
    uchar lData;
    if(RI) {
        lData = SBUF;
        if(gData.m_readIndexIn < READ_BUFFER_MAX) {
            gData.m_readData[gData.m_readIndexIn] = lData;
            P1 = gData.m_readData[gData.m_readIndexIn];
            gData.m_readIndexIn++;
        }
        RI = 0;
    }
}
//===============================================
void GUart_updateReadWrite() {
    if(gData.m_readIndexOut == gData.m_readIndexIn) {
        if(gData.m_readIndexOut != 0) {
            GUart_readOff(gData.m_readIndexOut);
        }
        gData.m_readIndexIn = 0;
        gData.m_readIndexOut = 0;
    }
    else {
        GUart_writeData(gData.m_readData[gData.m_readIndexOut]);
        gData.m_readIndexOut++;
    }
}
//===============================================
