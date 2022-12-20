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
bool GSocketEcho::onCallServer() {
    sendData(m_dataIn);
    readData(m_dataOut, 487);
    return true;
}
//===============================================
