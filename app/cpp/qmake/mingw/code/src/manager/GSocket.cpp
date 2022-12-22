//===============================================
#include "GSocket.h"
#include "GSocketEcho.h"
#include "GEnv.h"
#include "GCode.h"
#include "GLog.h"
//===============================================
GSocket::GSocket(const GString& _code)
: GObject(_code) {
    createDoms();
    initSocket();
}
//===============================================
GSocket::~GSocket() {

}
//===============================================
void GSocket::initSocket() {
    m_module        = GSocket::SOCKET_CLIENT_TCP;
    m_isTestEnv     = GEnv().isTestEnv();

    m_portProd      = GAPP->getData("socket", "port_prod").toInt();
    m_portTest      = GAPP->getData("socket", "port_test").toInt();
    m_port          = (m_isTestEnv ? m_portTest : m_portProd);
    m_backlog       = GAPP->getData("socket", "backlog").toInt();
    m_serverIp      = GAPP->getData("socket", "server_ip");
    m_clientIp      = GAPP->getData("socket", "client_ip");
    m_hostname      = m_serverIp;
    m_apiMethod     = GAPP->getData("socket", "api_method");
    m_apiKeyProd    = GAPP->getData("socket", "api_key_prod");
    m_apiKeyTest    = GAPP->getData("socket", "api_key_test");
    m_apiKey        = (m_isTestEnv ? m_apiKeyTest : m_apiKeyProd);
    m_apiUsername   = GAPP->getData("socket", "api_username");
    m_apiPassword   = GAPP->getData("socket", "api_password");
}
//===============================================
GSocket* GSocket::createSocket() {
    if(m_protocol == eGProtocol::PROTOCOL_ECHO) return new GSocketEcho;
    if(m_protocol == eGProtocol::PROTOCOL_RDVAPP) return new GSocket;
    if(m_protocol == eGProtocol::PROTOCOL_HTTP) return new GSocket;
    return new GSocketEcho;
}
//===============================================
void GSocket::setModule(eGModule _module) {
    m_module = _module;
}
//===============================================
void GSocket::setProtocol(eGProtocol _protocol) {
    m_protocol = _protocol;
}
//===============================================
bool GSocket::callServer(const GString& _dataIn, GString& _dataOut) {
    if(m_module == GSocket::SOCKET_CLIENT_TCP) return callServerTcp(_dataIn, _dataOut);
    if(m_module == GSocket::SOCKET_CLIENT_UDP) return callServerUdp(_dataIn, _dataOut);
    return callServerTcp(_dataIn, _dataOut);
}
//===============================================
GString GSocket::callServer(const GString& _module, const GString& _method, const GString& _data) {
    GCode lDom;
    lDom.createDoc();
    lDom.createRequest(_module, _method);
    lDom.loadData(_data);
    GString lDataIn = lDom.toString();
    GString lDataOut;
    GLOGT(eGMSG, lDataIn.c_str());
    callServer(lDataIn, lDataOut);
    GLOGT(eGMSG, lDataOut.c_str());
    GLOGI->deserialize(lDataOut);
    return lDataOut;
}
//===============================================
bool GSocket::callServerTcp(const GString& _dataIn, GString& _dataOut) {
    std::shared_ptr<GSocket> lSocket(createSocket());
    lSocket->onCallServerTcp(_dataIn, _dataOut);
    return true;
}
//===============================================
bool GSocket::onCallServerTcp(const GString& _dataIn, GString& _dataOut) {
    WSADATA lWsaData;
    WSAStartup(MAKEWORD(2, 2), &lWsaData);
    m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(m_socket == INVALID_SOCKET) {GERROR_ADD(eGERR, "Erreur lors de la connexion au serveur."); return false;}
    SOCKADDR_IN lAddress;
    lAddress.sin_family = AF_INET;
    lAddress.sin_addr.s_addr = inet_addr(m_hostname.c_str());
    lAddress.sin_port = htons(m_port);
    memset(&lAddress.sin_zero, 0, sizeof(lAddress.sin_zero));
    int lAnswer = connect(m_socket, (SOCKADDR*)(&lAddress), sizeof(lAddress));
    if(lAnswer == SOCKET_ERROR) {GERROR_ADD(eGERR, "Erreur lors de la connexion au serveur."); return false;}

    m_dataIn = _dataIn;
    onCallServer();

    GLOGT(eGMSG, "[EMISSION] : (%d)\n%s\n", m_dataIn.size(), m_dataIn.c_str());
    GLOGT(eGMSG, "[RECEPTION] : (%d)\n%s\n", m_dataOut.size(), m_dataOut.c_str());

    closesocket(m_socket);
    WSACleanup();
    return true;
}
//===============================================
bool GSocket::callServerUdp(const GString& _dataIn, GString& _dataOut) {
    return true;
}
//===============================================
bool GSocket::sendData(const GString& _dataIn) {
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
bool GSocket::sendDatas(const GString& _dataIn) {
    GString lData = GFORMAT("%*d%s", DATA_LENGTH_SIZE, _dataIn.size(), _dataIn.c_str());
    sendData(lData);
    return true;
}
//===============================================
bool GSocket::readDatas(GString& _dataOut) {
    GString lHeader;
    readData(lHeader, DATA_LENGTH_SIZE);
    int lDataSize = lHeader.substr(0, DATA_LENGTH_SIZE).toInt();
    if(lDataSize <= 0) return false;
    int lHeaderSize = lHeader.size();
    int lTotalSize = lDataSize + DATA_LENGTH_SIZE;
    int lDiffSize = lTotalSize - lHeaderSize;
    _dataOut = lHeader.substr(DATA_LENGTH_SIZE);
    readData(_dataOut, lDiffSize);
    return true;
}
//===============================================
bool GSocket::onCallServer() {return true;}
//===============================================
