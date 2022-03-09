//===============================================
#include "GSocket.h"
//===============================================
GSocket::GSocket() {
    m_ip = "0.0.0.0";
    m_port = 8585;
    m_backlog = 5;
    m_domain = AF_INET;
    m_type = SOCK_STREAM;
    m_protocol = IPPROTO_TCP;
    m_family = AF_INET;
    m_familyIp = AF_INET;
    //
    m_socket = -1;
    m_buffer[0] = 0;
    m_bufferIp[0] = 0;
}
//===============================================
GSocket::~GSocket() {

}
//===============================================
void GSocket::setAddressIp(const std::string& _ip) {
    m_ip = _ip;
}
//===============================================
void GSocket::setPort(int _port) {
    m_port = _port;
}
//===============================================
void GSocket::setBacklog(int _backlog) {
    m_backlog = _backlog;
}
//===============================================
void GSocket::createSocket() {
    m_socket = socket(m_domain, m_type, m_protocol);
}
//===============================================
void GSocket::createAddress() {
    bzero(&m_address, sizeof(m_address));
    m_address.sin_family = m_family;
    m_address.sin_addr.s_addr = inet_addr(m_ip.c_str());
    m_address.sin_port = htons(m_port);
}
//===============================================
void GSocket::listenSocket() {
    listen(m_socket, m_backlog);
}
//===============================================
void GSocket::bindSocket() {
    bind(m_socket, (struct sockaddr*)&m_address, sizeof(m_address));
}
//===============================================
void GSocket::connectSocket() {
    connect(m_socket, (struct sockaddr*)&m_address, sizeof(m_address));
}
//===============================================
void GSocket::start() {
    printf("demarrage du serveur...\n");
}
//===============================================
void GSocket::acceptSocket(GSocket& _socket) {
    int lSize = sizeof(_socket.m_address);
    _socket.m_socket = accept(m_socket, (struct sockaddr*)&_socket.m_address, (socklen_t*)&lSize);
}
//===============================================
int GSocket::recvData() {
    int lBytes = read(m_socket, m_buffer, BUFFER_DATA_SIZE);
    if(lBytes <= 0) lBytes = 0;
    m_buffer[lBytes] = 0;
    return lBytes;
}
//===============================================
int GSocket::recvData(GSocket& _socket) {
    int lSize = sizeof(_socket.m_address);
    int lBytes = recvfrom(m_socket, m_buffer, BUFFER_DATA_SIZE, 0, (struct sockaddr*)&_socket.m_address, (socklen_t*)&lSize);
    if(lBytes <= 0) lBytes = 0;
    m_buffer[lBytes] = 0;
    return lBytes;
}
//===============================================
int GSocket::recvData(GString& _data) {
    _data.clear();
    while(1) {
        int lBytes = recvData();
        if(lBytes <= 0) break;
        _data.add(m_buffer);
    }
    return _data.size();
}
//===============================================
int GSocket::sendData(const char* _data) {
    int lBytes = write(m_socket, _data, strlen(_data));
    if(lBytes <= 0) lBytes = 0;
    return lBytes;
}
//===============================================
int GSocket::sendData(GSocket& _socket, const char* _data) {
	int lSize = sizeof(_socket.m_address);
    int lBytes = sendto(m_socket, _data, strlen(_data), 0, (struct sockaddr*)&_socket.m_address, lSize);
    if(lBytes <= 0) lBytes = 0;
    return lBytes;
}
//===============================================
int GSocket::sendData(const GString& _data) {
    int lIndex = 0;
    while(1) {
        int lBytes = _data.toChar(m_buffer, lIndex, BUFFER_DATA_SIZE);
        if(lBytes <= 0) break;
        lIndex += lBytes;
        sendData(m_buffer);
    }
    return lIndex;
}
//===============================================
std::string GSocket::readAddressIp() const {
	char lBuffer[BUFFER_IP_SIZE + 1];
    inet_ntop(m_familyIp, &(m_address.sin_addr), lBuffer, BUFFER_IP_SIZE);
    return lBuffer;
}
//===============================================
void GSocket::closeSocket() {
    close(m_socket);
}
//===============================================
