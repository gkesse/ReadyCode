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
