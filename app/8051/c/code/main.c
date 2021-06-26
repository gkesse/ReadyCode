//===============================================
#include "GSch.h"
#include "G7Seg.h"
//===============================================
static uchar g_counter_port;
static uchar g_counter_data;
//===============================================
static void GTask_Init() {
    g_counter_port = 1;
    g_counter_data = 0;
}
//===============================================
static void GCounter_Update() {
    G7Seg_Digit_Write(g_counter_port, g_counter_data);
    if(++g_counter_data > 9) {
        g_counter_data = 0;
    }
}
//===============================================
void main() {
    GSch_Init(1);
    GTask_Init();
    GSch_Add_Task(GCounter_Update, 0, 500);
    GSch_Start();
    while(1) {
        GSch_Dispatch_Tasks();
    }
}
//===============================================