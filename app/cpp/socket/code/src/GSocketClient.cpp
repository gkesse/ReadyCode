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
	char str[INET_ADDRSTRLEN];


	//Initialize Winsock
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != NO_ERROR) {
		std::cout << "WSAStartup Failed with error: " << iResult << std::endl;
		return;
	}

	SOCKET UDPSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (UDPSocket == INVALID_SOCKET) {
		std::cout << "Error at socket(): " << WSAGetLastError() << std::endl;
		WSACleanup();
		return;
	}

	// The sockaddr_in structure specifies the address family,
	// IP address, and port for the socket that is being bound.
	sockaddr_in addrServer;
	addrServer.sin_family = AF_INET;
	InetPton(AF_INET, "127.0.0.1", &addrServer.sin_addr.s_addr);
	//InetPton(AF_INET, "192.168.0.20", &addrServer.sin_addr.s_addr);
	addrServer.sin_port = htons(8585);
	memset(&(addrServer.sin_zero), '\0', 8);



	//variables
	const int DEFAULT_BUFLEN = 256;
	char filename[DEFAULT_BUFLEN] = { 0 };
	std::cout << "Name of file: ";
	std::cin.getline(filename, DEFAULT_BUFLEN, '\n');
	//std::cout << filename << std::endl;

	const char *sendbuf = filename;

	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;


	//std::cout << "Array lenght:" << (int)strlen(sendbuf) << std::endl;
	int srvAddrLen = sizeof(addrServer);

	// Send file name
	inet_ntop(AF_INET, &addrServer.sin_addr, str, INET_ADDRSTRLEN);
	std::cout << "Sending name to: " << str << std::endl;


	int count = strlen(filename);
	sendto(UDPSocket, filename, count, 0, (struct sockaddr *)&addrServer, srvAddrLen);


	int c = recvfrom(UDPSocket, recvbuf, DEFAULT_BUFLEN, 0, (struct sockaddr *)&addrServer, &srvAddrLen);
	//std::cout << recvbuf << std::endl;


	inet_ntop(AF_INET, &addrServer.sin_addr, str, INET_ADDRSTRLEN);
	std::cout << "Recieved size from: " << str << std::endl;

	std::string size;
	for (int i = 0; i < c; i++) size += recvbuf[i];
	if (size == "-1") std::cout << "No file named \"" << filename << "\"" << std::endl;
	else std::cout << "The size of file \"" << filename << "\" is: " << size << std::endl;


	// cleanup
	closesocket(UDPSocket);
	WSACleanup();
}
//===============================================
