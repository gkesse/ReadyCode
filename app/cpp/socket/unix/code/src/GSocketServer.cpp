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
    lServer.sockets();
    lServer.binds();
    lServer.listens();
    lServer.start();
    lServer.accepts(lClient);
    lClient.recvs();
    lClient.sends("ok");
    lClient.print();
    lClient.close();
    lServer.close();
}
//===============================================
