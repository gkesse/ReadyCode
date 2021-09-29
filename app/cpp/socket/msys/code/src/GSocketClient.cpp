//===============================================
#include "GSocketClient.h"
#include "GSocket.h"
//===============================================
GSocketClient::GSocketClient() {

}
//===============================================
GSocketClient::~GSocketClient() {

}
//===============================================
void GSocketClient::run(int argc, char** argv) {
    std::string lBuffer = "Bonjour tout le monde";
    WSADATA lWsaData;
    SOCKADDR_IN lAddress;
    WSAStartup(MAKEWORD(2, 0), &lWsaData);
    const auto lSocket = socket(AF_INET, SOCK_STREAM, 0);
    InetPton(AF_INET, "127.0.0.1", &lAddress.sin_addr.s_addr);
    lAddress.sin_family = AF_INET;
    lAddress.sin_port = htons(5555);
    connect(lSocket, reinterpret_cast<SOCKADDR*>(&lAddress), sizeof(lAddress));
    //===============================================
    send(lSocket, lBuffer.c_str(), lBuffer.length(), 0);
    //===============================================
    closesocket(lSocket);
    WSACleanup();
}
//===============================================
