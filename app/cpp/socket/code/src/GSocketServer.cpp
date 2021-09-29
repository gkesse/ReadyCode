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
	char str[INET_ADDRSTRLEN];

	//Initialize Winsock
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != NO_ERROR) {
		std::cout << "WSAStartup failed with error: " << iResult << std::endl;
		return;
	}


	//Create a SOCKET for listening for incoming connections request
	SOCKET SrvSocket;
	SrvSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (SrvSocket == INVALID_SOCKET) {
		std::cout << "Socket failed with error: " << WSAGetLastError() << std::endl;
		WSACleanup();
		return;
	}


	//The sockaddr_in structure specifies the address family,
	//IP address, and port for the socket that is being bound
	sockaddr_in addrServer;
	addrServer.sin_family = AF_INET;
	InetPton(AF_INET, "127.0.0.1", &addrServer.sin_addr.s_addr);
	//InetPton(AF_INET, "192.168.0.20", &addrServer.sin_addr.s_addr);
	addrServer.sin_port = htons(6666);
	memset(&(addrServer.sin_zero), '\0', 8);

	//Bind socket
	if (bind(SrvSocket, (SOCKADDR *)& addrServer, sizeof(addrServer)) == SOCKET_ERROR) {
		std::cout << "Bind failed with error: " << WSAGetLastError() << std::endl;
		closesocket(SrvSocket);
		WSACleanup();
		return;
	}



	//Variables for recieve
	const int DEFAULT_BUFLEN = 256;
	int iSendResult;
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;



	struct sockaddr_in cliAddr;
	int cliAddrLen = sizeof(cliAddr);
	int count = recvfrom(SrvSocket, recvbuf, DEFAULT_BUFLEN, 0, (struct sockaddr *)&cliAddr, &cliAddrLen);


	inet_ntop(AF_INET, &cliAddr.sin_addr, str, INET_ADDRSTRLEN);
	std::cout << "Recieved name from: " << str << std::endl;
	//std::cout << "Recieved: " << recvbuf << std::endl;


	//Create string
	std::string filename;
	//std::cout << filename << std::endl;
	for (int i = 0; i < count; i++) filename += recvbuf[i];
	//std::cout << "Opening file: " << filename << std::endl;


	//Open file and count bytes
	std::fstream file;
	file.open(filename, std::ios::in | std::ios::binary);

	file.seekg(0, std::ios::end);
	int fileSize = file.tellg();
	file.close();
	std::cout << "File \"" << filename << "\" size: " << fileSize << std::endl;


	//Convert to char array
	std::string temp = std::to_string(fileSize);
	//std::cout << "Filesize in string: " << temp << std::endl;
	char tempc[DEFAULT_BUFLEN];
	int i = 0;
	while (temp[i] != '\0') {
		tempc[i] = temp[i];
		i++;
	}
	tempc[i] = '\0';
	//std::cout << "Filesize in char array: " << tempc << std::endl;
	const char* sendbuf = tempc;


	inet_ntop(AF_INET, &cliAddr.sin_addr, str, INET_ADDRSTRLEN);
	std::cout << "Sending size to: " << str << std::endl;

	int c = strlen(sendbuf);
	sendto(SrvSocket, sendbuf, c, 0, (struct sockaddr *)&cliAddr, cliAddrLen);

	// cleanup
	closesocket(SrvSocket);
	WSACleanup();

}
//===============================================
