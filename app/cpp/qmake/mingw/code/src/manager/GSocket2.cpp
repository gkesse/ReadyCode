//===============================================
#include "GSocket2.h"
#include "GLog.h"
#include "GPath.h"
#include "GCode2.h"
//===============================================
GSocket2::GSocket2() {
    m_major = 0;
    m_minor = 0;
    m_domain = 0;
    m_type = 0;
    m_protocol = 0;
    m_family = 0;
    m_port = 0;
    m_socket = 0;
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
void GSocket2::setHostname(const GString& _hostname) {
    m_hostname = _hostname;
}
//===============================================
bool GSocket2::callServer() {
    WSADATA lWsaData;
    WSAStartup(MAKEWORD(m_major, m_minor), &lWsaData);
    m_socket = socket(m_domain, m_type, m_protocol);
    if(m_socket == INVALID_SOCKET) return false;
    SOCKADDR_IN lAddress;
    lAddress.sin_family = m_family;
    lAddress.sin_addr.s_addr = inet_addr(m_hostname.c_str());
    lAddress.sin_port = htons(m_port);
    memset(&lAddress.sin_zero, 0, sizeof(lAddress.sin_zero));
    int lAnswer = connect(m_socket, (SOCKADDR*)(&lAddress), sizeof(lAddress));
    if(lAnswer == SOCKET_ERROR) return false;

    if(createData()) {
        if(sendData()) {
            if(readMethod()) {
                onCallServer();
            }
        }
    }

    m_dataIn.print();
    m_dataOut.print();

    closesocket(m_socket);
    WSACleanup();
    return true;
}
//===============================================
bool GSocket2::sendData() {
    int lIndex = 0;
    int lSize = m_dataOut.size();
    const char* lBuffer = m_dataOut.c_str();

    while(1) {
        int lBytes = send(m_socket, &lBuffer[lIndex], lSize - lIndex, 0);
        if(lBytes <= 0) return false;
        lIndex += lBytes;
        if(lIndex >= lSize) break;
    }

    return true;
}
//===============================================
int GSocket2::readData(char* _data, int _size) {
    int lBytes = recv(m_socket, _data, _size, 0);
    return lBytes;
}
//===============================================
bool GSocket2::readData(int _diffSize) {
    if(_diffSize < 0) return false;
    if(_diffSize == 0) return true;
    char lBuffer[BUFFER_SIZE + 1];
    int lSize = 0;
    while(1) {
        int lBytes = readData(lBuffer, BUFFER_SIZE);
        if(lBytes <= 0) return false;
        lBuffer[lBytes] = 0;
        m_dataIn += lBuffer;
        lSize += lBytes;
        if(lSize >= _diffSize) return true;
    }
    return true;
}
//===============================================
bool GSocket2::readMethod() {
    char lBuffer[METHOD_SIZE + 1];
    int lBytes = readData(lBuffer, METHOD_SIZE);
    if(lBytes <= 0) return false;
    lBuffer[lBytes] = 0;
    m_dataIn += lBuffer;
    return true;
}
//===============================================
bool GSocket2::createData() {return false;}
bool GSocket2::onCallServer() {return false;}
//===============================================
