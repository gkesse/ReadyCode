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
	char lBuffer[256];
	int lSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	struct sockaddr_in lAddress;
	bzero(&lAddress, sizeof(lAddress));
	lAddress.sin_family = AF_INET;
	lAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
	lAddress.sin_port = htons(8585);
	connect(lSocket, (struct sockaddr*)&lAddress, sizeof(lAddress));
	//===============================================
	read(lSocket, lBuffer, sizeof(lBuffer));
	std::cout << lBuffer << "...\n";
	//===============================================
	close(lSocket);
}
//===============================================
