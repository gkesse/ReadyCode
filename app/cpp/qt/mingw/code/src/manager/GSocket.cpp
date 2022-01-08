//===============================================
#include "GSocket.h"
#include "GXml.h"
#include "GThread.h"
#include "GString.h"
#include "GLog.h"
//===============================================
GSocket* GSocket::m_instance = 0;
//===============================================
std::queue<std::string> GSocket::m_dataIn;
std::queue<GSocket*> GSocket::m_clientIn;
int GSocket::m_messageId = 1;
//===============================================
GSocket::GSocket(bool _init) : GObject() {
    m_socket = -1;

    if(_init) {
        createDoms();
    }
}
//===============================================
GSocket::~GSocket() {

}
//===============================================
GSocket* GSocket::Instance() {
    if(m_instance == 0) {
        m_instance = new GSocket(true);
    }
    return m_instance;
}
//===============================================
void GSocket::createDoms() {
    m_dom.reset(new GXml);
    m_dom->loadXmlFile(GRES("cpp/xml", "socket.xml"));
    m_dom->createXPath();
}
//===============================================
int GSocket::getMajor() const {
    m_dom->queryXPath("/rdv/socket/major");
    m_dom->getNodeXPath();
    std::string lData = m_dom->getNodeValue();
    return std::stoi(lData);
}
//===============================================
int GSocket::getMinor() const {
    m_dom->queryXPath("/rdv/socket/minor");
    m_dom->getNodeXPath();
    std::string lData = m_dom->getNodeValue();
    return std::stoi(lData);
}
//===============================================
bool GSocket::getVersionShow() const {
    m_dom->queryXPath("/rdv/socket/versionshow");
    m_dom->getNodeXPath();
    std::string lData = m_dom->getNodeValue();
    return (lData == "1");
}
//===============================================
bool GSocket::getHostnameShow() const {
    m_dom->queryXPath("/rdv/socket/hostnameshow");
    m_dom->getNodeXPath();
    std::string lData = m_dom->getNodeValue();
    return (lData == "1");
}
//===============================================
bool GSocket::getAddressIpShow() const {
    m_dom->queryXPath("/rdv/socket/addressipshow");
    m_dom->getNodeXPath();
    std::string lData = m_dom->getNodeValue();
    return (lData == "1");
}
//===============================================
bool GSocket::getWelcomShow() const {
    m_dom->queryXPath("/rdv/socket/welcomshow");
    m_dom->getNodeXPath();
    std::string lData = m_dom->getNodeValue();
    return (lData == "1");
}
//===============================================
bool GSocket::getDebugShow() const {
    m_dom->queryXPath("/rdv/socket/debugshow");
    m_dom->getNodeXPath();
    std::string lData = m_dom->getNodeValue();
    return (lData == "1");
}
//===============================================
std::string GSocket::getAddressClient() const {
    m_dom->queryXPath("/rdv/socket/address/client");
    m_dom->getNodeXPath();
    std::string lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
std::string GSocket::getAddressServer() const {
    m_dom->queryXPath("/rdv/socket/address/server");
    m_dom->getNodeXPath();
    std::string lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
int GSocket::getPort() const {
    m_dom->queryXPath("/rdv/socket/port");
    m_dom->getNodeXPath();
    std::string lData = m_dom->getNodeValue();
    return std::stoi(lData);
}
//===============================================
int GSocket::getBacklog() const {
    m_dom->queryXPath("/rdv/socket/backlog");
    m_dom->getNodeXPath();
    std::string lData = m_dom->getNodeValue();
    return std::stoi(lData);
}
//===============================================
void GSocket::initSocket(int _major, int _minor) {
    WSADATA lWsaData;
    WSAStartup(MAKEWORD(_major, _minor), &lWsaData);
}
//===============================================
bool GSocket::createSocketTcp() {
    m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(m_socket == INVALID_SOCKET) {
        GLOG->addError("Erreur la methode (createSocketTcp) a echoue.");
        return false;
    }
    return true;
}
//===============================================
bool GSocket::cretaeSocketUdp() {
    m_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(m_socket == INVALID_SOCKET) {
        GLOG->addError("Erreur la methode (cretaeSocketUdp) a echoue.");
        return false;
    }
    return true;
}
//===============================================
void GSocket::createAddress(const std::string& _ip, int _port) {
    m_address.sin_family = AF_INET;
    m_address.sin_addr.s_addr = inet_addr(_ip.c_str());
    m_address.sin_port = htons(_port);
    memset(&m_address.sin_zero, 0, sizeof(m_address.sin_zero));
}
//===============================================
bool GSocket::listenSocket(int _backlog) {
    int lAnswer = listen(m_socket, _backlog);
    if(lAnswer == SOCKET_ERROR) {
        GLOG->addError("Erreur la methode (listenSocket) a echoue.");
        return false;
    }
    return true;
}
//===============================================
bool GSocket::bindSocket() {
    int lAnswer = bind(m_socket, (SOCKADDR*)&m_address, sizeof(m_address));
    if(lAnswer == SOCKET_ERROR) {
        GLOG->addError("Erreur la methode (bindSocket) a echoue.");
        return false;
    }
    return true;
}
//===============================================
bool GSocket::connectToServer() {
    int lAnswer = connect(m_socket, (SOCKADDR*)(&m_address), sizeof(m_address));
    if(lAnswer == SOCKET_ERROR) {
        GLOG->addError("Erreur la methode (connectToServer) a echoue.");
        return false;
    }
    return true;
}
//===============================================
bool GSocket::acceptConnection(GSocket& _socket) {
    int lSize = sizeof(_socket.m_address);
    _socket.m_socket = accept(m_socket, (SOCKADDR*)&_socket.m_address, &lSize);
    if(_socket.m_socket == INVALID_SOCKET) {
        GLOG->addError("Erreur la methode (acceptConnection) a echoue.");
        return false;
    }
    return true;
}
//===============================================
int GSocket::recvData(std::string& _data) {
    char lBuffer[BUFFER_SIZE + 1];
    int lBytes = recv(m_socket, lBuffer, BUFFER_SIZE, 0);
    if(lBytes > 0) {
        lBuffer[lBytes] = 0;
        _data = lBuffer;
    }
    return lBytes;
}
//===============================================
int GSocket::readData(std::string& _data) {
    _data = "";
    std::string lData;
    int lIndex = 0;
    while(1) {
        int lBytes = recvData(lData);
        if(lBytes <= 0) break;
        lIndex += lBytes;
        _data += lData;
    }
    return lIndex;
}
//===============================================
int GSocket::recvData(GSocket& _socket, std::string& _data) {
    char lBuffer[BUFFER_SIZE + 1];
    int lSize = sizeof(_socket.m_address);
    int lBytes = recvfrom(m_socket, lBuffer, BUFFER_SIZE, 0, (SOCKADDR*)&_socket.m_address, &lSize);
    if(lBytes > 0) {
        lBuffer[lBytes] = 0;
        _data = lBuffer;
    }
    return lBytes;
}
//===============================================
void GSocket::sendData(const std::string& _data) {
    send(m_socket, _data.c_str(), _data.size(), 0);
}
//===============================================
void GSocket::writeData(const std::string& _data) {
    int lIndex = 0;
    char lBuffer[BUFFER_SIZE + 1];
    GString lData(_data);
    while(1) {
        int lBytes = lData.toChar(lBuffer, lIndex, BUFFER_SIZE);
        if(lBytes <= 0) break;
        lIndex += lBytes;
        sendData(lBuffer);
    }
}
//===============================================
void GSocket::sendData(GSocket& _socket, const std::string& _data) {
    int lSize = sizeof(_socket.m_address);
    sendto(m_socket, _data.c_str(), _data.size(), 0, (SOCKADDR*)&_socket.m_address, lSize);
}
//===============================================
std::string GSocket::getAddressIp() const {
    std::string lAddressIp = inet_ntoa(m_address.sin_addr);
    return lAddressIp;
}
//===============================================
std::string GSocket::getHostname() const {
    char lBuffer[HOSTNAME_SIZE + 1];
    gethostname(lBuffer, HOSTNAME_SIZE);
    std::string lHostname = lBuffer;
    return lHostname;
}
//===============================================
void GSocket::shutdownWR() {
    shutdown(m_socket, SD_SEND);
}
//===============================================
void GSocket::shutdownRD() {
    shutdown(m_socket, SD_RECEIVE);
}
//===============================================
void GSocket::closeSocket() {
    closesocket(m_socket);
}
//===============================================
void GSocket::cleanSocket() {
    WSACleanup();
}
//===============================================
void GSocket::startServerTcp() {
    GSocket lServer;
    GThread lThread;

    lServer.initSocket(getMajor(), getMinor());

    if(getVersionShow()) {
        printf("version socket : %d.%d\n", getMajor(), getMinor());
    }
    if(getHostnameShow()) {
        printf("nom machine : %s\n", getHostname().c_str());
    }

    lServer.createSocketTcp();
    lServer.createAddress(getAddressClient(), getPort());
    lServer.bindSocket();
    lServer.listenSocket(getBacklog());

    if(getWelcomShow()) {
        printf("Demarrage du serveur...\n");
    }

    while(1) {
        GSocket* lClient = new GSocket;
        lServer.acceptConnection(*lClient);

        if(getAddressIpShow()) {
            printf("adresse ip client : %s\n", lClient->getAddressIp().c_str());
        }

        lThread.createThread(onServerTcp, lClient);
    }

    lServer.cleanSocket();
    lServer.cleanSocket();
}
//===============================================
void GSocket::callServerTcp(const std::string& _dataIn, std::string& _dataOut) {
    GSocket lClient;

    lClient.initSocket(getMajor(), getMinor());

    if(getVersionShow()) {
        printf("version socket : %d.%d\n", getMajor(), getMinor());
    }
    if(getHostnameShow()) {
        printf("nom machine : %s\n", getHostname().c_str());
    }

    lClient.createSocketTcp();
    lClient.createAddress(getAddressServer(), getPort());
    lClient.connectToServer();

    lClient.writeData(_dataIn);
    lClient.shutdownWR();
    lClient.readData(_dataOut);

    lClient.cleanSocket();
    lClient.cleanSocket();
}
//===============================================
DWORD WINAPI GSocket::onServerTcp(LPVOID _params) {
    GSocket* lClient = (GSocket*)_params;
    std::string lDataIn;

    lClient->readData(lDataIn);
    lClient->shutdownRD();

    m_dataIn.push(lDataIn);
    m_clientIn.push(lClient);

    return 0;
}
//===============================================
std::queue<std::string>& GSocket::getDataIn() const {
    return m_dataIn;
}
//===============================================
std::queue<GSocket*>& GSocket::getClientIn() const {
    return m_clientIn;
}
//===============================================
int& GSocket::getMessageId() const {
    return m_messageId;
}
//===============================================
void GSocket::showMessage(const std::string& _dataIn) const {
    if(getDebugShow()) {
        printf("---------------> %d\n", m_messageId++);
        printf("%s\n", _dataIn.c_str());
    }
}
//===============================================
void GSocket::resultOk(const std::string& _dataOut) {
    std::string lDataOut = "<result>ok</result>";
    if(_dataOut != "") lDataOut = _dataOut;
    writeData(lDataOut);
    closeSocket();
}
//===============================================
