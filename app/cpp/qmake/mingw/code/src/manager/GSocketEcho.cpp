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
    m_dataIn = GFORMAT("%*d%s", DATA_LENGTH_SIZE, m_dataIn.size(), m_dataIn.c_str());
    sendData(m_dataIn);
    GString lHeader;
    readData(lHeader, DATA_LENGTH_SIZE);
    int lHeaderSize = lHeader.size();
    int lDataSize = lHeader.substr(0, DATA_LENGTH_SIZE).toInt();
    int lTotalSize = lDataSize + DATA_LENGTH_SIZE;
    int lDiffSize = lTotalSize - lHeaderSize;
    m_dataOut = lHeader.substr(DATA_LENGTH_SIZE);
    readData(m_dataOut, lDiffSize);
    return true;
}
//===============================================
