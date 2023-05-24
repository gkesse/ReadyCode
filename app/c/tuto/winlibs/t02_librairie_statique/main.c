//===============================================
#include "GHello.h"
#include "GMath.h"
//===============================================
int main(int _argc, char** _argv) {
    GHello_sayHello("WinLibs");
    printf("22 + 7 = %.2f\n", GMath_add(22, 7));
    printf("22 - 7 = %.2f\n", GMath_sub(22, 7));
    printf("22 * 7 = %.2f\n", GMath_mul(22, 7));
    printf("22 / 7 = %.2f\n", GMath_div(22, 7));
    printf("22 quo 7 = %d\n", GMath_quo(22, 7));
    printf("22 mod 7 = %d\n", GMath_mod(22, 7));
    return 0;
}
//===============================================
