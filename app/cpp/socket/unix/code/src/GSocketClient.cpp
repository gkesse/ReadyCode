//===============================================
#include "GSocketClient.h"
#include "GSocket.h"
//===============================================
#define SERVERPORT	8888
#define MAXBUF		1024
//===============================================
GSocketClient::GSocketClient() {

}
//===============================================
GSocketClient::~GSocketClient() {

}
//===============================================
void GSocketClient::run(int argc, char** argv) {
	int sockd;
	int counter;
	int fd;
	struct sockaddr_in xferServer;
	char buf[MAXBUF + 1];
	int returnStatus;

	if (argc < 3)
	{
		fprintf(stderr, "Usage: %s <ip address> <filename> [dest filename]\n", argv[0]);
		exit(1);
	}

	/* create a socket */
	sockd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockd == -1)
	{
		fprintf(stderr, "Could not create socket!\n");
		exit(1);
	}

	/* set up the server information */
	xferServer.sin_family = AF_INET;
	xferServer.sin_addr.s_addr = inet_addr("127.0.0.1");
	xferServer.sin_port = htons(SERVERPORT);

	/* connect to the server */
	returnStatus = connect(sockd, (struct sockaddr*)&xferServer, sizeof(xferServer));

	if (returnStatus == -1)
	{
		fprintf(stderr, "Could not connect to server!\n");
		exit(1);
	}

	/* send the name of the file we want to the server */
	const char* lFilename = "data/server/test.xml";
	returnStatus = write(sockd, lFilename, strlen(lFilename));

	if (returnStatus == -1)
	{
		fprintf(stderr, "Could not send filename to server!\n");
		exit(1);
	}

	/* call the shutdown to set our socket to read only */
	shutdown(sockd, SHUT_WR);

	/* open up a handle to our destination file to receive the contents */
	/* from the server   */
	fd = open("data/client/test.xml", O_WRONLY | O_CREAT | O_APPEND);

	if (fd == -1)
	{
		fprintf(stderr, "Could not open destination file, using stdout.\n");
		fd = 1;
	}

	/* read the file from the socket as long as there is data */
	while ((counter = read(sockd, buf, MAXBUF)) > 0)
	{
		/* send the contents to stdout */
		write(fd, buf, counter);
	}

	if (counter == -1)
	{
		fprintf(stderr, "Could not read file from socket!\n");
		exit(1);
	}

	close(sockd);
}
//===============================================
