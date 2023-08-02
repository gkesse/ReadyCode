//===============================================
#include "GPort2.h"
//===============================================
sbit P0_0 = P0^0;
sbit P0_1 = P0^1;
sbit P0_2 = P0^2;
sbit P0_3 = P0^3;
sbit P0_4 = P0^4;
sbit P0_5 = P0^5;
sbit P0_6 = P0^6;
sbit P0_7 = P0^7;
//===============================================
sbit P1_0 = P1^0;
sbit P1_1 = P1^1;
sbit P1_2 = P1^2;
sbit P1_3 = P1^3;
sbit P1_4 = P1^4;
sbit P1_5 = P1^5;
sbit P1_6 = P1^6;
sbit P1_7 = P1^7;
//===============================================
sbit P2_0 = P2^0;
sbit P2_1 = P2^1;
sbit P2_2 = P2^2;
sbit P2_3 = P2^3;
sbit P2_4 = P2^4;
sbit P2_5 = P2^5;
sbit P2_6 = P2^6;
sbit P2_7 = P2^7;
//===============================================
sbit P3_0 = P3^0;
sbit P3_1 = P3^1;
sbit P3_2 = P3^2;
sbit P3_3 = P3^3;
sbit P3_4 = P3^4;
sbit P3_5 = P3^5;
sbit P3_6 = P3^6;
sbit P3_7 = P3^7;
//===============================================
void GPort2_writePort(uchar _port, uchar _data) {
    if(_port == 0) {
        P0 = _data;
    }
    else if(_port == 1) {
        P1 = _data;
    }
    else if(_port == 2) {
        P2 = _data;
    }
    else if(_port == 3) {
        P3 = _data;
    }
}
//===============================================
void GPort2_writePin(uchar _port, uchar _pin, ubit _data) {
    if(_port == 0) {
        if(_pin == 0) P0_0 = _data;
        else if(_pin == 1) P0_1 = _data;
        else if(_pin == 2) P0_2 = _data;
        else if(_pin == 3) P0_3 = _data;
        else if(_pin == 4) P0_4 = _data;
        else if(_pin == 5) P0_5 = _data;
        else if(_pin == 6) P0_6 = _data;
        else if(_pin == 7) P0_7 = _data;
    }
    else if(_port == 1) {
        if(_pin == 0) P1_0 = _data;
        else if(_pin == 1) P1_1 = _data;
        else if(_pin == 2) P1_2 = _data;
        else if(_pin == 3) P1_3 = _data;
        else if(_pin == 4) P1_4 = _data;
        else if(_pin == 5) P1_5 = _data;
        else if(_pin == 6) P1_6 = _data;
        else if(_pin == 7) P1_7 = _data;
    }
    else if(_port == 2) {
        if(_pin == 0) P2_0 = _data;
        else if(_pin == 1) P2_1 = _data;
        else if(_pin == 2) P2_2 = _data;
        else if(_pin == 3) P2_3 = _data;
        else if(_pin == 4) P2_4 = _data;
        else if(_pin == 5) P2_5 = _data;
        else if(_pin == 6) P2_6 = _data;
        else if(_pin == 7) P2_7 = _data;
    }
    else if(_port == 3) {
        if(_pin == 0) P3_0 = _data;
        else if(_pin == 1) P3_1 = _data;
        else if(_pin == 2) P3_2 = _data;
        else if(_pin == 3) P3_3 = _data;
        else if(_pin == 4) P3_4 = _data;
        else if(_pin == 5) P3_5 = _data;
        else if(_pin == 6) P3_6 = _data;
        else if(_pin == 7) P3_7 = _data;
    }
}
//===============================================
