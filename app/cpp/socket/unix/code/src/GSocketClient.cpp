//===============================================
#include "GSocketClient.h"
#include "GSocket.h"
#include "GFile2.h"
#include "GString.h"
//===============================================
GSocketClient::GSocketClient() {

}
//===============================================
GSocketClient::~GSocketClient() {

}
//===============================================
void GSocketClient::run(int argc, char** argv) {
	const int BUFFER_SIZE = 1024;
	char lBuffer[BUFFER_SIZE + 1];
	const char* lFilename = "data/server/test.xml";

	int lSocket = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in lAddress;
	bzero(&lAddress, sizeof(lAddress));
	lAddress.sin_family = AF_INET;
	lAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
	lAddress.sin_port = htons(8585);
	connect(lSocket, (struct sockaddr*)&lAddress, sizeof(lAddress));
	write(lSocket, lFilename, strlen(lFilename));
	shutdown(lSocket, SHUT_WR);
	GString lData;

	while(1) {
		int lBytes = read(lSocket, lBuffer, BUFFER_SIZE);
		if(lBytes <= 0) {break;}
		lData.addData(lBuffer, lBytes);
	}

	GFile2 lFile;
	lFile.setFilename("data/client/test.xml");
	lFile.openFile();
	lFile.writeData(lData);

	close(lSocket);
}
//===============================================
