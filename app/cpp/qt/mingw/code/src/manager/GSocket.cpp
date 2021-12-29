//===============================================
#include "GSocket.h"
#include "GThread.h"
#include "GString.h"
//===============================================
GSocket::GSocket() {
    m_socket = -1;
}
//===============================================
GSocket::~GSocket() {

}
//===============================================
void GSocket::initSocket(int _major, int _minor) {
    WSADATA lWsaData;
    WSAStartup(MAKEWORD(_major, _minor), &lWsaData);
}
//===============================================
void GSocket::createSocketTcp() {
    m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}
//===============================================
void GSocket::cretaeSocketUdp() {
    m_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
}
//===============================================
void GSocket::createAddress(const std::string& _ip, int _port) {
    m_address.sin_family = AF_INET;
    m_address.sin_addr.s_addr = inet_addr(_ip.c_str());
    m_address.sin_port = htons(_port);
    memset(&m_address.sin_zero, 0, sizeof(m_address.sin_zero));
}
//===============================================
void GSocket::listenSocket(int _backlog) {
    listen(m_socket, _backlog);
}
//===============================================
void GSocket::bindSocket() {
    bind(m_socket, (SOCKADDR*)&m_address, sizeof(m_address));
}
//===============================================
void GSocket::connectToServer() {
    connect(m_socket, (SOCKADDR*)(&m_address), sizeof(m_address));
}
//===============================================
void GSocket::acceptConnection(GSocket& _socket) {
    int lSize = sizeof(_socket.m_address);
    _socket.m_socket = accept(m_socket, (SOCKADDR*)&_socket.m_address, &lSize);
}
//===============================================
int GSocket::recvData(std::string& _data) {
    char lBuffer[BUFFER_SIZE + 1];
    int lBytes = recv(m_socket, lBuffer, BUFFER_SIZE, 0);
    if(lBytes > 0) {
        lBuffer[lBytes] = 0;
        _data = lBuffer;
    }
    return lBytes;
}
//===============================================
int GSocket::readData(std::string& _data) {
    _data = "";
    std::string lData;
    int lIndex = 0;
    while(1) {
        int lBytes = recvData(lData);
        if(lBytes <= 0) break;
        lIndex += lBytes;
        _data += lData;
    }
    return lIndex;
}
//===============================================
int GSocket::recvData(GSocket& _socket, std::string& _data) {
    char lBuffer[BUFFER_SIZE + 1];
    int lSize = sizeof(_socket.m_address);
    int lBytes = recvfrom(m_socket, lBuffer, BUFFER_SIZE, 0, (SOCKADDR*)&_socket.m_address, &lSize);
    if(lBytes > 0) {
        lBuffer[lBytes] = 0;
        _data = lBuffer;
    }
    return lBytes;
}
//===============================================
void GSocket::sendData(const std::string& _data) {
    send(m_socket, _data.c_str(), _data.size(), 0);
}
//===============================================
void GSocket::writeData(const std::string& _data) {
    int lIndex = 0;
    char lBuffer[BUFFER_SIZE + 1];
    GString lData(_data);
    while(1) {
        int lBytes = lData.toChar(lBuffer, lIndex, BUFFER_SIZE);
        if(lBytes <= 0) break;
        lIndex += lBytes;
        sendData(lBuffer);
    }
}
//===============================================
void GSocket::sendData(GSocket& _socket, const std::string& _data) {
    int lSize = sizeof(_socket.m_address);
    sendto(m_socket, _data.c_str(), _data.size(), 0, (SOCKADDR*)&_socket.m_address, lSize);
}
//===============================================
void GSocket::getAddressIp(std::string& _ip) {
    char* ip = inet_ntoa(m_address.sin_addr);
    _ip = ip;
}
//===============================================
void GSocket::getHostname(std::string& _hostname) {
    char lBuffer[HOSTNAME_SIZE + 1];
    gethostname(lBuffer, HOSTNAME_SIZE);
    _hostname = lBuffer;
}
//===============================================
void GSocket::shutdownWR() {
    shutdown(m_socket, SD_SEND);
}
//===============================================
void GSocket::shutdownRD() {
    shutdown(m_socket, SD_RECEIVE);
}
//===============================================
void GSocket::closeSocket() {
    closesocket(m_socket);
}
//===============================================
void GSocket::cleanSocket() {
    WSACleanup();
}
//===============================================
