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
    lServer.address();
    lServer.sockets2();
    lServer.start();
    lServer.binds();
    lClient.recvs(lClient);
    lClient.sends(lClient, "ok");
    lClient.print();
    lClient.closes();
    lServer.closes();
}
//===============================================
