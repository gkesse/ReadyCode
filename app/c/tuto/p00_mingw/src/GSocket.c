//===============================================
#include "GSocket.h"
//===============================================
#define GSOCKET_BUFFER_SIZE 1024
//===============================================
static void GSocket_delete(GSocket** _this);
static void GSocket_run(GSocket* _this);
static DWORD WINAPI GSocket_onThread(LPVOID _params);
static void GSocket_read(GSocket* _this);
//===============================================
GSocket* GSocket_new() {
    GSocket* lObj = (GSocket*)malloc(sizeof(GSocket));
    GSocket_init(lObj);
    return lObj;
}
//===============================================
void GSocket_init(GSocket* _this) {
    assert(_this);
    _this->delete = GSocket_delete;
    _this->run = GSocket_run;
    _this->read = GSocket_read;

    _this->m_obj = GObject_new();
}
//===============================================
static void GSocket_delete(GSocket** _this) {
    assert(*_this);
    GObject* lObj = (*_this)->m_obj;
    lObj->delete(&lObj);
    free(*_this);
    (*_this) = 0;
}
//===============================================
static void GSocket_run(GSocket* _this) {
    assert(_this);
    GLog* lLog = _this->m_obj->m_logs;

    int lMajor = 2;
    int lMinor = 2;
    int lPort = 8010;
    int lBacklog = 10;

    WSADATA wsaData;

    if(WSAStartup(MAKEWORD(lMajor, lMinor), &wsaData) == SOCKET_ERROR) {
        lLog->addError(lLog, "L'initialisation du server a échoué.");
        return;
    }

    struct sockaddr_in lAddress;
    lAddress.sin_family = AF_INET;
    lAddress.sin_addr.s_addr = INADDR_ANY;
    lAddress.sin_port = htons(lPort);

    SOCKET lServer = socket(AF_INET, SOCK_STREAM, 0);

    if(lServer == INVALID_SOCKET) {
        lLog->addError(lLog, "La création du socket server a échoué.");
        return;
    }

    if(bind(lServer, (struct sockaddr *)&lAddress, sizeof(lAddress)) == SOCKET_ERROR) {
        lLog->addError(lLog, "La liaison du socket server a échoué.");
        return;
    }

    if(listen(lServer, lBacklog) == SOCKET_ERROR) {
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
static DWORD WINAPI GSocket_onThread(LPVOID _params) {
    GSocket* lClient = (GSocket*)_params;
    printf("%s...\n", __PRETTY_FUNCTION__);
    lClient->read(lClient);
    closesocket(lClient->m_socket);
    return 0;
}
//===============================================
static void GSocket_read(GSocket* _this) {
    assert(_this);
    SOCKET lSocket = _this->m_socket;
    GString* lData = GString_new();

    while(1) {
        char lBuffer[GSOCKET_BUFFER_SIZE];
        int lBytes = recv(lSocket, lBuffer, GSOCKET_BUFFER_SIZE - 1, 0);
        if(lBytes == SOCKET_ERROR) break;
        lBuffer[lBytes] = '\0';

        lData->add(lData, lBuffer);

        u_long lBytesIO;
        int lOk = ioctlsocket(lSocket, FIONREAD, &lBytesIO);

        if(lOk == SOCKET_ERROR) break;
        if(lBytesIO <= 0) break;
    }

    lData->print(lData);
    lData->delete(&lData);
}
//===============================================
