//===============================================
#include "GSch.h"
#include "GUart.h"
//===============================================
static void GTask_Init() {
    GUart_Init(9600);
}
//===============================================
static void GTask_Update() {
    uchar l_data = GUart_Read_Char();
    if(l_data != 0) {
        GUart_Write_Char(l_data);
        GUart_Clear_Read_Char();
    }
}
//===============================================
void main() {
    GSch_Init(1);
    GTask_Init();
    GSch_Add_Task(GUart_Read_Char_Update, 0, 100);
    GSch_Add_Task(GTask_Update, 1, 100);
    GSch_Start();
    while(1) {
        GSch_Dispatch_Tasks();
    }
}
//===============================================