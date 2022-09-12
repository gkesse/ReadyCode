//===============================================
#include "GSocket2.h"
#include "GLog.h"
#include "GPath.h"
//===============================================
GSocket2::GSocket2() {
    m_major = 0;
    m_minor = 0;
    m_domain = 0;
    m_type = 0;
    m_protocol = 0;
    m_family = 0;
    m_port = 0;
}
//===============================================
GSocket2::~GSocket2() {

}
void GSocket2::setMajor(int _major) {
    m_major = _major;
}
//===============================================
void GSocket2::setMinor(int _minor) {
    m_minor = _minor;
}
//===============================================
void GSocket2::setDomain(int _domain) {
    m_domain = _domain;
}
//===============================================
void GSocket2::setType(int _type) {
    m_type = _type;
}
//===============================================
void GSocket2::setProtocol(int _protocol) {
    m_protocol = _protocol;
}
void GSocket2::setFamily(int _family) {
    m_family = _family;
}
//===============================================
void GSocket2::setPort(int _port) {
    m_port = _port;
}
//===============================================
void GSocket2::setHostname(const QString& _hostname) {
    m_hostname = _hostname;
}
//===============================================
bool GSocket2::callServer(const QString& _dataIn, QString& _dataOut) {
    WSADATA lWsaData;
    WSAStartup(MAKEWORD(m_major, m_minor), &lWsaData);
    SOCKET lSocket = socket(m_domain, m_type, m_protocol);
    if(lSocket == INVALID_SOCKET) return false;
    SOCKADDR_IN lAddress;
    lAddress.sin_family = m_family;
    lAddress.sin_addr.s_addr = inet_addr(m_hostname.toStdString().c_str());
    lAddress.sin_port = htons(m_port);
    memset(&lAddress.sin_zero, 0, sizeof(lAddress.sin_zero));
    int lAnswer = connect(lSocket, (SOCKADDR*)(&lAddress), sizeof(lAddress));
    if(lAnswer == SOCKET_ERROR) return false;
    int lBytes = send(lSocket, _dataIn.toStdString().c_str(), _dataIn.size(), 0);
    if(lBytes == -1) return false;
    return true;
}
//===============================================
