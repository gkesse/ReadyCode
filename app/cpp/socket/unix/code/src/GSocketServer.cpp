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
    int lSocket = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in lAddress;
    bzero(&lAddress, sizeof(lAddress));
    lAddress.sin_family = AF_INET;
    lAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    lAddress.sin_port = htons(8585);
    bind(lSocket, (struct sockaddr*)&lAddress, sizeof(lAddress));
    //===============================================
    struct sockaddr_in lAddress2;
    socklen_t lAdresseSize2 = sizeof(lAddress2);
    char lBuffer[256];
    while (1) {
        recvfrom(lSocket, lBuffer, 256, 0, (struct sockaddr*)&lAddress2, &lAdresseSize2);
        printf("Received: %s\n", lBuffer);
        strcpy(lBuffer, "OK");
        sendto(lSocket, lBuffer, strlen(lBuffer), 0,(struct sockaddr*)&lAddress2, sizeof(lAddress2));
    }
    //===============================================
    close(lSocket);
}
//===============================================
