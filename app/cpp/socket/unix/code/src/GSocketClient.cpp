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
	int lSocket = socket(AF_INET, SOCK_DGRAM, 0);
	struct sockaddr_in lAddress;
	bzero(&lAddress, sizeof(lAddress));
	lAddress.sin_family = AF_INET;
	lAddress.sin_addr.s_addr = INADDR_ANY;
	lAddress.sin_port = 0;
	bind(lSocket, (struct sockaddr*)&lAddress, sizeof(lAddress));
	struct sockaddr_in lAddress2;
	bzero(&lAddress2, sizeof(lAddress2));
	lAddress2.sin_family = AF_INET;
	lAddress2.sin_addr.s_addr = inet_addr("127.0.0.1");
	lAddress2.sin_port = htons(8585);
	socklen_t lAdresseSize2 = sizeof(lAddress2);
	//===============================================
	char lBuffer[256];
	strcpy(lBuffer, "Bonjour tout le monde");
	sendto(lSocket, lBuffer, strlen(lBuffer), 0, (struct sockaddr*)&lAddress2, sizeof(lAddress2));
	recvfrom(lSocket, lBuffer, 256, 0, (struct sockaddr*)&lAddress2, &lAdresseSize2);
	printf("Received: %s\n", lBuffer);
	//===============================================
	close(lSocket);
}
//===============================================
