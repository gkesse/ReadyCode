//===============================================
#include "GThread.h"
#include "GSocket.h"
#include "GLog.h"
#include "GHttp.h"
#include "GEnv.h"
#include "GCode.h"
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
    m_isTestEnv     = GEnv().isTestEnv();

    m_module        = m_dom->getData("socket", "module");
    m_domainName    = m_dom->getData("socket", "domain");
    m_typeName      = m_dom->getData("socket", "type");
    m_protocolName  = m_dom->getData("socket", "protocol");
    m_familyName    = m_dom->getData("socket", "family");
    m_portProd      = m_dom->getData("socket", "port_prod").toInt();
    m_portTest      = m_dom->getData("socket", "port_test").toInt();
    m_backlog       = m_dom->getData("socket", "backlog").toInt();
    m_serverIp      = m_dom->getData("socket", "server_ip");
    m_clientIp      = m_dom->getData("socket", "client_ip");
    m_apiMethod     = m_dom->getData("socket", "api_method");
    m_apiKeyProd    = m_dom->getData("socket", "api_key_prod");
    m_apiKeyTest    = m_dom->getData("socket", "api_key_test");
    m_apiUsername   = m_dom->getData("socket", "api_username");
    m_apiPassword   = m_dom->getData("socket", "api_password");
    m_startMessage  = m_dom->getData("socket", "start_message");

    m_domain        = loadDomain();
    m_type          = loadType();
    m_protocol      = loadProtocol();
    m_family        = loadFamily();
    m_hostname      = m_clientIp;
    m_port          = (m_isTestEnv ? m_portTest : m_portProd);
    m_apiKey        = (m_isTestEnv ? m_apiKeyTest : m_apiKeyProd);
}
//===============================================
int GSocket::loadDomain() const {
    if(m_domainName == "AF_INET") return AF_INET;
    return AF_INET;
}
//===============================================
int GSocket::loadType() const {
    if(m_typeName == "SOCK_STREAM") return SOCK_STREAM;
    return SOCK_STREAM;
}
//===============================================
int GSocket::loadProtocol() const {
    if(m_protocolName == "IPPROTO_TCP") return IPPROTO_TCP;
    return IPPROTO_TCP;
}
//===============================================
int GSocket::loadFamily() const {
    if(m_familyName == "AF_INET") return AF_INET;
    return AF_INET;
}
//===============================================
GString& GSocket::getDataIn() {
    return m_dataIn;
}
//===============================================
GString& GSocket::getDataOut() {
    return m_dataOut;
}
//===============================================
bool GSocket::runServer() {
    if(m_module == "tcp") {
        return runServerTcp();
    }
    return false;
}
//===============================================
bool GSocket::runServerTcp() {
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

    GLOGT(eGMSG, "%s", m_startMessage.c_str());

    struct sockaddr_in lAddress2;
    socklen_t lSize = sizeof(lAddress2);

    GThread lThread;
    lThread.setThreadCB((void*)onThreadCB);

    while(1) {
        GSocket* lClient = clone();
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
void* GSocket::onThreadCB(void* _params) {
    GSocket* lClient = (GSocket*)_params;
    lClient->runThreadCB();
    return 0;
}
//===============================================
bool GSocket::runThreadCB() {
    if(m_module == "tcp") {
        return runThreadTcp();
    }
    return false;
}
//===============================================
bool GSocket::runThreadTcp() {
    if(readMethod()) {
        onRunServerTcp();
    }

    sendResponse();
    close(m_socket);
    delete this;
    return true;
}
//===============================================
bool GSocket::readMethod() {
    char lBuffer[METHOD_SIZE + 1];
    int lBytes = readData(lBuffer, METHOD_SIZE);
    if(lBytes <= 0) return false;
    lBuffer[lBytes] = 0;
    m_dataIn += lBuffer;
    return true;
}
//===============================================
bool GSocket::sendResponse() {
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
bool GSocket::readData(int _diffSize) {
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
int GSocket::readData(char* _data, int _size) {
    int lBytes = recv(m_socket, _data, _size, 0);
    return lBytes;
}
//===============================================
int GSocket::sendData(const char* _data, int _size) {
    int lBytes = send(m_socket, _data, _size, 0);
    return lBytes;
}
//===============================================
GSocket* GSocket::clone() const {return new GSocket;}
bool GSocket::onRunServerTcp() {return false;}
//===============================================
