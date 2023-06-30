//===============================================
#include "GSocket.h"
#include "GServer.h"
#include "GCode.h"
//===============================================
GSocket::GSocket()
: GObject() {
    m_socket = SOCKET_ERROR;
}
//===============================================
GSocket::~GSocket() {

}
//===============================================
GLog& GSocket::getSrvLogs() {
    return m_srvLogs;
}
//===============================================
void GSocket::runServer() {
    int lMajor = 2;
    int lMinor = 2;
    int lPort = 9010;
    int lBacklog = 10;

    WSADATA wsaData;

    if(WSAStartup(MAKEWORD(lMajor, lMinor), &wsaData) == SOCKET_ERROR) {
        m_logs.addError("L'initialisation du socket a échoué.");
        return;
    }

    struct sockaddr_in lAddress;
    lAddress.sin_family = AF_INET;
    lAddress.sin_addr.s_addr = INADDR_ANY;
    lAddress.sin_port = htons(lPort);

    SOCKET lServer = socket(AF_INET, SOCK_STREAM, 0);

    if(lServer == INVALID_SOCKET) {
        m_logs.addError("La création du socket a échoué.");
        return;
    }

    if(bind(lServer, (struct sockaddr *)&lAddress, sizeof(lAddress)) == SOCKET_ERROR) {
        m_logs.addError("La liaison du socket server a échoué.");
        return;
    }

    if(listen(lServer, lBacklog) == SOCKET_ERROR) {
        m_logs.addError("L'initialisation du nombre de connexions à écouter a échoué.");
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
            m_logs.addError("La création du thread a échoué.");
            break;
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
GString GSocket::toHostname(const GString& _facade) const {
    if(_facade == "server_c") return "127.0.0.1";
    if(_facade == "server_cpp") return "127.0.0.1";
    if(_facade == "server_python") return "127.0.0.1";
    if(_facade == "server_java") return "127.0.0.1";
    return "127.0.0.1";
}
//===============================================
int GSocket::toPort(const GString& _facade) const {
    if(_facade == "server_c") return 9020;
    if(_facade == "server_cpp") return 9010;
    if(_facade == "server_python") return 9030;
    if(_facade == "server_java") return 9040;
    return 9010;
}
//===============================================
GString GSocket::callServer(const GString& _dataIn, const GString& _facade) {
    int lMajor = 2;
    int lMinor = 2;
    GString lHostname = toHostname(_facade);
    int lPort = toPort(_facade);

    WSADATA lWsaData;

    if(WSAStartup(MAKEWORD(lMajor, lMinor), &lWsaData) == SOCKET_ERROR) {
        m_logs.addError("La connexion au server a échoué.");
        return "";
    }

    struct sockaddr_in lAddress;

    inet_pton(AF_INET, lHostname.c_str(), &lAddress.sin_addr.s_addr);
    lAddress.sin_family = AF_INET;
    lAddress.sin_port = htons(lPort);

    SOCKET lClient = socket(AF_INET, SOCK_STREAM, 0);

    if(lClient == INVALID_SOCKET) {
        m_logs.addError("La connexion au server a échoué.");
        return "";
    }

    m_socket = lClient;
    int lConnectOk = connect(lClient, (SOCKADDR*)(&lAddress), sizeof(lAddress));

    if(lConnectOk == SOCKET_ERROR) {
        m_logs.addError("La connexion au server a échoué.");
        return "";
    }

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

        if(lData.size() >= BUFFER_MAX) {
            m_srvLogs.addError("La taille maximale des données est atteinte.");
            break;
        }

        u_long lBytesIO;
        int lOk = ioctlsocket(m_socket, FIONREAD, &lBytesIO);

        if(lOk == SOCKET_ERROR) break;
        if(lBytesIO <= 0) break;
    }
    return lData;
}
//===============================================
