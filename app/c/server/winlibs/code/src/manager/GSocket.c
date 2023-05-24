//===============================================
#include "GSocket.h"
#include "GServer.h"
//===============================================
#define GSOCKET_BUFFER_SIZE 10
//===============================================
static void GSocket_delete(GSocket* _this);
static void GSocket_run(GSocket* _this, int _argc, char** _argv);
static void GSocket_callServer(GSocket* _this, const char* _dataIn, GString* _dataOut);
static void GSocket_read(GSocket* _this, GString* _data);
static void GSocket_send(GSocket* _this, const char* _data);
//===============================================
static DWORD WINAPI GSocket_onThread(LPVOID _params);
//===============================================
GSocket* GSocket_new() {
    GSocket* lObj = (GSocket*)malloc(sizeof(GSocket));
    lObj->m_parent = GObject_new();
    lObj->delete = GSocket_delete;
    lObj->run = GSocket_run;
    lObj->callServer = GSocket_callServer;
    lObj->read = GSocket_read;
    lObj->send = GSocket_send;
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
static void GSocket_callServer(GSocket* _this, const char* _dataIn, GString* _dataOut) {
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

    _this->m_socket = lClient;
    connect(lClient, (SOCKADDR*)(&lAddress), sizeof(lAddress));
    _this->send(_this, _dataIn);
    _this->read(_this, _dataOut);

    closesocket(lClient);
    WSACleanup();
}
//===============================================
static DWORD WINAPI GSocket_onThread(LPVOID _params) {
    GSocket* lClient = (GSocket*)_params;
    GServer* lServer = GServer_new();
    GString* lRequest = GString_new();

    lClient->read(lClient, lRequest);
    lServer->run(lServer, lRequest);
    lServer->send(lServer, lClient);

    closesocket(lClient->m_socket);
    lRequest->delete(lRequest);
    lServer->delete(lServer);
    lClient->delete(lClient);
    return 0;
}
//===============================================
static void GSocket_read(GSocket* _this, GString* _data) {
    assert(_this);
    SOCKET lSocket = _this->m_socket;
    while(1) {
        char lBuffer[GSOCKET_BUFFER_SIZE];
        int lBytes = recv(lSocket, lBuffer, GSOCKET_BUFFER_SIZE - 1, 0);
        if(lBytes == SOCKET_ERROR) break;
        lBuffer[lBytes] = '\0';
        _data->add(_data, lBuffer);

        u_long lBytesIO;
        int lOk = ioctlsocket(lSocket, FIONREAD, &lBytesIO);

        if(lOk == SOCKET_ERROR) break;
        if(lBytesIO <= 0) break;
    }
}
//===============================================
static void GSocket_send(GSocket* _this, const char* _data) {
    assert(_this);
    SOCKET lSocket = _this->m_socket;
    int lIndex = 0;
    const char* lBuffer = _data;
    int lSize = strlen(_data);
    while(1) {
        int lBytes = send(lSocket, &lBuffer[lIndex], lSize - lIndex, 0);
        if(lBytes == SOCKET_ERROR) break;
        lIndex += lBytes;
        if(lIndex >= lSize) break;
    }
}
//===============================================
