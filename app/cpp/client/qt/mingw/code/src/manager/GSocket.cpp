//===============================================
#include "GSocket.h"
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
int GSocket::toPort() const {
    GString lEnv = getEnv("GPROJECT_ENV");
    if(lEnv == "TEST") return 9011;
    return 9010;
}
//===============================================
void GSocket::checkErrors(GString& _data) {
    if(m_dataLogs.hasErrors()) {
        m_logs.addError("Le serveur n'est pas disponible.");
    }
    else if(!_data.isEmpty()) {
        GCode lDom;
        if(!lDom.loadXml(_data)) {
            m_logs.addErrorSrv("Le serveur n'est pas disponible.");
            _data = "";
        }
    }
}
//===============================================
GString GSocket::callServer(const GString& _dataIn) {
    GString lData = callSocket(_dataIn);
    checkErrors(lData);
    return lData;
}
//===============================================
GString GSocket::callSocket(const GString& _dataIn) {
    int lMajor = 2;
    int lMinor = 2;
    GString lHostname = "readydev.ovh";
    int lPort = toPort();
    GString lMode = "dns";

    WSADATA lWsaData;

    if(WSAStartup(MAKEWORD(lMajor, lMinor), &lWsaData) == SOCKET_ERROR) {
        m_dataLogs.addError("Les données socket ne sont pas initialisées.");
        return "";
    }

    SOCKET lClient = socket(AF_INET, SOCK_STREAM, 0);

    if(lClient == INVALID_SOCKET) {
        m_dataLogs.addError("Le socket n'est pas initialisé.");
        return "";
    }

    if(lMode == "dns") {
        struct addrinfo lHint = {0};
        lHint.ai_flags = AI_NUMERICHOST;
        lHint.ai_family = AF_UNSPEC;
        lHint.ai_socktype = SOCK_STREAM;
        lHint.ai_protocol = IPPROTO_TCP;

        struct addrinfo* lAddrs = NULL;
        int lAddrsOk = getaddrinfo(lHostname.c_str(), NULL, &lHint, &lAddrs);
        if(lAddrsOk == EAI_NONAME) {
            lHint.ai_flags = 0;
            lAddrsOk = getaddrinfo(lHostname.c_str(), NULL, &lHint, &lAddrs);

            if(lAddrsOk == SOCKET_ERROR) {
                m_dataLogs.addError("Le nom de domaine n'est pas traité.");
                return "";
            }

            lHostname = inet_ntoa(((sockaddr_in *)lAddrs->ai_addr)->sin_addr);
        }
        else {
            m_dataLogs.addError("Le nom de domaine n'est pas traité.");
            return "";
        }
    }

    SOCKADDR_IN lAddress;
    lAddress.sin_family = AF_INET;
    lAddress.sin_addr.s_addr = inet_addr(lHostname.c_str());
    lAddress.sin_port = htons(lPort);
    memset(&lAddress.sin_zero, 0, sizeof(lAddress.sin_zero));

    m_socket = lClient;
    int lConnectOk = connect(lClient, (SOCKADDR*)(&lAddress), sizeof(lAddress));

    if(lConnectOk == SOCKET_ERROR) {
        m_dataLogs.addError("La connexion du socket a échoué.");
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
    GString lData = callServer(lDom.toString());
    return lData;
}
//===============================================
void GSocket::sendData(const GString& _data) {
    int lIndex = 0;
    const char* lBuffer = _data.c_str();
    int lSize = _data.size();
    while(1) {
        int lBytes = send(m_socket, &lBuffer[lIndex], lSize - lIndex, 0);
        if(lBytes == SOCKET_ERROR) {
            m_dataLogs.addError("L'émission des données a échoué.");
            break;
        }
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
        if(lBytes == SOCKET_ERROR) {
            m_dataLogs.addError("La réception des données a échoué.");
            break;
        }
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
