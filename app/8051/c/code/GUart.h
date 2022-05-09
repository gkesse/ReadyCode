//===============================================
#ifndef _GUart_
#define _GUart_
//===============================================
#include "GInclude.h"
//===============================================
void GUart_Init(uint baud);
void GUart_Write_Char(uchar d);
void GUart_Read_Char_Update();
uchar GUart_Read_Char();
void GUart_Clear_Read_Char();
//===============================================
#endif
//===============================================
