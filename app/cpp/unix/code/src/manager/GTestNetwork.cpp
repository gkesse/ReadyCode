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

    /* retrieve the port number for listening */
    simplePort = PORT;

    /* setup the address structure */
    /* use INADDR_ANY to bind to all local addresses  */
    bzero(&simpleServer, sizeof(simpleServer));
    simpleServer.sin_family = AF_INET;
    simpleServer.sin_addr.s_addr = htonl(INADDR_ANY);
    simpleServer.sin_port = htons(simplePort);

    /*  bind to the address and port with our socket  */
    returnStatus = bind(simpleSocket,(struct sockaddr *)&simpleServer,sizeof(simpleServer));

    if (returnStatus == 0) {
        fprintf(stderr, "Bind completed!\n");
    }
    else {
        fprintf(stderr, "Could not bind to address!\n");
        close(simpleSocket);
        exit(1);
    }

    /* lets listen on the socket for connections      */
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

        /* wait here */

        simpleChildSocket = accept(simpleSocket,(struct sockaddr *)&clientName, &clientNameLength);

        if (simpleChildSocket == -1) {

            fprintf(stderr, "Cannot accept connections!\n");
            close(simpleSocket);
            exit(1);

        }

        /* handle the new connection request  */
        /* write out our message to the client */
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

    /* create a streaming socket      */
    simpleSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (simpleSocket == -1) {
        fprintf(stderr, "Could not create a socket!\n");
        exit(1);
    }
    else {
        fprintf(stderr, "Socket created!\n");
    }

    /* retrieve the port number for connecting */
    simplePort = PORT;

    /* setup the address structure */
    /* use the IP address sent as an argument for the server address  */
    bzero(&simpleServer, sizeof(simpleServer));
    simpleServer.sin_family = AF_INET;
    inet_addr(ADDR, &simpleServer.sin_addr.s_addr);
    simpleServer.sin_port = htons(simplePort);

    /*  connect to the address and port with our socket  */
    returnStatus = connect(simpleSocket, (struct sockaddr *)&simpleServer, sizeof(simpleServer));

    if (returnStatus == 0) {
        fprintf(stderr, "Connect successful!\n");
    }
    else {
        fprintf(stderr, "Could not connect to address!\n");
        close(simpleSocket);
        exit(1);
    }

    /* get the message from the server   */
    returnStatus = read(simpleSocket, buffer, sizeof(buffer));

    if ( returnStatus > 0 ) {
        printf("%d: %s", returnStatus, buffer);
    } else {
        fprintf(stderr, "Return Status = %d \n", returnStatus);
    }

    close(simpleSocket);
}
//===============================================
