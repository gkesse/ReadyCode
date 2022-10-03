//===============================================
#include "GSocket2.h"
#include "GLog.h"
#include "GThread2.h"
#include "GHttp.h"
//===============================================
GSocket2::GSocket2()
: GObject() {
    m_domain = 0;
    m_type = 0;
    m_protocol = 0;
    m_family = 0;
    m_port = 0;
    m_backlog = 0;
    m_socket = 0;
}
//===============================================
GSocket2::~GSocket2() {

}
//===============================================
void GSocket2::setModule(const GString& _module) {
    m_module = _module;
}
//===============================================
void GSocket2::setHostname(const GString& _hostname) {
    m_hostname = _hostname;
}
//===============================================
void GSocket2::setMessage(const GString& _message) {
    m_message = _message;
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
//===============================================
void GSocket2::setFamily(int _family) {
    m_family = _family;
}
//===============================================
void GSocket2::setPort(int _port) {
    m_port = _port;
}
//===============================================
void GSocket2::setBacklog(int _backlog) {
    m_backlog = _backlog;
}
//===============================================
GString& GSocket2::getDataIn() {
    return m_dataIn;
}
//===============================================
GString& GSocket2::getDataOut() {
    return m_dataOut;
}
//===============================================
bool GSocket2::runServer() {
    if(m_module == "tcp") {
        return runServerTcp();
    }
    return false;
}
//===============================================
bool GSocket2::runServerTcp() {
    int lSocket = socket(m_domain, m_type, m_protocol);
    if(lSocket == -1) return false;

    struct sockaddr_in lAddressIn;
    bzero(&lAddressIn, sizeof(lAddressIn));
    lAddressIn.sin_family = m_family;
    lAddressIn.sin_addr.s_addr = inet_addr(m_hostname.c_str());
    lAddressIn.sin_port = htons(m_port);

    int lBind = bind(lSocket, (struct sockaddr*)&lAddressIn, sizeof(lAddressIn));
    if(lBind == -1) return false;

    int lListen = listen(lSocket, m_backlog);
    if(lListen == -1) return false;

    GLOGT(eGMSG, "%s", m_message.c_str());

    struct sockaddr_in lAddress2;
    socklen_t lSize = sizeof(lAddress2);

    GThread2 lThread;
    lThread.setThreadCB((void*)onThreadCB);

    while(1) {
        GSocket2* lClient = clone();
        int lSocket2 = accept(lSocket, (struct sockaddr*)&lAddress2, &lSize);
        if(lSocket2 == -1) return false;
        lClient->m_module = m_module;
        lClient->m_socket = lSocket2;
        lThread.setParams((void*)lClient);
        if(!lThread.run()) return false;
    }

    return true;
}
//===============================================
void* GSocket2::onThreadCB(void* _params) {
    GSocket2* lClient = (GSocket2*)_params;
    lClient->runThreadCB();
    return 0;
}
//===============================================
bool GSocket2::runThreadCB() {
    if(m_module == "tcp") {
        return runThreadTcp();
    }
    return false;
}
//===============================================
bool GSocket2::runThreadTcp() {
    if(readMethod()) {
        onRunServerTcp();
    }

    sendResponse();
    close(m_socket);
    delete this;
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
    int lIndex = 0;
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
int GSocket2::sendData(const char* _data, int _size) {
    int lBytes = send(m_socket, _data, _size, 0);
    return lBytes;
}
//===============================================
bool GSocket2::sendResponse() {
    GLOGT(eGMSG, "[RECEPTION] : (%d)\n%s", (int)m_dataIn.size(), m_dataIn.c_str());
    GLOGT(eGMSG, "[EMISSION] : (%d)\n%s", (int)m_dataOut.size(), m_dataOut.c_str());

    if(m_dataOut.size() > 0) {
        int lIndex = 0;
        int lSize = m_dataOut.size();
        const char* lBuffer = m_dataOut.c_str();

        while(1) {
            int lBytes = sendData(&lBuffer[lIndex], lSize - lIndex);
            if(lBytes <= 0) return false;
            lIndex += lBytes;
            if(lIndex >= lSize) break;
        }
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
GSocket2* GSocket2::clone() const {return new GSocket2;}
bool GSocket2::onRunServerTcp() {return false;}
//===============================================
