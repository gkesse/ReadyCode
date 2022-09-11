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

    while (lBytes > 0) {
        std::cout << "Received " << lBytes << " bytes:" << std::endl;
        std::string lMsg;
        Poco::Logger::formatDump(lMsg, lBuffer, lBytes);
        std::cout << lMsg << std::endl;
        lBytes = lSocket.receiveBytes(lBuffer, sizeof(lBuffer));
    }
}
//===============================================
