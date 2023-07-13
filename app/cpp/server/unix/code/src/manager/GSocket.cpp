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
    if(_facade == "server_cpp") return toPortCpp();
    if(_facade == "server_python") return 9030;
    if(_facade == "server_java") return 9040;
    return 9010;
}
//===============================================
int GSocket::toPortCpp() const {
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
            m_logs.addError("Le serveur n'est pas disponible.");
            _data = "";
        }
    }
}
//===============================================
void GSocket::runServer() {
    int lPort = toPortCpp();
    int lBacklog = 10;
    GString lHostname = "0.0.0.0";


    int lServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if(lServer == -1) {
        m_logs.addError("La création du socket a échoué.");
        return;
    }

    struct sockaddr_in lAddress;
    bzero(&lAddress, sizeof(lAddress));
    lAddress.sin_family = AF_INET;
    lAddress.sin_addr.s_addr = inet_addr(lHostname.c_str());
    lAddress.sin_port = htons(lPort);

    int lBindOk = bind(lServer, (struct sockaddr*)&lAddress, sizeof(lAddress));

    if(lBindOk == -1) {
        m_logs.addError("La liaison du socket server a échoué.");
        return;
    }

    int lListenOk = listen(lServer, lBacklog);

    if(lListenOk == -1) {
        m_logs.addError("L'initialisation du nombre de connexions à écouter a échoué.");
        return;
    }

    printf("Démarrage du serveur...\n");

    struct sockaddr_in lAddressC;
    socklen_t lAddressCL = sizeof(lAddressC);

    while(1) {
        GSocket* lClient = new GSocket;
        lClient->m_socket = accept(lServer, (struct sockaddr*)&lAddressC, &lAddressCL);

        pthread_t lThreadH;
        int lOk = pthread_create(&lThreadH, 0, onThreadCB, lClient);

        if(lOk == -1) {
            m_logs.addError("La création du thread a échoué.");
            break;
        }
    }

    close(lServer);
}
//===============================================
void* GSocket::onThreadCB(void* _params) {
    GSocket* lClient = (GSocket*)_params;
    GString lData = lClient->readData();
    GServer lServer;
    lServer.run(lData);
    lServer.sendResponse(lClient);
    close(lClient->m_socket);
    delete lClient;
    return 0;
}
//===============================================
GString GSocket::callSocket(const GString& _dataIn, const GString& _facade) {
    GString lHostname = toHostname(_facade);
    int lPort = toPort(_facade);

    int lClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if(lClient == -1) {
        m_dataLogs.addError("La création du socket a échoué.");
        return "";
    }

    struct sockaddr_in lAddress;
    bzero(&lAddress, sizeof(lAddress));
    lAddress.sin_family = AF_INET;
    lAddress.sin_addr.s_addr = inet_addr(lHostname.c_str());
    lAddress.sin_port = htons(lPort);

    m_socket = lClient;
    int lConnectOk = connect(lClient, (sockaddr*)&lAddress, sizeof(lAddress));

    if(lConnectOk == -1) {
        m_dataLogs.addError("La connexion du socket a échoué.");
        return "";
    }

    sendData(_dataIn);
    GString lDataOut = readData();

    close(lClient);
    return lDataOut;
}
//===============================================
GString GSocket::callServer(const GString& _dataIn, const GString& _facade) {
    GString lData = callSocket(_dataIn, _facade);
    checkErrors(lData);
    return lData;
}
//===============================================
GString GSocket::callFacade(const GString& _module, const GString& _method, const GString& _data) {
    GCode lDom;
    lDom.createDoc();
    lDom.addData("manager", "module", _module);
    lDom.addData("manager", "method", _method);
    lDom.loadData(_data);
    GString lData = callSocket(lDom.toString());
    checkErrors(lData);
    return lData;
}
//===============================================
void GSocket::sendData(const GString& _data) {
    int lIndex = 0;
    const char* lBuffer = _data.c_str();
    int lSize = _data.size();
    while(1) {
        int lBytes = send(m_socket, &lBuffer[lIndex], lSize - lIndex, 0);
        if(lBytes == -1) break;
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
        if(lBytes == -1) break;
        lBuffer[lBytes] = '\0';
        lData += lBuffer;

        if(lData.size() >= BUFFER_MAX) {
            m_dataLogs.addError("La taille maximale des données est atteinte.");
            break;
        }

        int lIoctlOk = ioctl(m_socket, FIONREAD, &lBytes);
        if(lIoctlOk == -1) break;
        if(lBytes <= 0) break;
    }
    return lData;
}
//===============================================
