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
    GString lSize = GFORMAT("%10d", _dataIn.size());
    sendData(lSize);
    sendData(_dataIn);
    readData(lSize, 10);
    readData(_dataOut, lSize.toInt());
    return true;
}
//===============================================
