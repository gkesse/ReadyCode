//===============================================
#include "GSocket.h"
//===============================================
GSocket::GSocket() {
    m_address = "0.0.0.0";
    m_port = 8585;
    m_listen = 5;
}
//===============================================
GSocket::~GSocket() {

}
//===============================================
void GSocket::setAddress(const std::string& address) {
    m_address = address;
}
//===============================================
void GSocket::setPort(int port) {
    m_port = port;
}
//===============================================
void GSocket::setListen(int listen) {
    m_listen = listen;
}
//===============================================
void GSocket::startTCP() {
    WSADATA lWsaData;
    WSAStartup(MAKEWORD(2, 2), &lWsaData);
    SOCKET lSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    sockaddr_in lAddress;
    lAddress.sin_family = AF_INET;
    InetPton(AF_INET, m_address.c_str(), &lAddress.sin_addr.s_addr);
    lAddress.sin_port = htons(m_port);
    memset(&lAddress.sin_zero, 0, sizeof(lAddress.sin_zero));
    bind(lSocket, (SOCKADDR *)& lAddress, sizeof(lAddress));
    listen(lSocket, m_listen);
    SOCKET lSocket2 = accept(lSocket, NULL, NULL);
    closesocket(lSocket);
    //===============================================
    char lBuffer[BUFFER_SIZE + 1];
    int lBytes = recv(lSocket2, lBuffer, BUFFER_SIZE, 0);
    GString lString;
    lString.setData(lBuffer, lBytes);
    std::cout << lString << "...\n";
    sprintf(lBuffer, "%s", "OK");
    send(lSocket2, lBuffer, strlen(lBuffer), 0);
    //===============================================
    shutdown(lSocket2, SD_SEND);
    closesocket(lSocket2);
    WSACleanup();
}
//===============================================
void GSocket::callTCP(const char* dataIn, GString& dataOut) {
    WSADATA lWsaData;
    WSAStartup(MAKEWORD(2, 2), &lWsaData);
    SOCKET lSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    sockaddr_in lAddress;
    lAddress.sin_family = AF_INET;
    InetPton(AF_INET, m_address.c_str(), &lAddress.sin_addr.s_addr);
    lAddress.sin_port = htons(m_port);
    memset(&lAddress.sin_zero, 0, sizeof(lAddress.sin_zero));
    connect(lSocket, (SOCKADDR*)&lAddress, sizeof(lAddress));
    //===============================================
    char lBuffer[BUFFER_SIZE + 1];
    send(lSocket, dataIn, strlen(dataIn), 0);
    int lBytes = recv(lSocket, lBuffer, BUFFER_SIZE, 0);
    dataOut.setData(lBuffer, lBytes);
    //===============================================
    shutdown(lSocket, SD_SEND);
    closesocket(lSocket);
    WSACleanup();
}
//===============================================
