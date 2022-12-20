//===============================================
#include "GSocketEcho.h"
#include "GLog.h"
//===============================================
GSocketEcho::GSocketEcho()
: GSocket() {
}
//===============================================
GSocketEcho::~GSocketEcho() {

}
//===============================================
bool GSocketEcho::runThreadCB() {
    runRequest();
    sendResponse();
    close(m_socket);
    delete this;
    return true;
}
//===============================================
bool GSocketEcho::runRequest() {
    readDatas(m_dataIn);
    m_dataOut = GFORMAT("[SERVER] : %s", m_dataIn.c_str());
    sendDatas(m_dataOut);
    return true;
}
//===============================================
