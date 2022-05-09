//===============================================
#include "GUart.h"
//===============================================
#define OSC_FREQ (11059200UL)
#define OSC_PER_INST (12) 
//===============================================
#define PRELOAD(baud) (256 - (uchar)((((ulong)OSC_FREQ / 100) * 3125) / ((ulong)baud * OSC_PER_INST * 1000)));
//===============================================
static uchar g_read_char;
//===============================================
void GUart_Init(uint baud) {
    TMOD |= 0x20;
    TH1 = PRELOAD(baud);
    SCON = 0x50;
    TR1 = 1;
    g_read_char = 0;
}
//===============================================
void GUart_Write_Char(uchar d) {
    if(d == '\n') {d = 0x0D;}
    SBUF = d;
	while (TI == 0);
	TI = 0;
}
//===============================================
void GUart_Read_Char_Update() {
    if(RI) {
        g_read_char = SBUF;
        RI = 0;
    }    
}
//===============================================
uchar GUart_Read_Char() {
    return g_read_char;    
}
//===============================================
void GUart_Clear_Read_Char() {
    g_read_char = 0;    
}
//===============================================
