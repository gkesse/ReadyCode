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
    GSocket lSocket;
    GSocket lClient;
	lSocket.init();
	lSocket.address();
	lSocket.sockets();
	lSocket.binds();
	lSocket.listens();
	lSocket.accepts(lClient);
	lSocket.recvs();
	lClient.print();
	lClient.close();
	lSocket.close();
	lSocket.close();
}
//===============================================
