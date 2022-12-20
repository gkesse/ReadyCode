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
    GString lSize;
    readData(lSize, 10);
    readData(m_dataIn, lSize.toInt());
    m_dataOut = GFORMAT("[SERVER] : %s", m_dataIn.c_str());
    return true;
}
//===============================================
