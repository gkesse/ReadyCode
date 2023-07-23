//===============================================
#ifndef _GSch_
#define _GSch_
//===============================================
#include "GInclude.h"
//===============================================
void GSch_Init(uchar ms);
void GSch_Add_Task(void (*pTask)(), const uint delay, const uint period);
void GSch_Start();
void GSch_Dispatch_Tasks();
//===============================================
#endif
//===============================================
