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
