//===============================================
#include "GSocket.h"
#include "GPath.h"
#include "GLog.h"
#include "GXml.h"
#include "GFormat.h"
#include "GThread.h"
//===============================================
GSocket::GSocket() : GObject() {
    createDoms();
    //
    m_socket = -1;
}
//===============================================
GSocket::~GSocket() {

}
//===============================================
void GSocket::createDoms() {
    m_dom.reset(new GXml);
    m_dom->loadXmlFile(GRES("xml", "pad.xml"));
    m_dom->createXPath();
}
//===============================================
std::string GSocket::getSocketItem(const std::string& _data) const {
    m_dom->queryXPath(sformat("/rdv/datas/data[code='socket']/%s", _data.c_str()));
    m_dom->getNodeXPath();
    std::string lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
int GSocket::loadDomain() const {
    std::string lName = getSocketItem("domain");
    int lDomain = AF_INET;
    if(lName == "AF_INET") {
        lDomain = AF_INET;
    }
    return lDomain;
}
//===============================================
int GSocket::loadType() const {
    std::string lName = getSocketItem("type");
    int lType = SOCK_STREAM;
    if(lName == "SOCK_STREAM") {
        lType = SOCK_STREAM;
    }
    return lType;
}
//===============================================
int GSocket::loadProtocol() const {
    std::string lName = getSocketItem("protocol");
    int lProtocol = IPPROTO_TCP;
    if(lName == "IPPROTO_TCP") {
        lProtocol = IPPROTO_TCP;
    }
    return lProtocol;
}
//===============================================
int GSocket::loadFamily() const {
    std::string lName = getSocketItem("family");
    int lFamily = AF_INET;
    if(lName == "AF_INET") {
        lFamily = AF_INET;
    }
    return lFamily;
}
//===============================================
int GSocket::loadFamilyIp() const {
    std::string lName = getSocketItem("family_ip");
    int lFamilyIp = AF_INET;
    if(lName == "AF_INET") {
        lFamilyIp = AF_INET;
    }
    return lFamilyIp;
}
//===============================================
void GSocket::createSocket(int _domain, int _type, int _protocol) {
    m_socket = socket(_domain, _type, _protocol);
}
//===============================================
void GSocket::createAddress(int _family, std::string _ip, int _port) {
    bzero(&m_address, sizeof(m_address));
    m_address.sin_family = _family;
    m_address.sin_addr.s_addr = inet_addr(_ip.c_str());
    m_address.sin_port = htons(_port);
}
//===============================================
void GSocket::listenSocket(int _backlog) {
    listen(m_socket, _backlog);
}
//===============================================
void GSocket::bindSocket() {
    bind(m_socket, (struct sockaddr*)&m_address, sizeof(m_address));
}
//===============================================
void GSocket::connectSocket() {
    connect(m_socket, (struct sockaddr*)&m_address, sizeof(m_address));
}
//===============================================
void GSocket::startMessage() {
    printf("=====>\n");
    printf("demarrage du serveur...\n");
}
//===============================================
void GSocket::acceptSocket(GSocket& _socket) {
    int lSize = sizeof(_socket.m_address);
    _socket.m_socket = accept(m_socket, (struct sockaddr*)&_socket.m_address, (socklen_t*)&lSize);
}
//===============================================
void GSocket::acceptSocket(GSocket* _socket) {
    int lSize = sizeof(_socket->m_address);
    _socket->m_socket = accept(m_socket, (struct sockaddr*)&_socket->m_address, (socklen_t*)&lSize);
}
//===============================================
int GSocket::recvData(std::string& _data) {
    char lBuffer[BUFFER_DATA_SIZE + 1];
    _data.clear();
    int lBytes = read(m_socket, lBuffer, BUFFER_DATA_SIZE);
    if(lBytes <= 0) lBytes = 0;
    lBuffer[lBytes] = 0;
    _data = lBuffer;
    return lBytes;
}
//===============================================
int GSocket::recvData(GSocket& _socket, std::string& _data) {
    char lBuffer[BUFFER_DATA_SIZE + 1];
    int lSize = sizeof(_socket.m_address);
    _data.clear();
    int lBytes = recvfrom(m_socket, lBuffer, BUFFER_DATA_SIZE, 0, (struct sockaddr*)&_socket.m_address, (socklen_t*)&lSize);
    if(lBytes <= 0) lBytes = 0;
    lBuffer[lBytes] = 0;
    _data = lBuffer;
    return lBytes;
}
//===============================================
int GSocket::readData(std::string& _data) {
    std::string lBuffer;
    recvData(lBuffer);
    int lSize = std::stoi(lBuffer);
    int lBytes = 0;
    _data.clear();

    for(int i = 0; i < lSize; i++) {
        lBytes += recvData(lBuffer);
        _data += lBuffer;
    }
    return lBytes;
}
//===============================================
int GSocket::sendData(const std::string& _data) {
    int lBytes = write(m_socket, _data.c_str(), _data.size());
    if(lBytes <= 0) lBytes = 0;
    return lBytes;
}
//===============================================
int GSocket::sendData(GSocket& _socket, const std::string& _data) {
    int lSize = sizeof(_socket.m_address);
    int lBytes = sendto(m_socket, _data.c_str(), _data.size(), 0, (struct sockaddr*)&_socket.m_address, lSize);
    if(lBytes <= 0) lBytes = 0;
    return lBytes;
}
//===============================================
int GSocket::writeData(const std::string& _data) {
    int lIndex = 0;
    int lLength = _data.size();
    int lSize = (int)ceil((double)lLength/BUFFER_DATA_SIZE);

    sendData(std::to_string(lSize));

    for(int i = 0; i < lSize; i++) {
        std::string lBuffer = _data.substr(lIndex, BUFFER_DATA_SIZE);
        lIndex += lBuffer.size();
        sendData(lBuffer);
    }

    return lIndex;
}
//===============================================
std::string GSocket::readAddressIp(int _familyIp) const {
    char lBuffer[BUFFER_IP_SIZE + 1];
    inet_ntop(_familyIp, &(m_address.sin_addr), lBuffer, BUFFER_IP_SIZE);
    return lBuffer;
}
//===============================================
void GSocket::closeSocket() {
    close(m_socket);
}
//===============================================
void GSocket::startServerTcp() {
    int lDomain = loadDomain();
    int lType = loadType();
    int lProtocol = loadProtocol();
    int lFamily = loadFamily();
    std::string lClientIp = getSocketItem("client_ip");
    int lPort = std::stoi(getSocketItem("port"));
    int lBacklog = std::stoi(getSocketItem("backlog"));

    createSocket(lDomain, lType, lProtocol);
    createAddress(lFamily, lClientIp, lPort);
    bindSocket();
    listenSocket(lBacklog);

    startMessage();

    GThread lThread;

    while(1) {
        GSocket* lClient = new GSocket;
        acceptSocket(lClient);
        lThread.createThread((void*)onServerTcp, lClient);
    }

    closeSocket();
}
//===============================================
void* GSocket::onServerTcp(GSocket* _client) {
    printf("%s\n", __FUNCTION__);

    GSocket* lClient = _client;

    std::string lData;
    lClient->readData(lData);
    lClient->writeData("<result>ok</result>");
    lClient->closeSocket();
    delete lClient;

    printf("=====>\n");
    printf("%s\n", lData.c_str());

    return 0;
}
//===============================================
std::string GSocket::callServerTcp(const std::string& _dataIn) {
    int lDomain = loadDomain();
    int lType = loadType();
    int lProtocol = loadProtocol();
    int lFamily = loadFamily();
    std::string lServerIp = getSocketItem("server_ip");
    int lPort = std::stoi(getSocketItem("port"));

    createSocket(lDomain, lType, lProtocol);
    createAddress(lFamily, lServerIp, lPort);
    connectSocket();

    std::string lDataOut;
    writeData(_dataIn);
    readData(lDataOut);
    closeSocket();

    return lDataOut;
}
//===============================================
