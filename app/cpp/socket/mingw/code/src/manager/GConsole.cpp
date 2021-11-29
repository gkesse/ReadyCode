//===============================================
#include "GConsole.h"
//===============================================
GConsole::GConsole() {

}
//===============================================
GConsole::~GConsole() {

}
//===============================================
void GConsole::showData(const std::string& _data) {
    printf("%s\n", _data.c_str());
}
//===============================================
void GConsole::showData(int _data) {
    printf("%d\n", _data);
}
//===============================================
void GConsole::showFormat(const char* _format, ...) {
    char lBuffer[BUFFER_SIZE + 1];
    va_list lArgs;
    va_start(lArgs, _format);
    vsprintf(lBuffer, _format, lArgs);
    va_end (lArgs);
    printf("%s\n", lBuffer);
}
//===============================================
