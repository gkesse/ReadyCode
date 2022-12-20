//===============================================
#include "GSocket.h"
#include "GSocketEcho.h"
#include "GSocketReadyApp.h"
#include "GSocketHttpApp.h"
#include "GThread.h"
#include "GEnv.h"
#include "GCode.h"
#include "GLog.h"
//===============================================
const char* GSocket::METHOD_RDVAPP        = "RDVAPP";
const char* GSocket::METHOD_HTTP_GET      = "GET";
const char* GSocket::METHOD_HTTP_POST     = "POST";
//===============================================
GSocket::GSocket()
: GObject() {
    createDoms();
    initSocket();
}
//===============================================
GSocket::~GSocket() {

}
//===============================================
void GSocket::initSocket() {
    m_module        = GSocket::SOCKET_SERVER_TCP;
    m_protocol      = GSocket::PROTOCOL_ECHO;

    m_isTestEnv     = GEnv().isTestEnv();

    m_portProd      = m_dom->getData("socket", "port_prod").toInt();
    m_portTest      = m_dom->getData("socket", "port_test").toInt();
    m_port          = (m_isTestEnv ? m_portTest : m_portProd);
    m_backlog       = m_dom->getData("socket", "backlog").toInt();
    m_serverIp      = m_dom->getData("socket", "server_ip");
    m_clientIp      = m_dom->getData("socket", "client_ip");
    m_hostname      = m_clientIp;
    m_startMessage  = m_dom->getData("socket", "start_message");
    m_stopMessage   = m_dom->getData("socket", "stop_message");
}
//===============================================
GSocket* GSocket::createSocket() {
    if(m_protocol == GSocket::PROTOCOL_ECHO) return new GSocketEcho;
    if(m_protocol == GSocket::PROTOCOL_RDVAPP) return new GSocketReadyApp;
    if(m_protocol == GSocket::PROTOCOL_HTTP) return new GSocketHttpApp;
    return new GSocketEcho;
}
//===============================================
void GSocket::setModule(GSocket::eGModule _module) {
    m_module = _module;
}
//===============================================
void GSocket::setProtocol(GSocket::eGProtocol _protocol) {
    m_protocol = _protocol;
}
//===============================================
bool GSocket::runServer() {
    if(m_module == GSocket::SOCKET_SERVER_TCP) return runServerTcp();
    return runServerTcp();
}
//===============================================
bool GSocket::runServerTcp() {
    int lSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(lSocket == -1) return false;

    struct sockaddr_in lAddressIn;
    bzero(&lAddressIn, sizeof(lAddressIn));
    lAddressIn.sin_family = AF_INET;
    lAddressIn.sin_addr.s_addr = inet_addr(m_hostname.c_str());
    lAddressIn.sin_port = htons(m_port);

    int lBind = bind(lSocket, (struct sockaddr*)&lAddressIn, sizeof(lAddressIn));
    if(lBind == -1) return false;

    int lListen = listen(lSocket, m_backlog);
    if(lListen == -1) return false;

    GLOGT(eGMSG, "%s", m_startMessage.c_str());

    struct sockaddr_in lAddress2;
    socklen_t lSize = sizeof(lAddress2);

    GThread lThread;
    lThread.setThreadCB((void*)onThreadCB);

    while(1) {
        GSocket* lClient = createSocket();
        int lSocket2 = accept(lSocket, (struct sockaddr*)&lAddress2, &lSize);
        if(lSocket2 == -1) return false;
        lClient->m_module = m_module;
        lClient->m_protocol = m_protocol;
        lClient->m_socket = lSocket2;
        lThread.setParams((void*)lClient);
        if(!lThread.run()) return false;
    }

    return true;
}
//===============================================
void* GSocket::onThreadCB(void* _params) {
    GSocket* lClient = (GSocket*)_params;
    lClient->runThreadCB();
    return 0;
}
//===============================================
bool GSocket::sendResponse() {
    GLOGT(eGMSG, "[RECEPTION] : (%d)\n%s\n", m_dataIn.size(), m_dataIn.c_str());
    GLOGT(eGMSG, "[EMISSION] : (%d)\n%s\n", m_dataOut.size(), m_dataOut.c_str());
    sendData(m_dataOut);
    return true;
}
//===============================================
bool GSocket::readData(GString& _dataOut, int _size) {
    if(_size <= 0) return false;
    char lBuffer[BUFFER_SIZE + 1];
    int lSize = 0;
    while(1) {
        int lBytes = recv(m_socket, lBuffer, BUFFER_SIZE, 0);
        if(lBytes <= 0) return false;
        lBuffer[lBytes] = 0;
        _dataOut += lBuffer;
        lSize += lBytes;
        if(lSize >= _size) return true;
    }
    return true;
}
//===============================================
int GSocket::sendData(const GString& _dataIn) {
    if(_dataIn.isEmpty()) return false;
    int lSize = _dataIn.size();
    const char* lBuffer = _dataIn.c_str();
    int lIndex = 0;

    while(1) {
        int lBytes = send(m_socket, &lBuffer[lIndex], lSize - lIndex, 0);
        if(lBytes <= 0) return false;
        lIndex += lBytes;
        if(lIndex >= lSize) break;
    }

    return true;
}
//===============================================
bool GSocket::sendDatas(const GString& _dataIn) {
    GString lSize = GFORMAT("%*d", _dataIn.size(), DATA_LENGTH_SIZE);
    sendData(lSize);
    sendData(_dataIn);
    return true;
}
//===============================================
bool GSocket::readDatas(GString& _dataOut) {
    GString lHeader;
    readData(lHeader, DATA_LENGTH_SIZE);
    int lSize = lHeader.substr(0, DATA_LENGTH_SIZE).toInt();
    int dSize = lSize - lHeader.size();
    readData(_dataOut, dSize);
    return true;
}
//===============================================
bool GSocket::runThreadCB() {return true;}
void GSocket::setRequest(const GString& _request) {}
GString GSocket::getRequest() const {return "";}
bool GSocket::addResponse(const GString& _data) {return true;}
bool GSocket::createResponse() {return true;}
GString GSocket::getResponse() const {return "";}
//===============================================
