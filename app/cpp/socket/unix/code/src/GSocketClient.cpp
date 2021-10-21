//===============================================
#include "GSocketClient.h"
#include "GSocket.h"
#include "GFile.h"
#include "GManager.h"
//===============================================
GSocketClient::GSocketClient() {

}
//===============================================
GSocketClient::~GSocketClient() {

}
//===============================================
void GSocketClient::run(int argc, char** argv) {
    GSocket lClient;
    GSocket lServer;
    lClient.ip("127.0.0.1");
    lClient.address();
    lClient.sockets2();
    lClient.binds();
    lClient.sends(lServer, "Bonjour tout le monde");
    lClient.recvs(lServer);
    lClient.print();
    lServer.ip();
    lServer.print2();
    lClient.closes();
}
//===============================================
