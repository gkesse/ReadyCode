//===============================================
#ifndef _GUart_
#define _GUart_
//===============================================
#include "GInclude.h"
//===============================================
void GUart_init(uint _baud);
void GUart_writeChar(const char* _data);
void GUart_updateWrite();
void GUart_updateRead();
void GUart_updateReadWrite();
//===============================================
#endif
//===============================================
