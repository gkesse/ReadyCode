//===============================================
#ifndef _GLcd_
#define _GLcd_
//===============================================
#include "GInclude.h"
//===============================================
#define LCD_CMD_MODE_8_BIT_2_LINES_5x7 0x38
#define LCD_CMD_MODE_4_BIT 0x02
#define LCD_CMD_MODE_4_BIT_2_LINES_5x7 0x28
#define LCD_CMD_DISPLAY_ON_CURSOR_ON_BLINK_ON 0x0F
#define LCD_CMD_DISPLAY_ON_CURSOR_OFF_BLINK_OFF 0x0C
#define LCD_CMD_DISPLAY_CLEAR 0x01
#define LCD_CMD_DISPLAY_SHIFT_LEFT 0x18
#define LCD_CMD_DISPLAY_SHIFT_RIGHT 0x1C
#define LCD_CMD_CURSOR_HOME 0x02
#define LCD_CMD_CURSOR_INCREMENT 0x06
#define LCD_CMD_CURSOR_DECREMENT 0x04
#define LCD_CMD_CURSOR_POS_R0_C0 0x80
#define LCD_CMD_CURSOR_POS_R1_C0 0xC0
//===============================================
void GLcd_Init();
void GLcd_Write_Cmd(uchar d);
void GLcd_Write_Pos(uchar row, uchar col);
void GLcd_Write_Char(uchar d);
void GLcd_Write_String(const char* d);
//===============================================
#endif
//===============================================
