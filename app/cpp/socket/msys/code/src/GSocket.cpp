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
void GSocket::init() {
    WSADATA lWsaData;
    WSAStartup(MAKEWORD(m_major, m_minor), &lWsaData);
}
//===============================================
void GSocket::sockets() {
    m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}
//===============================================
void GSocket::address() {
    m_address.sin_family = AF_INET;
    InetPton(AF_INET, m_ip.c_str(), &m_address.sin_addr.s_addr);
    m_address.sin_port = htons(m_port);
    memset(&m_address.sin_zero, 0, sizeof(m_address.sin_zero));
}
//===============================================
void GSocket::listens() {
    listen(m_socket, m_backlog);
}
//===============================================
void GSocket::binds() {
    bind(m_socket, (SOCKADDR *)&m_address, sizeof(m_address));
}
//===============================================
void GSocket::connects() {
	connect(m_socket, (SOCKADDR*)(&m_address), sizeof(m_address));
}
//===============================================
void GSocket::accepts(GSocket& _socket) {
	_socket.m_size = sizeof(_socket.m_address);
	_socket.m_socket = accept(m_socket, (SOCKADDR*)&_socket.m_address, &_socket.m_size);
}
//===============================================
void GSocket::recvs() {
    m_bytes = recv(m_socket, m_buffer, BUFFER_SIZE, 0);
    m_buffer[m_bytes] = 0;
}
//===============================================
void GSocket::sends(const char* _data) {
    m_bytes = send(m_socket, _data, strlen(_data), 0);
}
//===============================================
void GSocket::print() const {
	printf("...............(start)..............\n");
	printf("%s\n", m_buffer);
	printf("...............( end )..............\n");
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
