//===============================================
#include "GSocket.h"
#include "GServer.h"
#include "GCode.h"
//===============================================
GSocket::GSocket()
: GObject() {
    m_socket = -1;
}
//===============================================
GSocket::~GSocket() {

}
//===============================================
void GSocket::runServer() {
    int lMajor = 2;
    int lMinor = 2;
    int lPort = 8002;
    int lBacklog = 10;

    WSADATA wsaData;

    if(WSAStartup(MAKEWORD(lMajor, lMinor), &wsaData) == SOCKET_ERROR) {
        m_logs.addError("L'initialisation du server a échoué.");
        return;
    }

    struct sockaddr_in lAddress;
    lAddress.sin_family = AF_INET;
    lAddress.sin_addr.s_addr = INADDR_ANY;
    lAddress.sin_port = htons(lPort);

    SOCKET lServer = socket(AF_INET, SOCK_STREAM, 0);

    if(lServer == INVALID_SOCKET) {
        m_logs.addError("La création du socket server a échoué.");
        return;
    }

    if(bind(lServer, (struct sockaddr *)&lAddress, sizeof(lAddress)) == SOCKET_ERROR) {
        m_logs.addError("La liaison du socket server a échoué.");
        return;
    }

    if(listen(lServer, lBacklog) == SOCKET_ERROR) {
        m_logs.addError("L'initialisation du nombre de connexions autorisées a échoué.");
        return;
    }

    printf("Démarrage du serveur...\n");

    struct sockaddr_in lAddressC;
    int lAddressCL = sizeof(lAddressC);

    while(1) {
        GSocket* lClient = new GSocket;
        lClient->m_socket = accept(lServer, (struct sockaddr*)&lAddressC, &lAddressCL);

        DWORD lThreadId;
        HANDLE lThreadH = CreateThread(
                NULL,
                0,
                onThread,
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
DWORD WINAPI GSocket::onThread(LPVOID _params) {
    GSocket* lClient = (GSocket*)_params;
    GString lData = lClient->readData();
    GServer lServer;
    lServer.run(lData);
    lServer.sendResponse(lClient);
    closesocket(lClient->m_socket);
    delete lClient;
    return 0;
}
//===============================================
GString GSocket::callServer(const GString& _dataIn) {
    int lMajor = 2;
    int lMinor = 2;
    const char* lHostname = "127.0.0.1";
    int lPort = 8002;

    WSADATA lWsaData;

    if(WSAStartup(MAKEWORD(lMajor, lMinor), &lWsaData) == SOCKET_ERROR) {
        m_logs.addError("L'initialisation du server a échoué.");
        return "";
    }

    struct sockaddr_in lAddress;

    InetPton(AF_INET, lHostname, &lAddress.sin_addr.s_addr);
    lAddress.sin_family = AF_INET;
    lAddress.sin_port = htons(lPort);

    SOCKET lClient = socket(AF_INET, SOCK_STREAM, 0);

    if(lClient == INVALID_SOCKET) {
        m_logs.addError("La création du socket server a échoué.");
        return "";
    }

    m_socket = lClient;
    connect(lClient, (SOCKADDR*)(&lAddress), sizeof(lAddress));
    sendData(_dataIn);
    GString lDataOut = readData();

    closesocket(lClient);
    WSACleanup();
    return lDataOut;
}
//===============================================
GString GSocket::callFacade(const GString& _module, const GString& _method, const GString& _data) {
    GCode lDom;
    lDom.createDoc();
    lDom.addData("manager", "module", _module);
    lDom.addData("manager", "method", _method);
    lDom.loadData(_data);
    return callServer(lDom.toString());
}
//===============================================
void GSocket::sendData(const GString& _data) {
    int lIndex = 0;
    const char* lBuffer = _data.c_str();
    int lSize = _data.size();
    while(1) {
        int lBytes = send(m_socket, &lBuffer[lIndex], lSize - lIndex, 0);
        if(lBytes == SOCKET_ERROR) break;
        lIndex += lBytes;
        if(lIndex >= lSize) break;
    }
}
//===============================================
GString GSocket::readData() {
    GString lData = "";
    while(1) {
        char lBuffer[BUFFER_SIZE];
        int lBytes = recv(m_socket, lBuffer, BUFFER_SIZE - 1, 0);
        if(lBytes == SOCKET_ERROR) break;
        lBuffer[lBytes] = '\0';
        lData += lBuffer;

        u_long lBytesIO;
        int lOk = ioctlsocket(m_socket, FIONREAD, &lBytesIO);

        if(lOk == SOCKET_ERROR) break;
        if(lBytesIO <= 0) break;
    }
    return lData;
}
//===============================================
