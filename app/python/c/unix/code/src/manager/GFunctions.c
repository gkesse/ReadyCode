//===============================================
#include "GFunctions.h"
//===============================================
static char* gFunctions_Buffer = 0;
//===============================================
char* sformat(const char* _format, ...) {
    va_list lArgs;
    va_start(lArgs, _format);
    int lSize = vsnprintf(0, 0, _format, lArgs);
    char* lBuffer = (char*)malloc(sizeof(char)*(lSize + 1));
    vsnprintf(lBuffer, lSize + 1, _format, lArgs);
    va_end(lArgs);
    free(gFunctions_Buffer);
    gFunctions_Buffer = lBuffer;
    return lBuffer;
}
//===============================================
void GFunctions_delete() {
    free(gFunctions_Buffer);
}
//===============================================
