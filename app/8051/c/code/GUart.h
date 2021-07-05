//===============================================
#ifndef _GUart_
#define _GUart_
//===============================================
#include "GInclude.h"
//===============================================
void GUart_Init(uint baud);
void GUart_Write_Char(uchar d);
void GUart_Write_String(const uchar* d);
//===============================================
#endif
//===============================================
