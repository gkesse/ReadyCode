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

    while (lBytes > 0) {
        printf("[ INFO ] %s\n", lBuffer);
        lBytes = lSocket.receiveBytes(lBuffer, BUFFER_SIZE);
    }
}
//===============================================
