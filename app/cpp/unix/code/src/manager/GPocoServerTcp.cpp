//===============================================
#include "GPocoServerTcp.h"
#include "GLog.h"
#include "GFormat.h"
//===============================================
GPocoServerTcp::GPocoServerTcp(const Poco::Net::StreamSocket& _socket)
: Poco::Net::TCPServerConnection(_socket) {

}
//===============================================
GPocoServerTcp::~GPocoServerTcp() {

}
//===============================================
void GPocoServerTcp::run() {
    Poco::Net::StreamSocket& lSocket = socket();
    char lBuffer[BUFFER_SIZE];
    int lBytes = lSocket.receiveBytes(lBuffer, BUFFER_SIZE);
    std::string lDataIn = "";

    while (lBytes > 0) {
        lBuffer[lBytes] = 0;
        lDataIn += lBuffer;
        lBytes = lSocket.receiveBytes(lBuffer, BUFFER_SIZE);
    }

    printf("[ INFO ] %s\n", lDataIn.c_str());
}
//===============================================
