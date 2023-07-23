//===============================================
#include "GPort.h"
//===============================================
void GPort_Data_Write(uchar port, uchar d) {
    if(port == 0) {P0 = d;}
    else if(port == 1) {P1 = d;}
    else if(port == 2) {P2 = d;}
    else if(port == 3) {P3 = d;}
}
//=============================================== 
void GPort_Bit_Write(uchar port, uchar pin, bit d) {
    uchar l_mask = 0x01;
    l_mask <<= pin;
    if(port == 0) {P0 = (d == 0) ? (P0 & (~l_mask)) : (P0 | l_mask);}
    else if(port == 1) {P1 = (d == 0) ? (P1 & (~l_mask)) : (P1 | l_mask);}
    else if(port == 2) {P2 = (d == 0) ? (P2 & (~l_mask)) : (P2 | l_mask);}
    else if(port == 3) {P3 = (d == 0) ? (P3 & (~l_mask)) : (P3 | l_mask);}
}
//=============================================== 
