//===============================================
#include "GTask.h"
#include "GPort.h"
//===============================================
static uchar g_port;
static uchar g_data;
static bit g_state = 0;
//===============================================
void GTask_Init(uchar port, uchar d) {
    g_port = port;
    g_data = d;
    GPort_Data_Write(g_port, g_data);
}
//===============================================
void GTask_Update() {
    if(g_state == 0) {
        GPort_Data_Write(g_port, g_data);
        g_state = 1;
    }
    else {
        GPort_Data_Write(g_port, ~g_data);
        g_state = 0;
    }
}
//===============================================
