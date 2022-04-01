//===============================================
#include "GSocket.h"
#include "GPath.h"
#include "GLog.h"
#include "GFormat.h"
#include "GXml.h"
#include "GThread.h"
#include "GCode.h"
#include "GString.h"
#include "GEnv.h"
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
    //
    m_res.reset(new GCode);
    m_res->createCode();

}
//===============================================
int GSocket::loadDomain() const {
    int lDomain = AF_INET;
    std::string lName = getItem("socket", "domain");
    if(lName == "AF_INET") {
        lDomain = AF_INET;
    }
    return lDomain;
}
//===============================================
int GSocket::loadType() const {
    int lType = SOCK_STREAM;
    std::string lName = getItem("socket", "type");
    if(lName == "SOCK_STREAM") {
        lType = SOCK_STREAM;
    }
    return lType;
}
//===============================================
int GSocket::loadProtocol() const {
    int lProtocol = IPPROTO_TCP;
    std::string lName = getItem("socket", "protocol");
    if(lName == "IPPROTO_TCP") {
        lProtocol = IPPROTO_TCP;
    }
    return lProtocol;
}
//===============================================
int GSocket::loadFamily() const {
    int lFamily = AF_INET;
    std::string lName = getItem("socket", "family");
    if(lName == "AF_INET") {
        lFamily = AF_INET;
    }
    return lFamily;
}
//===============================================
int GSocket::loadPort() const {
    return loadPort(GEnv().isTestEnv());
}
//===============================================
int GSocket::loadPort(int _isTestEnv) const {
    int lPort = std::stoi(getItem("socket", "prod_port"));
    if(_isTestEnv) lPort = std::stoi(getItem("socket", "test_port"));
    return lPort;
}
//===============================================
void GSocket::createSocket(int _domain, int _type, int _protocol) {
    m_socket = socket(_domain, _type, _protocol);
    if(m_socket == -1) {
        GERROR("Erreur la methode (GSocket::createSocket) a echoue\n"
                "- erreur...: (%s).", strerror(errno));
        return;
    }
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
    int lAns = listen(m_socket, _backlog);
    if(lAns == -1) {
        GERROR("Erreur la methode (GSocket::listenSocket) a echoue\n"
                "- erreur...: (%s).", strerror(errno));
        return;
    }
}
//===============================================
void GSocket::bindSocket() {
    int lAns = bind(m_socket, (struct sockaddr*)&m_address, sizeof(m_address));
    if(lAns == -1) {
        GERROR("Erreur la methode (GSocket::bindSocket) a echoue\n"
                "- erreur...: (%s).", strerror(errno));
        return;
    }
}
//===============================================
void GSocket::connectSocket() {
    int lAns = connect(m_socket, (struct sockaddr*)&m_address, sizeof(m_address));
    if(lAns == -1) {
        GERROR("Erreur la methode (GSocket::connectSocket) a echoue\n"
                "- erreur...: (%s).", strerror(errno));
        return;
    }
}
//===============================================
void GSocket::startMessage() {
    GLOGT(eGMSG, "demarrage du serveur...");
}
//===============================================
void GSocket::acceptSocket(GSocket& _socket) {
    int lSize = sizeof(_socket.m_address);
    _socket.m_socket = accept(m_socket, (struct sockaddr*)&_socket.m_address, (socklen_t*)&lSize);
    if(_socket.m_socket == -1) {
        GERROR("Erreur la methode (GSocket::acceptSocket) a echoue\n"
                "- erreur...: (%s).", strerror(errno));
        return;
    }
}
//===============================================
void GSocket::acceptSocket(GSocket* _socket) {
    int lSize = sizeof(_socket->m_address);
    _socket->m_socket = accept(m_socket, (struct sockaddr*)&_socket->m_address, (socklen_t*)&lSize);
    if(_socket->m_socket == -1) {
        GERROR("Erreur la methode (GSocket::acceptSocket) a echoue\n"
                "- erreur...: (%s).", strerror(errno));
        return;
    }
}
//===============================================
int GSocket::recvData(std::string& _data) {
    return recvData(_data, BUFFER_DATA_SIZE);
}
//===============================================
int GSocket::recvData(std::string& _data, int _size) {
    _data.clear();
    char lBuffer[BUFFER_DATA_SIZE + 1];
    int lBytes = recv(m_socket, lBuffer, _size, 0);
    if(lBytes == -1) {
        GERROR("Erreur la methode (GSocket::recvData) a echoue (1)\n"
                "- erreur...: (%s).\n"
                "- bytes....: (%d).", strerror(errno), lBytes);
        return -1;
    }
    lBuffer[lBytes] = 0;
    _data = lBuffer;
    return lBytes;
}
//===============================================
int GSocket::recvData(GSocket& _socket, std::string& _data) {
    _data.clear();
    char lBuffer[BUFFER_DATA_SIZE + 1];
    int lSize = sizeof(_socket.m_address);
    int lBytes = recvfrom(m_socket, lBuffer, BUFFER_DATA_SIZE, 0, (struct sockaddr*)&_socket.m_address, (socklen_t*)&lSize);
    if(lBytes == -1) {
        GERROR("Erreur la methode (GSocket::recvData) a echoue (2)\n"
                "- erreur...: (%s).\n"
                "- bytes....: (%d).", strerror(errno), lBytes);
        return -1;
    }
    lBuffer[lBytes] = 0;
    _data = lBuffer;
    return lBytes;
}
//===============================================
int GSocket::readData(std::string& _data) {
    _data.clear();
    std::string lBuffer;
    recvData(lBuffer, BUFFER_NDATA_SIZE);
    GLOGT(eGMSG, "[%s]", lBuffer.c_str());
    int lSize = std::stoi(GString(lBuffer).trimData());
    int lBytes = 0;

    for(int i = 0; i < lSize; i++) {
        int iBytes = recvData(lBuffer);
        if(iBytes == -1) {
            GERROR("Erreur la methode (GSocket::readData) a echoue\n"
                    "- erreur....: (%s).\n"
                    "- bytes.....: (%d).\n"
                    "- ibytes....: (%d).", strerror(errno), lBytes, iBytes);
            return -1;
        }
        _data += lBuffer;
        lBytes += iBytes;
    }
    GLOGT(eGMSG, "%s", _data.c_str());
    return lBytes;
}
//===============================================
int GSocket::sendData(const std::string& _data) {
    int lBytes = send(m_socket, _data.c_str(), _data.size(), 0);
    if(lBytes == -1) {
        GERROR("Erreur la methode (GSocket::sendData) a echoue (1)\n"
                "- erreur...: (%s).\n"
                "- bytes....: (%d).", strerror(errno), lBytes);
        return -1;
    }
    return lBytes;
}
//===============================================
int GSocket::sendData(GSocket& _socket, const std::string& _data) {
    int lSize = sizeof(_socket.m_address);
    int lBytes = sendto(m_socket, _data.c_str(), _data.size(), 0, (struct sockaddr*)&_socket.m_address, lSize);
    if(lBytes == -1) {
        GERROR("Erreur la methode (GSocket::sendData) a echoue (2)\n"
                "- erreur...: (%s).\n"
                "- bytes....: (%d).", strerror(errno), lBytes);
        return -1;
    }
    return lBytes;
}
//===============================================
int GSocket::writeData(const std::string& _data) {
    int lBytes = 0;
    int lLength = _data.size();
    int lSize = (int)ceil((double)lLength/BUFFER_DATA_SIZE);
    std::string lBuffer = iformat(lSize, BUFFER_NDATA_SIZE);
    GLOGT(eGMSG, "[%s]", lBuffer.c_str());
    sendData(lBuffer);

    GLOGT(eGMSG, "%s", _data.c_str());
    for(int i = 0; i < lSize; i++) {
        std::string lBuffer = _data.substr(lBytes, BUFFER_DATA_SIZE);
        int iBytes = sendData(lBuffer);
        if(iBytes == -1) {
            GERROR("Erreur la methode (GSocket::sendData) a echoue\n"
                    "- erreur....: (%s).\n"
                    "- bytes.....: (%d).\n"
                    "- ibytes....: (%d).", strerror(errno), lBytes, iBytes);
            return -1;
        }
        lBytes += iBytes;
    }

    return lBytes;
}
//===============================================
void GSocket::closeSocket() {
    int lAns = close(m_socket);
    if(lAns == -1) {
        GERROR("Erreur la methode (GSocket::closeSocket) a echoue\n"
                "- erreur........: (%s).", strerror(errno));
        return;
    }
}
//===============================================
void GSocket::startServer(void* _onServerTcp) {
    int lDomain = loadDomain();
    int lType = loadType();
    int lProtocol = loadProtocol();
    int lFamily = loadFamily();
    std::string lClientIp = getItem("socket", "client_ip");
    int lPort = loadPort();
    int lBacklog = std::stoi(getItem("socket", "backlog"));

    GLOGT(eGMSG, "");
    GLOGW(eGMSG, "domain......: %d", lDomain);
    GLOGW(eGMSG, "type........: %d", lType);
    GLOGW(eGMSG, "protocol....: %d", lProtocol);
    GLOGW(eGMSG, "family......: %d", lFamily);
    GLOGW(eGMSG, "port........: %d", lPort);
    GLOGW(eGMSG, "backlog.....: %d", lBacklog);

    createSocket(lDomain, lType, lProtocol);
    createAddress(lFamily, lClientIp, lPort);
    bindSocket();
    listenSocket(lBacklog);

    startMessage();

    GThread lThread;

    while(1) {
        GSocket* lClient = new GSocket;
        lClient->m_server = this;
        acceptSocket(lClient);
        lThread.createThread(_onServerTcp, lClient);
    }

    closeSocket();
}
//===============================================
void* GSocket::onServerThread(GSocket* _client) {
    GSocket* lClient = _client;
    GSocket* lServer = lClient->m_server;
    std::queue<GSocket*>& lClientIns = lServer->m_clientIns;

    std::string lData;
    lClient->readData(lData);
    lClient->setRequest(lData);
    lClientIns.push(lClient);
    return 0;
}
//===============================================
std::string GSocket::callServer(const std::string& _dataIn) {
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
void GSocket::setRequest(const std::string& _req) {
    m_request = _req;
}
//===============================================
std::string GSocket::getRequest() const {
    return m_request;
}
//===============================================
std::queue<std::string>& GSocket::getDataIns() {
    return m_dataIns;
}
//===============================================
std::queue<GSocket*>& GSocket::getClientIns() {
    return m_clientIns;
}
//===============================================
std::shared_ptr<GCode>& GSocket::getResponse(){
    return m_res;
}
//===============================================
std::string GSocket::readAddressIp() const {
    std::string lAddressIp = inet_ntoa(m_address.sin_addr);
    return lAddressIp;
}
//===============================================
