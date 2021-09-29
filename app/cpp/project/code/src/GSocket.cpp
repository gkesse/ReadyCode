//===============================================
#include "GSocket.h"
#include "GManager.h"
//===============================================
GSocket::GSocket() {

}
//===============================================
GSocket::~GSocket() {

}
//===============================================
void GSocket::startServer() {
	WSADATA lWSADATA;
	int lWSAStartup = WSAStartup(MAKEWORD(2, 2), &lWSADATA);
	if(lWSADATA != NO_ERROR) {
		printf("[error] L'initialisation du socket a echoue\n");
		return;
	}
	SOCKET lSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (lSocket == INVALID_SOCKET) {
		printf("[error] La creation du socket a echoue : %d\n", WSAGetLastError());
		WSACleanup();
		return;
	}
}
//===============================================
