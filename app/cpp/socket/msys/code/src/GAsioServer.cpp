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
    lServer.address();
    lServer.endpoint();
    lServer.acceptor();
    lServer.start();
    while(1) {
        lServer.socket();
        lServer.accept();
        lServer.thread(onThread, lServer.socket2());
    }
}
//===============================================
void GAsioServer::onThread(boost::shared_ptr<boost::asio::ip::tcp::socket> _socket) {
	GAsio lServer;
	lServer.socket(_socket);
	lServer.recv();
	lServer.send("ok");
	lServer.print();
}
//===============================================
