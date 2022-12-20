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
    readData(m_dataIn, 1000);
    m_dataOut = GFORMAT("[SERVER] : %s", m_dataIn.c_str());
    sendData(m_dataOut);
    return true;
}
//===============================================
