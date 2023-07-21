//===============================================
#include "GPort.h"
//===============================================
void main() {
    GPort_configPort(1, 0x00);
    GPort_writePort(1, 0xFF);
    
    while(1) {
        GPort_writePin(1, 1, 1);
        GDelay_ms(500);
        GPort_writePin(1, 1, 0);
        GDelay_ms(500);
    }
}
//===============================================
