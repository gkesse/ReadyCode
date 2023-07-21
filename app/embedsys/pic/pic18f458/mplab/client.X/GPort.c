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
        if(_pin == 0) TRISAbits.TRISA0 = _data;
        else if(_pin == 1) TRISAbits.TRISA1 = _data;
        else if(_pin == 2) TRISAbits.TRISA2 = _data;
        else if(_pin == 3) TRISAbits.TRISA3 = _data;
        else if(_pin == 4) TRISAbits.TRISA4 = _data;
        else if(_pin == 5) TRISAbits.TRISA5 = _data;
        else if(_pin == 6) TRISAbits.TRISA6 = _data;
    }
    else if(_port == 1) {
        if(_pin == 0) TRISBbits.TRISB0 = _data;
        else if(_pin == 1) TRISBbits.TRISB1 = _data;
        else if(_pin == 2) TRISBbits.TRISB2 = _data;
        else if(_pin == 3) TRISBbits.TRISB3 = _data;
        else if(_pin == 4) TRISBbits.TRISB4 = _data;
        else if(_pin == 5) TRISBbits.TRISB5 = _data;
        else if(_pin == 6) TRISBbits.TRISB6 = _data;
        else if(_pin == 7) TRISBbits.TRISB7 = _data;
    }
    else if(_port == 2) {
        if(_pin == 0) TRISCbits.TRISC0 = _data;
        else if(_pin == 1) TRISCbits.TRISC1 = _data;
        else if(_pin == 2) TRISCbits.TRISC2 = _data;
        else if(_pin == 3) TRISCbits.TRISC3 = _data;
        else if(_pin == 4) TRISCbits.TRISC4 = _data;
        else if(_pin == 5) TRISCbits.TRISC5 = _data;
        else if(_pin == 6) TRISCbits.TRISC6 = _data;
        else if(_pin == 7) TRISCbits.TRISC7 = _data;
    }
    else if(_port == 3) {
        if(_pin == 0) TRISDbits.TRISD0 = _data;
        else if(_pin == 1) TRISDbits.TRISD1 = _data;
        else if(_pin == 2) TRISDbits.TRISD2 = _data;
        else if(_pin == 3) TRISDbits.TRISD3 = _data;
        else if(_pin == 4) TRISDbits.TRISD4 = _data;
        else if(_pin == 5) TRISDbits.TRISD5 = _data;
        else if(_pin == 6) TRISDbits.TRISD6 = _data;
        else if(_pin == 7) TRISDbits.TRISD7 = _data;
    }
    else if(_port == 4) {
        if(_pin == 0) TRISEbits.TRISE0 = _data;
        else if(_pin == 1) TRISEbits.TRISE1 = _data;
        else if(_pin == 2) TRISEbits.TRISE2 = _data;
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
