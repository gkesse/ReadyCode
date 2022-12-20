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
    sendDatas(_dataIn);
    readDatas(_dataOut);
    return true;
}
//===============================================
