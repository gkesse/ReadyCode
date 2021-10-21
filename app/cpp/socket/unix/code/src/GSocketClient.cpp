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
    lClient.ip("127.0.0.1");
    lClient.address();
    lClient.sockets();
    lClient.connects();
    lClient.sends("Bonjour tout le monde");
    lClient.recvs();
    lClient.print();
    lClient.closes();
}
//===============================================
