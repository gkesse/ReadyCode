//===============================================
#include "GManager.h"
#include "GStruct.h"
#include "GDefine.h"
#include "GSocket.h"
#include "GThread.h"
#include "GXml.h"
//===============================================
GManager::GManager() {

}
//===============================================
GManager::~GManager() {

}
//===============================================
void GManager::createPoint(std::string& _data, const std::string& _x, const std::string& _y, const std::string& _z) {
    GXml lXml, lData;
    lXml.removeBlank();
    lXml.createDoc();
    lXml.createRoot(RDV_DATA_ROOT);
    lXml.appendChild(RDV_DATA_MODULE, RDV_MOD_OPENCV);
    lXml.appendChild(RDV_DATA_METHOD, RDV_MET_DRAW_POINT);
    lXml.appendChild(lData, RDV_DATA_REF);
    lData.appendChild(RDV_POINT_X, "1.0");
    lData.appendChild(RDV_POINT_Y, "1.0");
    lData.appendChild(RDV_POINT_Z, "0.0");
    lXml.docToString(_data);
    lXml.freeDoc();
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
void GManager::startServer(void* _onStart) {
    sGSocket lSocket;
    lSocket.on_start = _onStart;
    startServer(lSocket);
}
//===============================================
