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
void GSocket::init(int _major, int _minor) {
    WSADATA lWsaData;
    WSAStartup(MAKEWORD(_major, _minor), &lWsaData);
}
//===============================================
void GSocket::sockets() {
    m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}
//===============================================
void GSocket::sockets2() {
    m_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
}
//===============================================
void GSocket::address(const std::string& _ip, int _port) {
    m_address.sin_family = AF_INET;
    m_address.sin_addr.s_addr = inet_addr(_ip.c_str());
    m_address.sin_port = htons(_port);
    memset(&m_address.sin_zero, 0, sizeof(m_address.sin_zero));
}
//===============================================
void GSocket::listens(int _backlog) {
    listen(m_socket, _backlog);
}
//===============================================
void GSocket::binds() {
    bind(m_socket, (SOCKADDR*)&m_address, sizeof(m_address));
}
//===============================================
void GSocket::connects() {
    connect(m_socket, (SOCKADDR*)(&m_address), sizeof(m_address));
}
//===============================================
void GSocket::accepts(GSocket& _socket) {
    int lSize = sizeof(_socket.m_address);
    _socket.m_socket = accept(m_socket, (SOCKADDR*)&_socket.m_address, &lSize);
}
//===============================================
int GSocket::recvs(std::string& _data) {
    char lBuffer[BUFFER_SIZE + 1];
    int lBytes = recv(m_socket, lBuffer, BUFFER_SIZE, 0);
    if(lBytes > 0) {
        lBuffer[lBytes] = 0;
        _data = lBuffer;
    }
    return lBytes;
}
//===============================================
int GSocket::reads(std::string& _data) {
    _data = "";
    std::string lData;
    int lIndex = 0;
    while(1) {
        int lBytes = recvs(lData);
        if(lBytes <= 0) break;
        lIndex += lBytes;
        _data += lData;
    }
    return lIndex;
}
//===============================================
int GSocket::recvs(GSocket& _socket, std::string& _data) {
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
void GSocket::sends(const std::string& _data) {
    send(m_socket, _data.c_str(), _data.size(), 0);
}
//===============================================
void GSocket::writes(const std::string& _data) {
    int lIndex = 0;
    char lBuffer[BUFFER_SIZE + 1];
    GString lData(_data);
    while(1) {
        int lBytes = lData.toChar(lBuffer, lIndex, BUFFER_SIZE);
        if(lBytes <= 0) break;
        lIndex += lBytes;
        sends(lBuffer);
    }
}
//===============================================
void GSocket::sends(GSocket& _socket, const std::string& _data) {
    int lSize = sizeof(_socket.m_address);
    sendto(m_socket, _data.c_str(), _data.size(), 0, (SOCKADDR*)&_socket.m_address, lSize);
}
//===============================================
void GSocket::ip(std::string& _ip) {
    char* ip = inet_ntoa(m_address.sin_addr);
    _ip = ip;
}
//===============================================
void GSocket::hostname(std::string& _hostname) {
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
void GSocket::close() {
    closesocket(m_socket);
}
//===============================================
void GSocket::clean() {
    WSACleanup();
}
//===============================================
void GSocket::start(sGSocket& _socket) {
    GSocket lServer;
    GThread lThread;

    lServer.init(_socket.major, _socket.minor);
    lServer.hostname(_socket.hostname);
    lServer.address(_socket.address_ip, _socket.port);
    lServer.sockets();
    lServer.binds();
    lServer.listens(_socket.backlog);

    printf("Demarrage du serveur...\n");
    printf("Hostname.....: %s\n", _socket.hostname.c_str());

    while(1) {
        GSocket* lClient = new GSocket;
        lServer.accepts(*lClient);
        lClient->ip(_socket.client_ip);
        _socket.socket = lClient;
        lThread.create((GThread::onThreadCB)_socket.on_start, &_socket);
    }

    lServer.close();
    lServer.clean();
}
//===============================================
void GSocket::call(sGSocket& _socket, const std::string& _dataIn, std::string& _dataOut) {
    GSocket lClient;
    lClient.init(_socket.major, _socket.minor);
    lClient.hostname(_socket.hostname);
    lClient.address(_socket.address_ip, _socket.port);
    lClient.sockets();
    lClient.connects();
    lClient.writes(_dataIn);
    lClient.shutdownWR();
    lClient.reads(_dataOut);
    lClient.close();
    lClient.clean();
}
//===============================================
