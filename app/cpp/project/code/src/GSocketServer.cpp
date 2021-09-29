//===============================================
#include "GSocketServer.h"
#include "GSocket.h"
#include "GManager.h"
//===============================================
GSocketServer::GSocketServer(QObject* parent) :
GSocketUi(parent) {

}
//===============================================
GSocketServer::~GSocketServer() {

}
//===============================================
void GSocketServer::run(int argc, char** argv) {
	GSocket* lSocket = new GSocket;
	lSocket->startServer();
	delete lSocket;
}
//===============================================
