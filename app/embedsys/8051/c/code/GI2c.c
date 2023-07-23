//===============================================
#include "GI2c.h"
//===============================================
#define I2C_PORT P0
//===============================================
sbit g_sda_pin = I2C_PORT^0;
sbit g_scl_pin = I2C_PORT^1;
//===============================================
void GI2c_Init(){
    g_sda_pin = 1;
    g_scl_pin = 1;
}
//===============================================
void GI2c_Start(){
    g_scl_pin = 1;
    GI2c_Delay();
    g_sda_pin = 0;
    GI2c_Delay();
    g_scl_pin = 0;
    GI2c_Delay();
}
//===============================================
void GI2c_Restart(){
    g_sda_pin = 1;
    g_scl_pin = 1;
    g_sda_pin = 0;
    g_scl_pin = 0;
}
//===============================================
void GI2c_Stop(){
    g_sda_pin = 0;
    GI2c_Delay();
    g_scl_pin = 1;
    GI2c_Delay();
    g_sda_pin = 1;
    GI2c_Delay();
}
//===============================================
void GI2c_Ack(){
    GI2c_Delay();
    g_sda_pin = 0;
    GI2c_Delay();
    g_scl_pin = 1;
    GI2c_Delay();
    g_scl_pin = 0;
    GI2c_Delay();
    g_sda_pin = 1;
    GI2c_Delay();
}
//===============================================
void GI2c_Nak(){
    g_sda_pin = 1;
    g_scl_pin = 1;
    g_scl_pin = 0;
    g_sda_pin = 1;
}
//===============================================
void GI2c_Write_Char(uchar d){
    uchar i;
    for (i = 0; i < 8; i++) {
        g_sda_pin = (d & 0x80) ? 1 : 0;
        g_scl_pin = 1;
        GI2c_Delay();
        g_scl_pin = 0;
        GI2c_Delay();
        d <<= 1;
    }
    g_sda_pin = 1;
    GI2c_Delay();
    g_scl_pin = 1;
    GI2c_Delay();
    if (g_sda_pin == 1) {
        g_scl_pin = 0;
        GI2c_Delay();
    }
    g_sda_pin = 1;
    g_scl_pin = 1;
}
//===============================================
char GI2c_Read(uchar lastone) {
    uchar i, d = 0;
    for (i = 0; i < 8; i++) {
        g_scl_pin = 1;
        GI2c_Delay();
        if(g_sda_pin) d |=1;
        if(i<7) d<<=1;
        g_scl_pin = 0;
        GI2c_Delay();
    }
    g_sda_pin = lastone;
    g_scl_pin = 1;
    GI2c_Delay();
    g_scl_pin = 0;
    g_sda_pin = 1;
    g_scl_pin = 1;
    GI2c_Delay();
    return d;
}

void GI2c_SendAddr(uchar addr, uchar rd){
    GI2c_Start();
    GI2c_Send(addr+rd);
}
void GI2c_Delay(){
    unsigned int i;
    for (i = 0; i < 4000; i++);
    return;
}
//===============================================
