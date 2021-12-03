//===============================================
#include "GManager.h"
#include "GXml.h"
#include "GThread.h"
#include "GSocket.h"
#include "GDefine.h"
//===============================================
GManager* GManager::m_instance = 0;
//===============================================
GManager::GManager() {

}
//===============================================
GManager::~GManager() {

}
//===============================================
GManager* GManager::Instance() {
    if(m_instance == 0) {
        m_instance = new GManager;
    }
    return m_instance;
}
//===============================================
void GManager::getModule(const std::string& _dataIn, std::string& _module) {
    GXml lXml;
    lXml.parseData(_dataIn).getRoot();
    lXml(RDV_DATA_MODULE).getNodeValue(_module);
}
//===============================================
void GManager::getMethod(const std::string& _dataIn, std::string& _method) {
    GXml lXml;
    lXml.parseData(_dataIn).getRoot();
    lXml(RDV_DATA_METHOD).getNodeValue(_method);
}
//===============================================
void GManager::getData(const std::string& _dataIn, int _index, std::string& _data) {
    GXml lXml;
    lXml.parseData(_dataIn).getRoot();
    lXml.firstChild(lXml).nextSibling(lXml).nextSibling(lXml).firstChild(lXml);
    for(int i = 0; i < _index; i++) {
    	lXml.nextSibling(lXml);
    }
    lXml.getNodeValue(_data);
}
//===============================================
void GManager::getPoint(sGPoint& _point, const std::string& _x, const std::string& _y, const std::string& _z) {
    _point.x = std::stof(_x);
    _point.y = std::stof(_y);
    _point.z = std::stof(_z);
}
//===============================================
void GManager::callServer(const std::string& _dataIn, std::string& _dataOut) {
    GSocket lClient;
    sGSocket lParams;
    lParams.address_ip = "127.0.0.1";
    lClient.initSocket(lParams.major, lParams.minor);
    lClient.getHostname(lParams.hostname);
    lClient.createAddress(lParams.address_ip, lParams.port);
    lClient.createSocketTcp();
    lClient.connectToServer();
    lClient.writeData(_dataIn);
    lClient.shutdownWR();
    lClient.readData(_dataOut);
    lClient.closeSocket();
    lClient.cleanSocket();
}
//===============================================
void GManager::startServer(sGSocket& _socket) {
    GSocket lServer;
    GThread lThread;

    lServer.initSocket(_socket.major, _socket.minor);
    lServer.getHostname(_socket.hostname);
    lServer.createAddress(_socket.address_ip, _socket.port);
    lServer.createSocketTcp();
    lServer.bindSocket();
    lServer.listenSocket(_socket.backlog);

    printf("Demarrage du serveur...\n");

    if(_socket.hostname_on) {
        printf("Hostname.....: %s\n", _socket.hostname.c_str());
    }

    while(1) {
        GSocket* lClient = new GSocket;
        lServer.acceptConnection(*lClient);
        lClient->getAddressIp(_socket.client_ip);
        _socket.socket = lClient;
        lThread.createThread((GThread::onThreadCB)_socket.on_start, &_socket);
    }

    lServer.closeSocket();
    lServer.cleanSocket();
}
//===============================================
void GManager::startServer(void* _onStartServer) {
    sGSocket lSocket;
    lSocket.on_start = _onStartServer;
    startServer(lSocket);
}
//===============================================
void GManager::onStartServer(void* _params, std::queue<std::string>& _data) {
    sGSocket* lSocket = (sGSocket*)_params;
    GSocket* lClient = lSocket->socket;
    std::string lData;
    lClient->readData(lData);
    lClient->writeData("OK");
    _data.push(lData);
    lClient->closeSocket();
    delete lClient;
}
//===============================================
