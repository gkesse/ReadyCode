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
	GSocket lSocket;
	lSocket.init();
	lSocket.ip("127.0.0.1");
	lSocket.address();
	lSocket.sockets();
	lSocket.connects();
	lSocket.sends("Bonjour tout le monde");
    lSocket.close();
}
//===============================================
