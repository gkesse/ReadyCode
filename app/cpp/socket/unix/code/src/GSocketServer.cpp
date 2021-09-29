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
	int lSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	struct sockaddr_in lAddress;
	bzero(&lAddress, sizeof(lSocket));
	lAddress.sin_family = AF_INET;
	lAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	lAddress.sin_port = htons(8585);
	bind(lSocket, (struct sockaddr*)&lAddress, sizeof(lAddress));
	listen(lSocket, 5);
	const char* lMessage = "Bonjour tout le monde";
	//===============================================
	while (1) {
		struct sockaddr_in lAddress2 = {0};
		int lAdresseSize2 = sizeof(lAddress2);
		int lSocket2 = accept(lSocket,(struct sockaddr *)&lAddress2, (socklen_t*)&lAdresseSize2);
		write(lSocket2, lMessage, strlen(lMessage));
		close(lSocket2);
	}
	//===============================================
	close(lSocket);
	return;
}
//===============================================
