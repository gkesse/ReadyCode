//===============================================
#include "GSocket.h"
#include "GPath.h"
#include "GLog.h"
#include "GXml.h"
#include "GFormat.h"
#include "GThread.h"
#include "GHostname.h"
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
    if(GLOGI->hasError()) return;
    m_dom.reset(new GXml);
    m_dom->loadXmlFile(GRES("xml", "pad.xml"));
    m_dom->createXPath();
}
//===============================================
std::string GSocket::getSocketItem(const std::string& _data) const {
    if(GLOGI->hasError()) return "";
    m_dom->queryXPath(sformat("/rdv/datas/data[code='socket']/%s", _data.c_str()));
    m_dom->getNodeXPath();
    std::string lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
int GSocket::loadDomain() const {
    int lDomain = AF_INET;
    if(GLOGI->hasError()) return lDomain;
    std::string lName = getSocketItem("domain");
    if(lName == "AF_INET") {
        lDomain = AF_INET;
    }
    return lDomain;
}
//===============================================
int GSocket::loadType() const {
    int lType = SOCK_STREAM;
    if(GLOGI->hasError()) return lType;
    std::string lName = getSocketItem("type");
    if(lName == "SOCK_STREAM") {
        lType = SOCK_STREAM;
    }
    return lType;
}
//===============================================
int GSocket::loadProtocol() const {
    int lProtocol = IPPROTO_TCP;
    if(GLOGI->hasError()) return lProtocol;
    std::string lName = getSocketItem("protocol");
    if(lName == "IPPROTO_TCP") {
        lProtocol = IPPROTO_TCP;
    }
    return lProtocol;
}
//===============================================
int GSocket::loadFamily() const {
    int lFamily = AF_INET;
    if(GLOGI->hasError()) return lFamily;
    std::string lName = getSocketItem("family");
    if(lName == "AF_INET") {
        lFamily = AF_INET;
    }
    return lFamily;
}
//===============================================
void GSocket::createSocket(int _domain, int _type, int _protocol) {
    if(GLOGI->hasError()) return;
    m_socket = socket(_domain, _type, _protocol);
    if(m_socket == -1) {
        GLOG("Erreur la methode (GSocket::createSocket) a echoue\n"
                "- erreur...: (%s).", strerror(errno));
        return;
    }
}
//===============================================
void GSocket::createAddress(int _family, std::string _ip, int _port) {
    if(GLOGI->hasError()) return;
    bzero(&m_address, sizeof(m_address));
    m_address.sin_family = _family;
    m_address.sin_addr.s_addr = inet_addr(_ip.c_str());
    m_address.sin_port = htons(_port);
}
//===============================================
void GSocket::listenSocket(int _backlog) {
    if(GLOGI->hasError()) return;
    int lAns = listen(m_socket, _backlog);
    if(lAns == -1) {
        GLOG("Erreur la methode (GSocket::listenSocket) a echoue\n"
                "- erreur...: (%s).", strerror(errno));
        return;
    }
}
//===============================================
void GSocket::bindSocket() {
    if(GLOGI->hasError()) return;
    int lAns = bind(m_socket, (struct sockaddr*)&m_address, sizeof(m_address));
    if(lAns == -1) {
        GLOG("Erreur la methode (GSocket::bindSocket) a echoue\n"
                "- erreur...: (%s).", strerror(errno));
        return;
    }
}
//===============================================
void GSocket::connectSocket() {
    if(GLOGI->hasError()) return;
    int lAns = connect(m_socket, (struct sockaddr*)&m_address, sizeof(m_address));
    if(lAns == -1) {
        GLOG("Erreur la methode (GSocket::connectSocket) a echoue\n"
                "- erreur...: (%s).", strerror(errno));
        return;
    }
}
//===============================================
void GSocket::startMessage() {
    if(GLOGI->hasError()) return;
    printf("=====>\n");
    printf("demarrage du serveur...\n");
}
//===============================================
void GSocket::acceptSocket(GSocket& _socket) {
    if(GLOGI->hasError()) return;
    int lSize = sizeof(_socket.m_address);
    _socket.m_socket = accept(m_socket, (struct sockaddr*)&_socket.m_address, (socklen_t*)&lSize);
    if(_socket.m_socket == -1) {
        GLOG("Erreur la methode (GSocket::acceptSocket) a echoue\n"
                "- erreur...: (%s).", strerror(errno));
        return;
    }
}
//===============================================
void GSocket::acceptSocket(GSocket* _socket) {
    if(GLOGI->hasError()) return;
    int lSize = sizeof(_socket->m_address);
    _socket->m_socket = accept(m_socket, (struct sockaddr*)&_socket->m_address, (socklen_t*)&lSize);
    if(_socket->m_socket == -1) {
        GLOG("Erreur la methode (GSocket::acceptSocket) a echoue\n"
                "- erreur...: (%s).", strerror(errno));
        return;
    }
}
//===============================================
int GSocket::recvData(std::string& _data) {
    _data.clear();
    if(GLOGI->hasError()) return -1;
    char lBuffer[BUFFER_DATA_SIZE + 1];
    int lBytes = recv(m_socket, lBuffer, BUFFER_DATA_SIZE, 0);
    if(lBytes == -1) {
        GLOG("Erreur la methode (GSocket::recvData) a echoue (1)\n"
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
    if(GLOGI->hasError()) return -1;
    char lBuffer[BUFFER_DATA_SIZE + 1];
    int lSize = sizeof(_socket.m_address);
    int lBytes = recvfrom(m_socket, lBuffer, BUFFER_DATA_SIZE, 0, (struct sockaddr*)&_socket.m_address, (socklen_t*)&lSize);
    if(lBytes == -1) {
        GLOG("Erreur la methode (GSocket::recvData) a echoue (2)\n"
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
    if(GLOGI->hasError()) return -1;
    std::string lBuffer;
    recvData(lBuffer);
    int lSize = std::stoi(lBuffer);
    int lBytes = 0;

    for(int i = 0; i < lSize; i++) {
        int iBytes = recvData(lBuffer);
        if(iBytes == -1) {
            GLOG("Erreur la methode (GSocket::readData) a echoue\n"
                    "- erreur....: (%s).\n"
                    "- bytes.....: (%d).\n"
                    "- ibytes....: (%d).", strerror(errno), lBytes, iBytes);
            return -1;
        }
        _data += lBuffer;
        lBytes += iBytes;
    }
    return lBytes;
}
//===============================================
int GSocket::sendData(const std::string& _data) {
    if(GLOGI->hasError()) return -1;
    int lBytes = send(m_socket, _data.c_str(), _data.size(), 0);
    if(lBytes == -1) {
        GLOG("Erreur la methode (GSocket::sendData) a echoue (1)\n"
                "- erreur...: (%s).\n"
                "- bytes....: (%d).", strerror(errno), lBytes);
        return -1;
    }
    return lBytes;
}
//===============================================
int GSocket::sendData(GSocket& _socket, const std::string& _data) {
    if(GLOGI->hasError()) return -1;
    int lSize = sizeof(_socket.m_address);
    int lBytes = sendto(m_socket, _data.c_str(), _data.size(), 0, (struct sockaddr*)&_socket.m_address, lSize);
    if(lBytes == -1) {
        GLOG("Erreur la methode (GSocket::sendData) a echoue (2)\n"
                "- erreur...: (%s).\n"
                "- bytes....: (%d).", strerror(errno), lBytes);
        return -1;
    }
    return lBytes;
}
//===============================================
int GSocket::writeData(const std::string& _data) {
    if(GLOGI->hasError()) return -1;
    int lBytes = 0;
    int lLength = _data.size();
    int lSize = (int)ceil((double)lLength/BUFFER_DATA_SIZE);

    sendData(iformat(lSize, BUFFER_DATA_SIZE));

    for(int i = 0; i < lSize; i++) {
        std::string lBuffer = _data.substr(lBytes, BUFFER_DATA_SIZE);
        int iBytes = sendData(lBuffer);
        if(iBytes == -1) {
            GLOG("Erreur la methode (GSocket::sendData) a echoue\n"
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
    if(GLOGI->hasError()) return;
    int lAns = close(m_socket);
    if(lAns == -1) {
        GLOG("Erreur la methode (GSocket::closeSocket) a echoue\n"
                "- erreur........: (%s).", strerror(errno));
        return;
    }
}
//===============================================
void GSocket::startServerTcp(void* _onServerTcp) {
    if(GLOGI->hasError()) return;
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
        if(GLOGI->hasError()) break;
        GSocket* lClient = new GSocket;
        lClient->m_server = this;
        acceptSocket(lClient);
        lThread.createThread(_onServerTcp, lClient);
    }

    closeSocket();
}
//===============================================
void* GSocket::onServerTcp(GSocket* _client) {
    if(GLOGI->hasError()) return 0;
    GSocket* lClient = _client;
    GSocket* lServer = lClient->m_server;
    std::queue<std::string>& lDataIns = lServer->m_dataIns;
    std::queue<GSocket*>& lClientIns = lServer->m_clientIns;

    GHostname lHostname;
    lHostname.onSaveHostname("", lClient);

    std::string lData;
    lClient->readData(lData);
    lDataIns.push(lData);
    lClientIns.push(lClient);
    lClient->writeData("<result>ok</result>");
    lClient->closeSocket();
    delete lClient;
    return 0;
}
//===============================================
std::string GSocket::callServerTcp(const std::string& _dataIn) {
    if(GLOGI->hasError()) return "";
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
std::queue<std::string>& GSocket::getDataIns() {
    return m_dataIns;
}
//===============================================
std::queue<GSocket*>& GSocket::getClientIns() {
    return m_clientIns;
}
//===============================================
std::string GSocket::readAddressIp() const {
    std::string lAddressIp = inet_ntoa(m_address.sin_addr);
    return lAddressIp;
}
//===============================================
