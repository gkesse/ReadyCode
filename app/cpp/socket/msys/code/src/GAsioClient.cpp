//===============================================
#include "GAsioClient.h"
#include "GAsio.h"
#include "GFile.h"
#include "GManager.h"
//===============================================
GAsioClient::GAsioClient() {

}
//===============================================
GAsioClient::~GAsioClient() {

}
//===============================================
void GAsioClient::run(int argc, char** argv) {
    GAsio lClient;
    lClient.ip("127.0.0.1");
    lClient.address();
    lClient.endpoint();
    lClient.socket();
    lClient.connect();
    lClient.send("Bonjour tout le monde");
    lClient.recv();
    lClient.print();
}
//===============================================
