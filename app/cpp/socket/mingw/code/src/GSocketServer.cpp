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
    lServer.init();
    lServer.address();
    lServer.sockets2();
    lServer.binds();
    lServer.start();
    lServer.recvs(lClient);
    lServer.sends(lClient, "ok");
    lServer.print();
    lServer.close();
    lServer.clean();
}
//===============================================
