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
    runRequest()();
    sendResponse();
    close(m_socket);
    delete this;
    return true;
}
//===============================================
bool GSocketEcho::runRequest() {
    GString lSize;
    GString lData;
    readData(lSize, 10);
    readData(lData, lSize.toInt());
    m_dataIn = lData;
    m_dataOut = lData;
    return true;
}
//===============================================
