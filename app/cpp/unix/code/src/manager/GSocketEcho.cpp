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
    readEcho()();
    sendResponse();
    close(m_socket);
    delete this;
    return true;
}
//===============================================
bool GSocketEcho::readEcho() {
    char lBuffer[BUFFER_SIZE + 1];
    int lBytes = readData(lBuffer, BUFFER_SIZE);
    if(lBytes <= 0) return false;
    lBuffer[lBytes] = 0;
    m_dataIn = lBuffer;
    m_dataOut = m_dataIn;
    return true;
}
//===============================================
