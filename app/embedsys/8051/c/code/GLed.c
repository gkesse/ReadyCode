//===============================================
#include "GLed.h"
#include "GButton.h"
//===============================================
#define LED_PORT P3
//===============================================
typedef enum _eGState {
    OFF,
    UP,
    DOWN,
    LEFT,
    RIGHT
} eGState;
//===============================================
sbit g_led_up = LED_PORT^0;
sbit g_led_down = LED_PORT^1;
sbit g_led_left = LED_PORT^2;
sbit g_led_right = LED_PORT^3;
//===============================================
void GLed_Init() {
    g_led_up = 1;
    g_led_down = 1;
    g_led_left = 1;
    g_led_right = 1;
}
//===============================================
void GLed_Update() {
    uchar l_button_state = GButton_Get_State();
    if(l_button_state == UP) {
        g_led_up = !g_led_up;
        g_led_down = 1;
        g_led_left = 1;
        g_led_right = 1;
    }
    else if(l_button_state == DOWN) {
        g_led_down = !g_led_down;
        g_led_up = 1;
        g_led_left = 1;
        g_led_right = 1;
    }
    else if(l_button_state == LEFT) {
        g_led_left = !g_led_left;
        g_led_up = 1;
        g_led_down = 1;
        g_led_right = 1;
    }
    else if(l_button_state == RIGHT) {
        g_led_right = !g_led_right;
        g_led_up = 1;
        g_led_down = 1;
        g_led_left = 1;
    }
    else if(l_button_state == OFF) {
        g_led_up = 1;
        g_led_down = 1;
        g_led_left = 1;
        g_led_right = 1;
    }
}
//===============================================
