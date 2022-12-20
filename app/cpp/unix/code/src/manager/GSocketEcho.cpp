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
    GString lHeader;
    readData(lHeader, DATA_LENGTH_SIZE);
    int lHeaderSize = lHeader.size();
    int lDataSize = lHeader.substr(0, DATA_LENGTH_SIZE).toInt();
    int lTotalSize = lDataSize + DATA_LENGTH_SIZE;
    int lDiffSize = lTotalSize - lHeaderSize;
    m_dataIn = lHeader.substr(DATA_LENGTH_SIZE);
    readData(m_dataIn, lDiffSize);

    m_dataIn = GFORMAT("[SERVER] : %s", m_dataIn.c_str());
    m_dataOut = GFORMAT("%*d%s", DATA_LENGTH_SIZE, m_dataOut.size(), m_dataOut.c_str());
    sendData(m_dataOut);
    return true;
}
//===============================================
