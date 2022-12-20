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
    m_dataOut += ""
            "The WSAGetLastError function returns the last "
            "error that occurred for the calling thread. "
            "When a particular Windows Sockets function indicates "
            "an error has occurred, this function should be called "
            "immediately to retrieve the extended error code for the "
            "failing function call. These error codes and a short text "
            "description associated with an error code are defined in the Winerror.h "
            "header file. The FormatMessage function can be used to obtain "
            "the message string for the returned error.";
    sendDatas(m_dataOut);
    return true;
}
//===============================================
