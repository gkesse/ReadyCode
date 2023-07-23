//===============================================
#ifndef _GSch_
#define _GSch_
//===============================================
#include "GInclude.h"
//===============================================
void GSch_init(uchar _ms);
void GSch_addTask(void (*_pTask)(), const uint _delay, const uint _period);
void GSch_start();
void GSch_dispatchTasks();
//===============================================
#endif
//===============================================
