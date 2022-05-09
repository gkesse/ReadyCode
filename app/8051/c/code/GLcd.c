//===============================================
#include "GLcd.h"
#include "GDelay.h"
//===============================================
#define LCD_DATA_PORT P1
#define LCD_CMD_PORT P3
//===============================================
sbit g_lcd_en = LCD_CMD_PORT^0;
sbit g_lcd_rw = LCD_CMD_PORT^1;
sbit g_lcd_rs = LCD_CMD_PORT^2;
//===============================================
void GLcd_Init() {
    GLcd_Write_Cmd(LCD_CMD_MODE_8_BIT_2_LINES_5x7);
    GDelay_60us(10);
    GLcd_Write_Cmd(LCD_CMD_DISPLAY_ON_CURSOR_OFF_BLINK_OFF);
    GDelay_60us(10);
    GLcd_Write_Cmd(LCD_CMD_CURSOR_INCREMENT);
    GDelay_60us(10);
    GLcd_Write_Cmd(LCD_CMD_DISPLAY_CLEAR);
    GDelay_60us(10);
    GLcd_Write_Cmd(LCD_CMD_CURSOR_POS_R0_C0);
    GDelay_60us(10);
}
//===============================================
void GLcd_Write_Cmd(uchar d) {
    LCD_DATA_PORT = d;
    g_lcd_rs = 0;
    g_lcd_rw = 0;
    g_lcd_en = 1;
    GDelay_60us(1);
    g_lcd_en = 0;
}
//===============================================
void GLcd_Write_Pos(uchar row, uchar col) {
    uchar l_pos = LCD_CMD_CURSOR_POS_R0_C0;
    if(row == 1) {l_pos = LCD_CMD_CURSOR_POS_R1_C0;}
    l_pos += col;
    GLcd_Write_Cmd(l_pos);
}
//===============================================
void GLcd_Write_Char(uchar d) {
    LCD_DATA_PORT = d;
    g_lcd_rs = 1;
    g_lcd_rw = 0;
    g_lcd_en = 1;
    GDelay_60us(1);
    g_lcd_en = 0;
}
//===============================================
void GLcd_Write_String(const uchar* d) {
    uchar i;
    for(i = 0; d[i] != '\0'; i++) {
        GLcd_Write_Char(d[i]);
    }
}
//===============================================