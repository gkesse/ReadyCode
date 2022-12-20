//===============================================
#include "GSocketEcho.h"
#include "GLog.h"
//===============================================
GSocketEcho::GSocketEcho(const GString& _code)
: GSocket(_code) {

}
//===============================================
GSocketEcho::~GSocketEcho() {

}
//===============================================
bool GSocketEcho::onCallServer(const GString& _dataIn, GString& _dataOut) {
    sendData(_dataIn);
    readData(_dataOut, 1000);
    return true;
}
//===============================================
