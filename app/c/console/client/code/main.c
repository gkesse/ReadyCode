//===============================================
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <iphlpapi.h>
#include <ws2tcpip.h>
//===============================================
int main(int argc, char** argv) {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_socktype = SOCK_STREAM;

    struct addrinfo *peer_address;
    getaddrinfo("127.0.0.1", "8080", &hints, &peer_address);
    
    SOCKET socket_peer = socket(peer_address->ai_family, 
    peer_address->ai_socktype, peer_address->ai_protocol);
    connect(socket_peer, 
    peer_address->ai_addr, peer_address->ai_addrlen);
    freeaddrinfo(peer_address);
    
    char lMessage[256];
    sprintf(lMessage, "Bonjour ! C'est quoi la date ?");
    send(socket_peer, lMessage, strlen(lMessage), 0);
    printf("[client] send : %s\n", lMessage);

    int lBytes = recv(socket_peer, lMessage, sizeof(lMessage), 0);
    lMessage[lBytes] = 0;
    printf("[client] recv : %s\n", lMessage);

    closesocket(socket_peer);
    WSACleanup();
    return 0;
}
//===============================================
