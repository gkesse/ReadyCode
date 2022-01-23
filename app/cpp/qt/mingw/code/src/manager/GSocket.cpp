//===============================================
#include "GSocket.h"
#include "GDescriptor.h"
#include "GThread.h"
#include "GTimer.h"
#include "GString.h"
#include "GXml.h"
#include "GLog.h"
//===============================================
GSocket* GSocket::m_instance = 0;
GSocket* GSocket::m_socketObj = 0;
int GSocket::m_messageId = 1;
//===============================================
GSocket::GSocket() : GObject() {
    m_socket = 0;
    m_serverOn = true;
    m_onServerTcp = onServerTcp;
    m_onClientTcp = onClientTcp;
    m_hasBroadcast = false;
    m_hasBroadcastExclusive = false;
    m_hasResponseLoop = false;
    m_readOn = false;
    createDoms();
}
//===============================================
GSocket::~GSocket() {

}
//===============================================
GSocket* GSocket::Instance() {
    if(m_instance == 0) {
        m_instance = new GSocket;
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
    //send(m_socket, "ok", 2, 0);
    return lBytes;
}
//===============================================
int GSocket::readData(std::string& _data) {
    _data = "";
    std::string lData;
    int lIndex = 0;
    for(int i = 0; i < 1; i++) {
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
    //char lBuffer[3];
    send(m_socket, _data.c_str(), _data.size(), 0);
    /*int lBytes = recv(m_socket, lBuffer, 3, 0);
    if(lBytes > 0) {
        lBuffer[lBytes] = 0;
    }*/
}
//===============================================
void GSocket::writeData(const std::string& _data) {
    int lIndex = 0;
    char lBuffer[BUFFER_SIZE + 1];
    GString lData(_data);
    for(int i = 0; i < 1; i++) {
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
void GSocket::stopServer() {
    m_serverOn = false;
}
//===============================================
bool GSocket::isServerOn() const {
    return m_serverOn;
}
//===============================================
void GSocket::startServerTcp() {
    initSocket(getMajor(), getMinor());

    if(getVersionShow()) {
        printf("version socket : %d.%d\n", getMajor(), getMinor());
    }
    if(getHostnameShow()) {
        printf("nom machine : %s\n", getHostname().c_str());
    }

    createSocketTcp();
    createAddress(getAddressClient(), getPort());
    bindSocket();
    listenSocket(getBacklog());

    if(getWelcomShow()) {
        printf("Demarrage du serveur...\n");
    }

    GThread lThread;

    while(1) {
        GSocket* lClient = new GSocket;
        acceptConnection(*lClient);
        lClient->m_server = this;

        if(getAddressIpShow()) {
            printf("adresse ip client : %s\n", lClient->getAddressIp().c_str());
        }

        lThread.createThread(m_onServerTcp, lClient);
    }

    closeSocket();
    cleanSocket();
}
//===============================================
void GSocket::callServerTcp(const std::string& _dataIn, std::string& _dataOut) {
    initSocket(getMajor(), getMinor());

    if(getVersionShow()) {
        printf("version socket : %d.%d\n", getMajor(), getMinor());
    }
    if(getHostnameShow()) {
        printf("nom machine : %s\n", getHostname().c_str());
    }

    createSocketTcp();
    createAddress(getAddressServer(), getPort());
    connectToServer();

    writeData(_dataIn);
    readData(_dataOut);

    cleanSocket();
    cleanSocket();
}
//===============================================
void GSocket::callServerTcp(const GObject& _request, std::string& _dataOut) {
    callServerTcp(_request.toString(), _dataOut);
}
//===============================================
DWORD WINAPI GSocket::onServerTcp(LPVOID _params) {
    GSocket* lClient = (GSocket*)_params;
    GSocket* lServer = lClient->m_server;
    std::queue<std::string>& lDataIn = lServer->m_dataIn;
    std::queue<GSocket*>& lClientIn = lServer->m_clientIn;

    std::string lDataRD;

    lClient->readData(lDataRD);

    lDataIn.push(lDataRD);
    lClientIn.push(lClient);

    return 0;
}
//===============================================
void GSocket::startClientTcp() {
    m_socketObj = this;

    initSocket(getMajor(), getMinor());

    if(getVersionShow()) {
        printf("version socket : %d.%d\n", getMajor(), getMinor());
    }
    if(getHostnameShow()) {
        printf("nom machine : %s\n", getHostname().c_str());
    }

    createSocketTcp();
    createAddress(getAddressServer(), getPort());
    connectToServer();

    GThread lThread;
    lThread.createThread(m_onClientTcp, this);
}
//===============================================
DWORD WINAPI GSocket::onClientTcp(LPVOID _params) {
    GSocket* lClient = (GSocket*)_params;
    std::queue<std::string>& lDataAns = lClient->m_dataAns;
    std::string lData;

    while(1) {
        lClient->readData(lData);
        if(lData == "") {
            lClient->closeSocket();
            lClient->cleanSocket();
            delete lClient;
            break;
        }
        lDataAns.push(lData);
    }

    return 0;
}
//===============================================
void GSocket::setOnServerTcp(GThread::onThreadCB _onServerTcp) {
    m_onServerTcp = _onServerTcp;
}
//===============================================
void GSocket::setOnClientTcp(GThread::onThreadCB _onClientTcp) {
    m_onClientTcp = _onClientTcp;
}
//===============================================
void GSocket::addDataIn(const std::string& _data) {
    m_dataIn.push(_data);
}
//===============================================
void GSocket::addDataIn(const GObject& _data) {
    m_dataIn.push(_data.toString());
}
//===============================================
std::queue<std::string>& GSocket::getDataIn() {
    return m_dataIn;
}
//===============================================
std::queue<GSocket*>& GSocket::getClientIn() {
    return m_clientIn;
}
//===============================================
std::queue<GSocket*>& GSocket::getClientAns() {
    return m_clientAns;
}
//===============================================
std::map<std::string, GSocket*>& GSocket::getClientMap() {
    return m_clientMap;
}
//===============================================
GSocket* GSocket::getServer() const {
    return m_server;
}
//===============================================
std::string GSocket::getRequest() const {
    return m_request;
}
//===============================================
void GSocket::setRequest(const std::string& _request) {
    m_request = _request;
}
//===============================================
void GSocket::showMessage(const std::string& _dataIn) const {
    if(getDebugShow()) {
        printf("-----> %d\n", GSocket::m_messageId++);
        printf("%s\n", _dataIn.c_str());
    }
}
//===============================================
void GSocket::addDataAns(const std::string& _data) {
    m_dataAns.push(_data);
}
//===============================================
std::queue<std::string>& GSocket::getDataAns() {
    return m_dataAns;
}
//===============================================
void GSocket::addDataOut(const std::string& _data) {
    m_dataOut.push_back(_data);
}
//===============================================
void GSocket::addDataOut(const GObject& _data) {
    m_dataOut.push_back(_data.toString());
}
//===============================================
void GSocket::addResultOk(const std::string& _data) {
    m_resultOk.push_back(_data);
}
//===============================================
void GSocket::addResultOk(const GObject& _data) {
    m_resultOk.push_back(_data.toString());
}
//===============================================
void GSocket::addErrors(const std::string& _data) {
    m_errors.push_back(_data);
}
//===============================================
void GSocket::addErrors(const GObject& _data) {
    m_errors.push_back(_data.toString());
}
//===============================================
std::string GSocket::getDataOut() const {
    std::string lDataOut = "";
    std::string lResultOk = "";
    std::string lErrors = "";

    for(size_t i = 0; i < m_dataOut.size(); i++) {
        if(i != 0) lDataOut += "\n";
        lDataOut += m_dataOut.at(i);
    }
    for(size_t i = 0; i < m_resultOk.size(); i++) {
        if(i != 0) lResultOk += "\n";
        lResultOk += m_resultOk.at(i);
    }
    for(size_t i = 0; i < m_errors.size(); i++) {
        if(i != 0) lErrors += "\n";
        lErrors += m_errors.at(i);
    }
    if(lErrors != "") {
        return lErrors;
    }
    if(lDataOut != "") {
        return lDataOut;
    }
    return lResultOk;
}
//===============================================
void GSocket::sendResponse() {
    if(hasResponseLoop()) {
        std::queue<std::string>& lDataAns = m_server->getDataAns();
        std::queue<GSocket*>& lClientAns = m_server->getClientAns();
        lDataAns.push(getDataOut());
        lClientAns.push(this);
    }
    else {
        writeData(getDataOut());
        closeSocket();
    }
}
//===============================================
void GSocket::setResponseLoop(bool _hasResponseLoop) {
    m_hasResponseLoop = _hasResponseLoop;
}
//===============================================
bool GSocket::hasResponseLoop() const {
    return m_hasResponseLoop;
}
//===============================================
void GSocket::setBroadcast(bool _hasBroadcast) {
    m_hasBroadcast = _hasBroadcast;
}
//===============================================
bool GSocket::hasBroadcast() const {
    return m_hasBroadcast;
}
//===============================================
void GSocket::setBroadcastExclusive(bool _hasBroadcastExclusive) {
    m_hasBroadcastExclusive = _hasBroadcastExclusive;
}
//===============================================
bool GSocket::hasBroadcastExclusive() const {
    return m_hasBroadcastExclusive;
}
//===============================================
bool GSocket::hasReadData() {
    m_fdRead.reset(new GDescriptor);
    m_fdRead->initDescriptor();
    m_fdRead->enableDescriptor(m_socket);
    m_fdRead->initTimeout(10);
    bool lOk = m_fdRead->selectDescriptor();
    return lOk;
}
//===============================================
void GSocket::addClient(const std::string& _id, GSocket* _socket) {
    if(m_clientMap.count(_id) == 0) {
        m_clientMap[_id] = _socket;
        showMessage(sformat("nombre de clients (%d)", (int)m_clientMap.size()));
    }
    else {
        GLOG->addError(sformat("Erreur la methode (addClient) a echoue "
                "sur l'ID (%s).", _id.c_str()));
    }
}
//===============================================
void GSocket::removeClient() {
    std::map<std::string, GSocket*>& lClientMap = m_server->getClientMap();
    std::map<std::string, GSocket*>::iterator it;

    for (it = lClientMap.begin(); it != lClientMap.end(); it++) {
        GSocket* lClient = it->second;
        if(lClient == this) {
            lClientMap.erase(it);
            break;
        }
    }
}
//===============================================
