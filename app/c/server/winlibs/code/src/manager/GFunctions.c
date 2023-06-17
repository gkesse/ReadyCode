//===============================================
#include "GFunctions.h"
//===============================================
static char* GFunctions_Buffer = 0;
//===============================================
const char* sformat(const char* _format, ...) {
    va_list lArgs;
    va_start(lArgs, _format);
    int lSize = vsnprintf(0, 0, _format, lArgs);
    char* lBuffer = (char*)malloc(sizeof(char)*(lSize + 1));
    vsnprintf(lBuffer, lSize + 1, _format, lArgs);
    va_end(lArgs);
    free(GFunctions_Buffer);
    GFunctions_Buffer = lBuffer;
    return lBuffer;
}
//===============================================
void GFunctions_delete() {
    free(GFunctions_Buffer);
}
//===============================================
