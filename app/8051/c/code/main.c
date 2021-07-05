//===============================================
#include "GSch.h"
#include "GUart.h"
//===============================================
static void GTask_Init() {
    GUart_Init(9600);
    GUart_Write_String("Bonjour tout le monde\n");
    GUart_Write_String("Bienvenue sur ReadyDev\n");
}
//===============================================
static void GTask_Update() {

}
//===============================================
void main() {
    GSch_Init(1);
    GTask_Init();
    GSch_Add_Task(GTask_Update, 0, 0);
    GSch_Start();
    while(1) {
        GSch_Dispatch_Tasks();
    }
}
//===============================================