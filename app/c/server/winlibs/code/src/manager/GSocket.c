//===============================================
#include "GSocket.h"
//===============================================
#define GSOCKET_BUFFER_SIZE 1024
//===============================================
static void GSocket_delete(GSocket* _this);
static void GSocket_run(GSocket* _this, int _argc, char** _argv);
static void GSocket_callServer(GSocket* _this, const char* _data);
//===============================================
static DWORD WINAPI GSocket_onThread(LPVOID _params);
//===============================================
GSocket* GSocket_new() {
    GSocket* lObj = (GSocket*)malloc(sizeof(GSocket));
    lObj->m_parent = GObject_new();
    lObj->delete = GSocket_delete;
    lObj->run = GSocket_run;
    lObj->callServer = GSocket_callServer;
    return lObj;
}
//===============================================
static void GSocket_delete(GSocket* _this) {
    assert(_this);
    _this->m_parent->delete(_this->m_parent);
    free(_this);
}
//===============================================
static void GSocket_run(GSocket* _this, int _argc, char** _argv) {
    assert(_this);
    GLog* lLog = _this->m_parent->m_logs;

    WSADATA wsaData;

    if(WSAStartup(MAKEWORD(2, 2), &wsaData) == SOCKET_ERROR) {
        lLog->addError(lLog, "L'initialisation du server a échoué.");
        return;
    }

    struct sockaddr_in lAddress;
    lAddress.sin_family = AF_INET;
    lAddress.sin_addr.s_addr = INADDR_ANY;
    lAddress.sin_port = htons(8002);

    SOCKET lServer = socket(AF_INET, SOCK_STREAM, 0);

    if(lServer == INVALID_SOCKET) {
        lLog->addError(lLog, "La création du socket server a échoué.");
        return;
    }

    if(bind(lServer, (struct sockaddr *)&lAddress, sizeof(lAddress)) == SOCKET_ERROR) {
        lLog->addError(lLog, "La liaison du socket server a échoué.");
        return;
    }

    if(listen(lServer, 10) == SOCKET_ERROR) {
        lLog->addError(lLog, "L'initialisation du nombre de connexions autorisées a échoué.");
        return;
    }

    printf("Démarrage du serveur...\n");

    struct sockaddr_in lAddressC;
    int lAddressCL = sizeof(lAddressC);

    while(1) {
        GSocket* lClient = GSocket_new();
        lClient->m_socket = accept(lServer, (struct sockaddr*)&lAddressC, &lAddressCL);

        DWORD lThreadId;
        HANDLE lThreadH = CreateThread(
                NULL,
                0,
                GSocket_onThread,
                lClient,
                0,
                &lThreadId
        );

        if(!lThreadH) {
            printf("La création du thread a échoué\n");
        }
    }

    closesocket(lServer);
    WSACleanup();
}
//===============================================
static void GSocket_callServer(GSocket* _this, const char* _data) {
    assert(_this);
    GLog* lLog = _this->m_parent->m_logs;

    WSADATA lWsaData;

    if(WSAStartup(MAKEWORD(2, 2), &lWsaData) == SOCKET_ERROR) {
        lLog->addError(lLog, "L'initialisation du server a échoué.");
        return;
    }

    struct sockaddr_in lAddress;

    InetPton(AF_INET, "127.0.0.1", &lAddress.sin_addr.s_addr);
    lAddress.sin_family = AF_INET;
    lAddress.sin_port = htons(8002);

    SOCKET lClient = socket(AF_INET, SOCK_STREAM, 0);

    if(lClient == INVALID_SOCKET) {
        lLog->addError(lLog, "La création du socket server a échoué.");
        return;
    }

    connect(lClient, (SOCKADDR*)(&lAddress), sizeof(lAddress));
    send(lClient, _data, strlen(_data), 0);
    char lBuffer[GSOCKET_BUFFER_SIZE];
    int lBytes = recv(lClient, lBuffer, GSOCKET_BUFFER_SIZE - 1, 0);
    lBuffer[lBytes] = '\0';
    printf("%s\n", lBuffer);

    closesocket(lClient);
    WSACleanup();
}
//===============================================
static DWORD WINAPI GSocket_onThread(LPVOID _params) {
    GSocket* lSocket = (GSocket*)_params;
    SOCKET lClient = lSocket->m_socket;

    char lBuffer[GSOCKET_BUFFER_SIZE];
    int lBytes = recv(lClient, lBuffer, GSOCKET_BUFFER_SIZE - 1, 0);
    lBuffer[lBytes] = '\0';
    printf("%s\n", lBuffer);
    const char* lResponse = "Très OK.";
    send(lClient, lResponse, strlen(lResponse), 0);

    closesocket(lClient);
    return 0;
}
//===============================================
