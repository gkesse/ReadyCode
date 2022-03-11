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
int GSocket::loadFamilyIp() const {
    int lFamilyIp = AF_INET;
    if(GLOGI->hasError()) return AF_INET;

    std::string lName = getSocketItem("family_ip");
    if(lName == "AF_INET") {
        lFamilyIp = AF_INET;
    }
    return lFamilyIp;
}
//===============================================
void GSocket::createSocket(int _domain, int _type, int _protocol) {
    if(GLOGI->hasError()) return;

    m_socket = socket(_domain, _type, _protocol);
    if(m_socket == -1) {
        GLOG("Erreur la methode (GSocket::createSocket) a echoue\n"
                "- erreur...: (%s).", errno);
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
                "- erreur...: (%s).", errno);
        return;
    }
}
//===============================================
void GSocket::bindSocket() {
    if(GLOGI->hasError()) return;

    int lAns = bind(m_socket, (struct sockaddr*)&m_address, sizeof(m_address));
    if(lAns == -1) {
        GLOG("Erreur la methode (GSocket::bindSocket) a echoue\n"
                "- erreur...: (%s).", errno);
        return;
    }
}
//===============================================
void GSocket::connectSocket() {
    if(GLOGI->hasError()) return;

    int lAns = connect(m_socket, (struct sockaddr*)&m_address, sizeof(m_address));
    if(lAns == -1) {
        GLOG("Erreur la methode (GSocket::connectSocket) a echoue\n"
                "- erreur...: (%s).", errno);
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
                "- erreur...: (%s).", errno);
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
                "- erreur...: (%s).", errno);
        return;
    }
}
//===============================================
int GSocket::recvData(std::string& _data) {
    printf("%s\n", __FUNCTION__);
    _data.clear();
    if(GLOGI->hasError()) return 0;

    char lBuffer[BUFFER_DATA_SIZE + 1];
    int lBytes = read(m_socket, lBuffer, BUFFER_DATA_SIZE);
    if(lBytes <= 0) {
        GLOG("Erreur la methode (GSocket::recvData) a echoue\n"
                "- erreur...: (%s).", errno);
        return 0;
    }
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
    if(lBytes <= 0) {
        GLOG("Erreur la methode (GSocket::recvData) a echoue\n"
                "- erreur...: (%s).", errno);
        return 0;
    }
    lBuffer[lBytes] = 0;
    _data = lBuffer;
    return lBytes;
}
//===============================================
int GSocket::readData(std::string& _data) {
    printf("%s\n", __FUNCTION__);
    _data.clear();
    if(GLOGI->hasError()) return 0;

    std::string lBuffer;
    recvData(lBuffer);
    int lSize = std::stoi(lBuffer);
    int lBytes = 0;
    printf("=> %d\n", lSize);

    for(int i = 0; i < lSize; i++) {
        int iBytes = recvData(lBuffer);
        if(iBytes <= 0) {
            GLOG("Erreur la methode (GSocket::readData) a echoue\n"
                    "- erreur...: (%s).", errno);
            return lBytes;
        }
        _data += lBuffer;
        lBytes += iBytes;
        printf("=> %d : %d\n", iBytes, (int)lBuffer.size());
    }
    return lBytes;
}
//===============================================
int GSocket::sendData(const std::string& _data) {
    printf("%s\n", __FUNCTION__);
    if(GLOGI->hasError()) return 0;

    int lBytes = write(m_socket, _data.c_str(), _data.size());
    if(lBytes <= 0) {
        GLOG("Erreur la methode (GSocket::sendData) a echoue\n"
                "- erreur...: (%s).", errno);
        return 0;
    }
    return lBytes;
}
//===============================================
int GSocket::sendData(GSocket& _socket, const std::string& _data) {
    if(GLOGI->hasError()) return 0;

    int lSize = sizeof(_socket.m_address);
    int lBytes = sendto(m_socket, _data.c_str(), _data.size(), 0, (struct sockaddr*)&_socket.m_address, lSize);
    if(lBytes <= 0) {
        GLOG("Erreur la methode (GSocket::sendData) a echoue\n"
                "- erreur...: (%s).", errno);
        return 0;
    }
    return lBytes;
}
//===============================================
int GSocket::writeData(const std::string& _data) {
    printf("%s\n", __FUNCTION__);
    if(GLOGI->hasError()) return 0;

    int lBytes = 0;
    int lLength = _data.size();
    int lSize = (int)ceil((double)lLength/BUFFER_DATA_SIZE);
    printf("=> %d\n", lSize);

    sendData(std::to_string(lSize));

    for(int i = 0; i < lSize; i++) {
        std::string lBuffer = _data.substr(lBytes, BUFFER_DATA_SIZE);
        int iBytes = sendData(lBuffer);
        if(iBytes <= 0) {
            GLOG("Erreur la methode (GSocket::sendData) a echoue\n"
                    "- erreur...: (%s).", errno);
            return lBytes;
        }
        lBytes += iBytes;
        printf("=> %d : %d\n", iBytes, (int)lBuffer.size());
    }

    return lBytes;
}
//===============================================
std::string GSocket::readAddressIp(int _familyIp) const {
    if(GLOGI->hasError()) return "";

    char lBuffer[BUFFER_IP_SIZE + 1];
    const char* lAns = inet_ntop(_familyIp, &(m_address.sin_addr), lBuffer, BUFFER_IP_SIZE);
    if(!lAns) {
        GLOG("Erreur la methode (GSocket::readAddressIp) a echoue\n"
                "- erreur........: (%s).\n"
                "- famille_ip....: (%d)", _familyIp);
        return "";
    }
    return lBuffer;
}
//===============================================
void GSocket::closeSocket() {
    if(GLOGI->hasError()) return;

    int lAns = close(m_socket);
    if(lAns == -1) {
        GLOG("Erreur la methode (GSocket::closeSocket) a echoue\n"
                "- erreur........: (%s).", errno);
        return;
    }
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
