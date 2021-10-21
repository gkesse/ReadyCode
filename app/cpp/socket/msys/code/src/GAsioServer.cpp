//===============================================
#include "GAsioServer.h"
#include "GFile.h"
#include "GString.h"
#include "GAsio.h"
//===============================================
GAsioServer::GAsioServer() {

}
//===============================================
GAsioServer::~GAsioServer() {

}
//===============================================
void GAsioServer::run(int argc, char** argv) {
	GAsio lServer;
	lServer.endpoint();
	lServer.acceptor();
	lServer.bind();
	lServer.listen();
	lServer.socket();
	lServer.start();
	lServer.accept();
}
//===============================================
