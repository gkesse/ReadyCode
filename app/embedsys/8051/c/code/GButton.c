//===============================================
#include "GButton.h"
//===============================================
#define BUTTON_PORT P1
//===============================================
typedef enum _eGState {
    OFF,
    UP,
    DOWN,
    LEFT,
    RIGHT
} eGState;
//===============================================
sbit g_button_up = BUTTON_PORT^0;
sbit g_button_down = BUTTON_PORT^1;
sbit g_button_left = BUTTON_PORT^2;
sbit g_button_right = BUTTON_PORT^3;
sbit g_button_off = BUTTON_PORT^4;
//===============================================
static uchar g_button_state;
//===============================================
void GButton_Init() {
    g_button_up = 1;
    g_button_down = 1;
    g_button_left = 1;
    g_button_right = 1;
    g_button_state = OFF;
}
//===============================================
void GButton_Update() {
    if(g_button_up == 0) {
        g_button_state = UP;
    }
    else if(g_button_down == 0) {
        g_button_state = DOWN;
    }
    else if(g_button_left == 0) {
        g_button_state = LEFT;
    }
    else if(g_button_right == 0) {
        g_button_state = RIGHT;
    }
    else if(g_button_off == 0) {
        g_button_state = OFF;
    }
}
//===============================================
uchar GButton_Get_State() {
    return g_button_state;
}
//===============================================
