//===============================================
#include "GTestNetwork.h"
#include "GLog.h"
#include "GFormat.h"
//===============================================
GTestNetwork* GTestNetwork::m_test = 0;
//===============================================
GTestNetwork::GTestNetwork() : GModule() {

}
//===============================================
GTestNetwork::~GTestNetwork() {

}
//===============================================
void GTestNetwork::run(int _argc, char** _argv) {
    std::string lKey = "default";
    if(_argc > 2) lKey = _argv[2];
    //===============================================
    // default
    //===============================================
    if(lKey == "default") {
        runTest(_argc, _argv);
    }
    //===============================================
    // simple
    //===============================================
    else if(lKey == "server/simple") {
        runServerSimple(_argc, _argv);
    }
    else if(lKey == "client/simple") {
        runClientSimple(_argc, _argv);
    }
    //===============================================
    // udp
    //===============================================
    else if(lKey == "server/udp") {
        runServerUdp(_argc, _argv);
    }
    else if(lKey == "client/udp") {
        runClientUdp(_argc, _argv);
    }
    //===============================================
    // end
    //===============================================
    else {
        runTest(_argc, _argv);
    }
}
//===============================================
void GTestNetwork::runTest(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
}
//===============================================
void GTestNetwork::runServerSimple(int _argc, char** _argv) {
    GLOGT(eGFUN, "");

    const char APRESSMESSAGE[] = "APRESS - For Professionals, By Professionals!\n";
    const int PORT = 9002;

    int simpleSocket = 0;
    int simplePort = 0;
    int returnStatus = 0;
    struct sockaddr_in simpleServer;

    simpleSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (simpleSocket == -1) {

        fprintf(stderr, "Could not create a socket!\n");
        exit(1);

    }
    else {
        fprintf(stderr, "Socket created!\n");
    }

    simplePort = PORT;

    bzero(&simpleServer, sizeof(simpleServer));
    simpleServer.sin_family = AF_INET;
    simpleServer.sin_addr.s_addr = htonl(INADDR_ANY);
    simpleServer.sin_port = htons(simplePort);

    returnStatus = bind(simpleSocket,(struct sockaddr *)&simpleServer,sizeof(simpleServer));

    if (returnStatus == 0) {
        fprintf(stderr, "Bind completed!\n");
    }
    else {
        fprintf(stderr, "Could not bind to address!\n");
        close(simpleSocket);
        exit(1);
    }

    returnStatus = listen(simpleSocket, 5);

    if (returnStatus == -1) {
        fprintf(stderr, "Cannot listen on socket!\n");
        close(simpleSocket);
        exit(1);
    }

    while (1) {
        struct sockaddr_in clientName = { 0 };
        int simpleChildSocket = 0;
        int clientNameLength = sizeof(clientName);

        simpleChildSocket = accept(simpleSocket,(struct sockaddr *)&clientName, (socklen_t*)&clientNameLength);

        if (simpleChildSocket == -1) {
            fprintf(stderr, "Cannot accept connections!\n");
            close(simpleSocket);
            exit(1);
        }

        write(simpleChildSocket, APRESSMESSAGE, strlen(APRESSMESSAGE));
        close(simpleChildSocket);
    }

    close(simpleSocket);
}
//===============================================
void GTestNetwork::runClientSimple(int _argc, char** _argv) {
    GLOGT(eGFUN, "");

    const int PORT = 9002;
    const char* ADDR = "127.0.0.1";

    int simpleSocket = 0;
    int simplePort = 0;
    int returnStatus = 0;
    char buffer[256] = "";

    struct sockaddr_in simpleServer;

    simpleSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (simpleSocket == -1) {
        fprintf(stderr, "Could not create a socket!\n");
        exit(1);
    }
    else {
        fprintf(stderr, "Socket created!\n");
    }

    simplePort = PORT;

    bzero(&simpleServer, sizeof(simpleServer));
    simpleServer.sin_family = AF_INET;
    simpleServer.sin_addr.s_addr = inet_addr(ADDR);
    simpleServer.sin_port = htons(simplePort);

    returnStatus = connect(simpleSocket, (struct sockaddr*)&simpleServer, sizeof(simpleServer));

    if (returnStatus == 0) {
        fprintf(stderr, "Connect successful!\n");
    }
    else {
        fprintf(stderr, "Could not connect to address!\n");
        close(simpleSocket);
        exit(1);
    }

    returnStatus = read(simpleSocket, buffer, sizeof(buffer));

    if ( returnStatus > 0 ) {
        printf("%d: %s", returnStatus, buffer);
    }
    else {
        fprintf(stderr, "Return Status = %d \n", returnStatus);
    }

    close(simpleSocket);
}
//===============================================
void GTestNetwork::runServerUdp(int _argc, char** _argv) {
    GLOGT(eGFUN, "");

    const int MAXBUF = 1024;
    const int PORT = 9002;

    int udpSocket;
    int returnStatus = 0;
    int addrlen = 0;
    struct sockaddr_in udpServer, udpClient;
    char buf[MAXBUF];

    udpSocket = socket(AF_INET, SOCK_DGRAM, 0);

    if (udpSocket == -1) {
        fprintf(stderr, "Could not create a socket!\n");
        exit(1);
    }
    else {
        printf("Socket created.\n");
    }

    udpServer.sin_family = AF_INET;
    udpServer.sin_addr.s_addr = htonl(INADDR_ANY);
    udpServer.sin_port = PORT;

    returnStatus = bind(udpSocket, (struct sockaddr*)&udpServer, sizeof(udpServer));

    if (returnStatus == 0) {
        fprintf(stderr, "Bind completed!\n");
    }
    else {
        fprintf(stderr, "Could not bind to address!\n");
        close(udpSocket);
        exit(1);
    }

    while(1) {
        addrlen = sizeof(udpClient);

        returnStatus = recvfrom(udpSocket, buf, MAXBUF, 0, (struct sockaddr*)&udpClient, &addrlen);

        if (returnStatus == -1) {
            fprintf(stderr, "Could not receive message!\n");
        }
        else {
            printf("Received: %s\n", buf);
            strcpy(buf, "OK");
            returnStatus = sendto(udpSocket, buf, strlen(buf)+1, 0,(struct sockaddr*)&udpClient, sizeof(udpClient));

            if (returnStatus == -1) {
                fprintf(stderr, "Could not send confirmation!\n");
            }
            else {
                printf("Confirmation sent.\n");
            }
        }

    }

    close(udpSocket);
}
//===============================================
void GTestNetwork::runClientUdp(int _argc, char** _argv) {
    GLOGT(eGFUN, "");

    const int MAXBUF = 1024;
    const int PORT = 9002;
    const char* ADDR = "127.0.0.1";

    int udpSocket;
    int returnStatus;
    int addrlen;
    struct sockaddr_in udpClient, udpServer;
    char buf[MAXBUF];

    udpSocket = socket(AF_INET, SOCK_DGRAM, 0);

    if (udpSocket == -1) {
        fprintf(stderr, "Could not create a socket!\n");
        exit(1);
    }
    else {
        printf("Socket created.\n");
    }

    udpClient.sin_family = AF_INET;
    udpClient.sin_addr.s_addr = INADDR_ANY;
    udpClient.sin_port = 0;

    returnStatus = bind(udpSocket, (struct sockaddr*)&udpClient, sizeof(udpClient));

    if (returnStatus == 0) {
        fprintf(stderr, "Bind completed!\n");
    }
    else {
        fprintf(stderr, "Could not bind to address!\n");
        close(udpSocket);
        exit(1);
    }

    strcpy(buf, "For Professionals, By Professionals.\n");

    udpServer.sin_family = AF_INET;
    udpServer.sin_addr.s_addr = inet_addr(ADDR);
    udpServer.sin_port = htons(PORT));

    returnStatus = sendto(udpSocket, buf, strlen(buf)+1, 0, (struct sockaddr*)&udpServer, sizeof(udpServer));

    if (returnStatus == -1) {
        fprintf(stderr, "Could not send message!\n");
    }
    else {
        printf("Message sent.\n");
        addrlen = sizeof(udpServer);
        returnStatus = recvfrom(udpSocket, buf, MAXBUF, 0, (struct sockaddr*)&udpServer, &addrlen);
        if (returnStatus == -1) {
            fprintf(stderr, "Did not receive confirmation!\n");
        }
        else {
            buf[returnStatus] = 0;
            printf("Received: %s\n", buf);
        }
    }

    close(udpSocket);
}
//===============================================
