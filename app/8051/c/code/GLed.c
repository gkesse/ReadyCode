//===============================================
#include "GLed.h"
#include "GPort.h"
//===============================================
static uchar g_port;
static uchar g_pin;
//===============================================
void GLed_Init(uchar port, uchar pin) {
    g_port = port;
    g_pin = pin;
    GPort_Data_Write(g_port, 0xF0);
}
//===============================================
void GLed_Update() {

}
//===============================================
