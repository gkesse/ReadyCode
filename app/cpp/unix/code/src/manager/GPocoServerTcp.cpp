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
    char lBuffer[256];
    int lBytes = lSocket.receiveBytes(lBuffer, sizeof(lBuffer));
    std::string lDataIn = "";

    while (lBytes > 0) {
        lDataIn += lBuffer;
        lBytes = lSocket.receiveBytes(lBuffer, sizeof(lBuffer));
    }

    std::cout << lDataIn << "\n";
}
//===============================================
