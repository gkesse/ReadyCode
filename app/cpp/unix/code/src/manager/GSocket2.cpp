//===============================================
#include "GSocket2.h"
#include "GPath.h"
#include "GLog.h"
#include "GFormat.h"
#include "GXml.h"
#include "GThread.h"
#include "GCode.h"
#include "GString.h"
#include "GEnv.h"
#include "GHost.h"
#include "GHttp.h"
#include "GThread2.h"
//===============================================
GSocket2::GSocket2()
: GObject() {
    m_domain = 0;
    m_type = 0;
    m_protocol = 0;
    m_family = 0;
    m_port = 0;
    m_backlog = 0;
    m_server = 0;
    m_socket = 0;
}
//===============================================
GSocket2::~GSocket2() {

}
//===============================================
void GSocket2::setModule(const GString2& _module) {
    m_module = _module;
}
//===============================================
void GSocket2::setHostname(const GString2& _hostname) {
    m_hostname = _hostname;
}
//===============================================
void GSocket2::setMessage(const GString2& _message) {
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
int GSocket2::getSocket() const {
    return m_socket;
}
//===============================================
GString2& GSocket2::getDataIn() {
    return m_dataIn;
}
//===============================================
const GString2& GSocket2::getDataIn() const {
    return m_dataIn;
}
//===============================================
GString2& GSocket2::getDataOut() {
    return m_dataOut;
}
//===============================================
const GString2& GSocket2::getDataOut() const {
    return m_dataOut;
}
//===============================================
bool GSocket2::run() {
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
        GSocket2* lClient = new GSocket2;
        int lSocket2 = accept(lSocket, (struct sockaddr*)&lAddress2, &lSize);
        if(lSocket2 == -1) return false;
        lClient->m_socket = lSocket2;
        lClient->m_server = this;
        lThread.setParams((void*)lClient);
        if(!lThread.run()) return false;
    }

    return true;
}
//===============================================
void* GSocket2::onThreadCB(void* _params) {
    GSocket2* lClient = (GSocket2*)_params;
    GString2& lDataIn = lClient->getDataIn();
    GString2& lDataOut = lClient->getDataOut();

    if(lClient->readMethod()) {
        if(lDataIn.startBy("GET")) {
            lClient->runHttp();
        }
    }

    GLOGT(eGMSG, "[EMISSION] : (%d)\n%s", (int)lDataIn.size(), lDataIn.c_str());
    GLOGT(eGMSG, "[RECEPTION] : (%d)\n%s", (int)lDataOut.size(), lDataOut.c_str());

    if(lDataOut.size() > 0) {
        int lIndex = 0;
        int lSize = lDataOut.size();
        const char* lBuffer = lDataOut.c_str();

        while(1) {
            int lBytes = send(lClient->m_socket, &lBuffer[lIndex], lSize - lIndex, 0);
            if(lBytes <= 0) break;
            lIndex += lBytes;
            GLOGT(eGOFF, "SIZE : %d\n", lBytes);
        }
    }

    close(lClient->m_socket);
    delete lClient;
    return 0;
}
//===============================================
bool GSocket2::runHttp() {
    GHttp lHttp;
    lHttp.setClient(this);
    lHttp.runHttp();
    return true;
}
//===============================================
int GSocket2::readData(char* _data, int _size) {
    int lBytes = recv(m_socket, _data, _size, 0);
    return lBytes;
}
//===============================================
bool GSocket2::addDataIn(const GString2& _data) {
    m_dataIn += _data;
    return true;
}
//===============================================
bool GSocket2::readMethod() {
    char lBuffer[METHOD_SIZE + 1];
    int lBytes = recv(m_socket, lBuffer, METHOD_SIZE, 0);
    if(lBytes <= 0) return false;
    lBuffer[lBytes] = 0;
    m_dataIn += lBuffer;
    return true;
}
//===============================================
