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
	int lPort = 8585;
	int returnStatus = 0;
	char lBuffer[256] = "";

	int lSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	struct sockaddr_in lAddress;
	bzero(&lAddress, sizeof(lAddress));
	lAddress.sin_family = AF_INET;
	inet_addr(argv[2], &lAddress.sin_addr.s_addr);
	lAddress.sin_port = htons(lPort);

	connect(lSocket, (struct sockaddr*)&lAddress, sizeof(lAddress));

	read(lSocket, lBuffer, sizeof(lBuffer));
	std::cout << lBuffer << "...\n";

	close(lSocket);
}
//===============================================
