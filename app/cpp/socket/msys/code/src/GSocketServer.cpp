//===============================================
#include "GSocketServer.h"
#include "GFile.h"
#include "GString.h"
#include "GSocket.h"
//===============================================
GSocketServer::GSocketServer() {

}
//===============================================
GSocketServer::~GSocketServer() {

}
//===============================================
void GSocketServer::run(int argc, char** argv) {
    WSADATA lWsaData;
    WSAStartup(MAKEWORD(2, 2), &lWsaData);
    const auto lSocket = socket(AF_INET, SOCK_STREAM, 0);

    SOCKADDR_IN lAddress;
    lAddress.sin_addr.s_addr = INADDR_ANY;
    lAddress.sin_family = AF_INET;
    lAddress.sin_port = htons(5555);

    bind(lSocket, reinterpret_cast<SOCKADDR*>(&lAddress), sizeof(lAddress));
    listen(lSocket, 5);

    SOCKADDR_IN lAddress2;
    int lAddressSize2 = sizeof(lAddress2);
    //===============================================
    while(1) {
        SOCKET lSocket2 = accept(lSocket, reinterpret_cast<SOCKADDR*>(&lAddress2), &lAddressSize2);
        auto lAsync = std::async(std::launch::async, on_client_connect, lSocket2);
    }
    //===============================================
    closesocket(lSocket);
    WSACleanup();
}
//===============================================
void GSocketServer::on_client_connect(SOCKET _socket) {
    char lBuffer[1024];
    recv(_socket, lBuffer, sizeof(lBuffer), 0);
    std::cout << "Client says: " << lBuffer << std::endl;
    memset(lBuffer, 0, sizeof(lBuffer));
    closesocket(_socket);
}
//===============================================
