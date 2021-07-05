//===============================================
#include "GUart.h"
//===============================================
#define OSC_FREQ (11059200UL)
#define OSC_PER_INST (12) 
//===============================================
#define PRELOAD(baud) (256 - (uchar)((((ulong)OSC_FREQ / 100) * 3125) / ((ulong)baud * OSC_PER_INST * 1000)));
//===============================================
void GUart_Init(uint baud) {
    TMOD |= 0x20;
    TH1 = PRELOAD(baud);
    SCON = 0x50;
    TR1 = 1;
}
//===============================================
void GUart_Write_Char(uchar d) {
    SBUF = d;
	while (TI == 0);
	TI = 0;
}
//===============================================
void GUart_Write_String(const uchar* d) {
    uchar i;
    for(i = 0; d[i] != '\0'; i++) {
        GUart_Write_Char(d[i]);
    }
}
//===============================================
