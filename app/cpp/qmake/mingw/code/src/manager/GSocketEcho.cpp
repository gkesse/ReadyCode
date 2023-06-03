//===============================================
#include "GSocketEcho.h"
//===============================================
GSocketEcho::GSocketEcho()
: GSocket() {

}
//===============================================
GSocketEcho::~GSocketEcho() {

}
//===============================================
bool GSocketEcho::onCallServer() {
    sendDatas(m_dataIn);
    readDatas(m_dataOut);
    return true;
}
//===============================================
