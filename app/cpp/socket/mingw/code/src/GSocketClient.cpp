//===============================================
#include "GSocketClient.h"
#include "GSocket.h"
//===============================================
GSocketClient::GSocketClient() {

}
//===============================================
GSocketClient::~GSocketClient() {

}
//===============================================
void GSocketClient::run(int argc, char** argv) {
    GSocket lClient;
    lClient.init();
    lClient.ip("127.0.0.1");
    lClient.address();
    lClient.sockets2();
    lClient.sends(lClient, "Bonjour tout le monde");
    lClient.recvs(lClient);
    lClient.print();
    lClient.close();
    lClient.clean();
}
//===============================================
