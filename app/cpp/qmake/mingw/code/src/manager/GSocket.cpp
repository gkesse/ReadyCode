//===============================================
#include "GLog.h"
#include "GSocket.h"
#include "GPath.h"
#include "GCode.h"
#include "GEnv.h"
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

    m_major         = m_dom->getData("socket", "major").toInt();
    m_minor         = m_dom->getData("socket", "minor").toInt();
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

    m_domain        = loadDomain();
    m_type          = loadType();
    m_protocol      = loadProtocol();
    m_family        = loadFamily();
    m_hostname      = m_serverIp;
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
bool GSocket::callServer() {
    WSADATA lWsaData;
    WSAStartup(MAKEWORD(m_major, m_minor), &lWsaData);
    m_socket = socket(m_domain, m_type, m_protocol);
    if(m_socket == INVALID_SOCKET) {GERROR_ADD(eGERR, "Erreur lors de la connexion au serveur."); return false;}
    SOCKADDR_IN lAddress;
    lAddress.sin_family = m_family;
    lAddress.sin_addr.s_addr = inet_addr(m_hostname.c_str());
    lAddress.sin_port = htons(m_port);
    memset(&lAddress.sin_zero, 0, sizeof(lAddress.sin_zero));
    int lAnswer = connect(m_socket, (SOCKADDR*)(&lAddress), sizeof(lAddress));
    if(lAnswer == SOCKET_ERROR) {GERROR_ADD(eGERR, "Erreur lors de la connexion au serveur."); return false;}

    m_dataOut = "";
    m_dataIn = "";

    if(createData()) {
        if(sendData()) {
            if(readMethodReadyApp()) {
                onCallServer();
            }
        }
    }

    GLOGT(eGMSG, "[EMISSION] : (%d)\n%s", (int)m_dataOut.size(), m_dataOut.c_str());
    GLOGT(eGMSG, "[RECEPTION] : (%d)\n%s", (int)m_dataIn.size(), m_dataIn.c_str());

    closesocket(m_socket);
    WSACleanup();
    return true;
}
//===============================================
bool GSocket::sendData() {
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
int GSocket::readData(char* _data, int _size) {
    int lBytes = recv(m_socket, _data, _size, 0);
    return lBytes;
}
//===============================================
bool GSocket::readData(int _diffSize) {
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
bool GSocket::readMethodReadyApp() {
    char lBuffer[METHOD_SIZE + 1];
    int lBytes = readData(lBuffer, METHOD_SIZE);
    if(lBytes <= 0) return false;
    lBuffer[lBytes] = 0;
    m_dataIn += lBuffer;
    return true;
}
//===============================================
bool GSocket::createData() {return false;}
bool GSocket::onCallServer() {return false;}
//===============================================
