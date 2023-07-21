//===============================================
#include "GPort.h"
//===============================================
void GPort_configPort(uchar _port, uchar _data) {
    if(_port == 0) {
        TRISA = _data;
    }
    else if(_port == 1) {
        TRISB = _data;
    }
    else if(_port == 2) {
        TRISC = _data;
    }
    else if(_port == 3) {
        TRISD = _data;
    }
    else if(_port == 4) {
        TRISE = _data;
    }
}
//===============================================
void GPort_configPin(uchar _port, uchar _pin, GBit _data) {
    if(_port == 0) {
        if(_pin == 0) TRISA0 = _data;
        else if(_pin == 1) TRISA1 = _data;
        else if(_pin == 2) TRISA2 = _data;
        else if(_pin == 3) TRISA3 = _data;
        else if(_pin == 4) TRISA4 = _data;
        else if(_pin == 5) TRISA5 = _data;
        else if(_pin == 6) TRISA6 = _data;
    }
    else if(_port == 1) {
        if(_pin == 0) TRISB0 = _data;
        else if(_pin == 1) TRISB1 = _data;
        else if(_pin == 2) TRISB2 = _data;
        else if(_pin == 3) TRISB3 = _data;
        else if(_pin == 4) TRISB4 = _data;
        else if(_pin == 5) TRISB5 = _data;
        else if(_pin == 6) TRISB6 = _data;
        else if(_pin == 7) TRISB7 = _data;
    }
    else if(_port == 2) {
        if(_pin == 0) TRISC0 = _data;
        else if(_pin == 1) TRISC1 = _data;
        else if(_pin == 2) TRISC2 = _data;
        else if(_pin == 3) TRISC3 = _data;
        else if(_pin == 4) TRISC4 = _data;
        else if(_pin == 5) TRISC5 = _data;
        else if(_pin == 6) TRISC6 = _data;
        else if(_pin == 7) TRISC7 = _data;
    }
    else if(_port == 3) {
        if(_pin == 0) TRISD0 = _data;
        else if(_pin == 1) TRISD1 = _data;
        else if(_pin == 2) TRISD2 = _data;
        else if(_pin == 3) TRISD3 = _data;
        else if(_pin == 4) TRISD4 = _data;
        else if(_pin == 5) TRISD5 = _data;
        else if(_pin == 6) TRISD6 = _data;
        else if(_pin == 7) TRISD7 = _data;
    }
    else if(_port == 4) {
        if(_pin == 0) TRISE0 = _data;
        else if(_pin == 1) TRISE1 = _data;
        else if(_pin == 2) TRISE2 = _data;
    }
}
//===============================================
void GPort_writePort(uchar _port, uchar _data) {
    if(_port == 0) {
        PORTA = _data;
    }
    else if(_port == 1) {
        PORTB = _data;
    }
    else if(_port == 2) {
        PORTC = _data;
    }
    else if(_port == 3) {
        PORTD = _data;
    }
    else if(_port == 4) {
        PORTE = _data;
    }
}
//===============================================
void GPort_writePin(uchar _port, uchar _pin, GBit _data) {
    if(_port == 0) {
        if(_pin == 0) PORTAbits.RA0 = _data;
        else if(_pin == 1) PORTAbits.RA1 = _data;
        else if(_pin == 2) PORTAbits.RA2 = _data;
        else if(_pin == 3) PORTAbits.RA3 = _data;
        else if(_pin == 4) PORTAbits.RA4 = _data;
        else if(_pin == 5) PORTAbits.RA5 = _data;
        else if(_pin == 6) PORTAbits.RA6 = _data;
    }
    else if(_port == 1) {
        if(_pin == 0) PORTBbits.RB0 = _data;
        else if(_pin == 1) PORTBbits.RB1 = _data;
        else if(_pin == 2) PORTBbits.RB2 = _data;
        else if(_pin == 3) PORTBbits.RB3 = _data;
        else if(_pin == 4) PORTBbits.RB4 = _data;
        else if(_pin == 5) PORTBbits.RB5 = _data;
        else if(_pin == 6) PORTBbits.RB6 = _data;
        else if(_pin == 7) PORTBbits.RB7 = _data;
    }
    else if(_port == 2) {
        if(_pin == 0) PORTCbits.RC0 = _data;
        else if(_pin == 1) PORTCbits.RC1 = _data;
        else if(_pin == 2) PORTCbits.RC2 = _data;
        else if(_pin == 3) PORTCbits.RC3 = _data;
        else if(_pin == 4) PORTCbits.RC4 = _data;
        else if(_pin == 5) PORTCbits.RC5 = _data;
        else if(_pin == 6) PORTCbits.RC6 = _data;
        else if(_pin == 7) PORTCbits.RC7 = _data;
    }
    else if(_port == 3) {
        if(_pin == 0) PORTDbits.RD0 = _data;
        else if(_pin == 1) PORTDbits.RD1 = _data;
        else if(_pin == 2) PORTDbits.RD2 = _data;
        else if(_pin == 3) PORTDbits.RD3 = _data;
        else if(_pin == 4) PORTDbits.RD4 = _data;
        else if(_pin == 5) PORTDbits.RD5 = _data;
        else if(_pin == 6) PORTDbits.RD6 = _data;
        else if(_pin == 7) PORTDbits.RD7 = _data;
    }
    else if(_port == 4) {
        if(_pin == 0) PORTEbits.RE0 = _data;
        else if(_pin == 1) PORTEbits.RE1 = _data;
        else if(_pin == 2) PORTEbits.RE2 = _data;
    }
}
//===============================================
