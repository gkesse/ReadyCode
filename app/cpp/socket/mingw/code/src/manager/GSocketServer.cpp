//===============================================
#include "GSocketServer.h"
#include "GFile.h"
#include "GString.h"
#include "GSocket.h"
#include "GThread.h"
//===============================================
GSocketServer::GSocketServer() {

}
//===============================================
GSocketServer::~GSocketServer() {

}
//===============================================
void GSocketServer::run(int argc, char** argv) {
    GSocket lServer;
    sGSocket lParams;
    GThread lThread;
    lParams.on_start = (void*)onStart;
    lServer.start(lParams);
}
//===============================================
DWORD WINAPI GSocketServer::onStart(LPVOID _params) {
    sGSocket* lSocket = (sGSocket*)_params;
    GSocket* lClient = lSocket->socket;
    std::string lData;

    lClient->recvs(lData);
    lClient->shutdownRD();
    lClient->sends("OK");

    printf("Client IP....: %s\n", lSocket->client_ip.c_str());
    printf("Data.........: %s\n", lData.c_str());

    lClient->close();
    delete lClient;
    return 0;
}
//===============================================
