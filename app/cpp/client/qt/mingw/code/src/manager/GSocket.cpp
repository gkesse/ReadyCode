//===============================================
#include "GSocket.h"
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
GString GSocket::callServer(const GString& _dataIn) {
    int lMajor = 2;
    int lMinor = 2;
    const char* lHostname = "127.0.0.1";
    int lPort = 8002;

    WSADATA lWsaData;

    if(WSAStartup(MAKEWORD(lMajor, lMinor), &lWsaData) == SOCKET_ERROR) {
        m_logs.addError("La connexion au serveur a échoué.");
        return "";
    }

    struct sockaddr_in lAddress;

    inet_pton(AF_INET, lHostname, &lAddress.sin_addr.s_addr);
    lAddress.sin_family = AF_INET;
    lAddress.sin_port = htons(lPort);

    SOCKET lClient = socket(AF_INET, SOCK_STREAM, 0);

    if(lClient == INVALID_SOCKET) {
        m_logs.addError("La connexion au serveur a échoué.");
        return "";
    }

    m_socket = lClient;
    int lConnectOk = connect(lClient, (SOCKADDR*)(&lAddress), sizeof(lAddress));

    if(lConnectOk == SOCKET_ERROR) {
        m_logs.addError("La connexion au serveur a échoué.");
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

        u_long lBytesIO;
        int lOk = ioctlsocket(m_socket, FIONREAD, &lBytesIO);

        if(lOk == SOCKET_ERROR) break;
        if(lBytesIO <= 0) break;
    }
    return lData;
}
//===============================================
