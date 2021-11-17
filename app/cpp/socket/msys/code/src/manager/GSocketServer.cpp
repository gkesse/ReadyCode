//===============================================
#include "GSocketServer.h"
#include "GFile.h"
#include "GString.h"
#include "GSocket.h"
//===============================================
GSocketServer::GSocketServer() {

}
//===============================================
GSocketServer::~GSocketServer() {

}
//===============================================
void GSocketServer::run(int argc, char** argv) {
    GSocket lServer;
    GSocket lClient;
    GString lData;
    lServer.init();
    lServer.address();
    lServer.createSocketTcp();
    lServer.bindSocket();
    lServer.listens();
    lServer.start();
    lServer.acceptConnection(lClient);
    lClient.recvs(lData);
    lData.print();
    lClient.closeSocket();
    lServer.closeSocket();
    lServer.cleanSocket();
}
//===============================================
