//===============================================
#include "GSocket.h"
//===============================================
GSocket::GSocket() {
    m_ip = "0.0.0.0";
    m_port = 8585;
    m_backlog = 5;
    m_major = 2;
    m_minor = 2;
    m_socket = -1;
    m_size = 0;
    m_bytes = 0;
    m_buffer[0] = 0;
}
//===============================================
GSocket::~GSocket() {

}
//===============================================
void GSocket::ip(const std::string& _ip) {
    m_ip = _ip;
}
//===============================================
void GSocket::port(int _port) {
    m_port = _port;
}
//===============================================
void GSocket::backlog(int _backlog) {
    m_backlog = _backlog;
}
//===============================================
void GSocket::sockets() {
    m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}
//===============================================
void GSocket::sockets2() {
    m_socket = socket(AF_INET, SOCK_DGRAM, 0);
}
//===============================================
void GSocket::address() {
    bzero(&m_address, sizeof(m_address));
    m_address.sin_family = AF_INET;
    m_address.sin_addr.s_addr = inet_addr(m_ip.c_str());
    m_address.sin_port = htons(m_port);
}
//===============================================
void GSocket::listens() {
    listen(m_socket, m_backlog);
}
//===============================================
void GSocket::binds() {
    bind(m_socket, (struct sockaddr*)&m_address, sizeof(m_address));
}
//===============================================
void GSocket::connects() {
    connect(m_socket, (struct sockaddr*)&m_address, sizeof(m_address));
}
//===============================================
void GSocket::start() {
    printf("demarrage du serveur...\n");
}
//===============================================
void GSocket::accepts(GSocket& _socket) {
    _socket.m_size = sizeof(_socket.m_address);
    _socket.m_socket = accept(m_socket, (struct sockaddr*)&_socket.m_address, (socklen_t*)&_socket.m_size);
}
//===============================================
void GSocket::recvs() {
    m_bytes = read(m_socket, m_buffer, sizeof(m_buffer));
    m_buffer[m_bytes] = 0;
}
//===============================================
void GSocket::recvs(GSocket& _socket) {
    _socket.m_size = sizeof(_socket.m_address);
    m_bytes = recvfrom(m_socket, m_buffer, sizeof(m_buffer), 0, (struct sockaddr*)&_socket.m_address, &_socket.m_size);
    m_buffer[m_bytes] = 0;
}
//===============================================
void GSocket::recvs(GString& _data) {
    _data.clear();
    while(1) {
        recvs();
        if(m_bytes <= 0) break;
        _data.add(m_buffer);
    }
}
//===============================================
void GSocket::sends(const char* _data) {
    m_bytes = write(m_socket, _data, strlen(_data));
}
//===============================================
void GSocket::sends(GSocket& _socket, const char* _data) {
    _socket.m_size = sizeof(_socket.m_address);
    sendto(m_socket, _data, strlen(_data), 0, (struct sockaddr*)&_socket.m_address, _socket.m_size);
}
//===============================================
void GSocket::sends(const GString& _data) {
    int lIndex = 0;
    while(1) {
        m_bytes = _data.toChar(m_buffer, lIndex, BUFFER_SIZE);
        if(m_bytes <= 0) break;
        lIndex += m_bytes;
        sends(m_buffer);
    }
}
//===============================================
void GSocket::ip() {
    //inet_ntop(AF_INET, &m_address.sin_addr, m_ip2, IP_SIZE);
}
//===============================================
void GSocket::print() const {
    printf("%s\n", m_buffer);
}
//===============================================
void GSocket::print2() const {
    printf("IP..........: %s\n", m_ip2);
}
//===============================================
void GSocket::closes() {
	close(m_socket);
}
//===============================================
