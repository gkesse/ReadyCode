//===============================================
#ifndef _GPort_
#define	_GPort_
//===============================================
#include "GInclude.h"
//===============================================
void GPort_configPort(uchar _port, uchar _data);
void GPort_configPin(uchar _port, uchar _pin, GBit _data);
void GPort_writePort(uchar _port, uchar _data);
void GPort_writePin(uchar _port, uchar _pin, GBit _data);
//===============================================
#endif
//===============================================
