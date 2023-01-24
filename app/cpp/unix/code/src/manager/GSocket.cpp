//===============================================
#include "GSocket.h"
#include "GThread.h"
#include "GHttp.h"
//===============================================
const char* GSocket::METHOD_HTTP_GET = "GET";
const char* GSocket::METHOD_HTTP_POST = "POST";
const char* GSocket::METHOD_RDVAPP = "RDVAPP";
//===============================================
GSocket::GSocket()
: GObject() {
    m_port = 0;
    m_backlog = 0;
    m_socket = 0;
    m_isTestEnv = false;
}
//===============================================
GSocket::~GSocket() {

}
//===============================================
void GSocket::setModule(const GString& _module) {
    m_module = _module;
}
//===============================================
void GSocket::setHostname(const GString& _hostname) {
    m_hostname = _hostname;
}
//===============================================
void GSocket::setPort(int _port) {
    m_port = _port;
}
//===============================================
void GSocket::setBacklog(int _backlog) {
    m_backlog = _backlog;
}
//===============================================
void GSocket::setStartMessage(const GString& _startMessage) {
    m_startMessage = _startMessage;
}
//===============================================
void GSocket::setStopMessage(const GString& _stopMessage) {
    m_stopMessage = _stopMessage;
}
//===============================================
int GSocket::getSocket() const {
    return m_socket;
}
//===============================================
bool GSocket::createSocketX() {
    if(m_hostname.isEmpty()) {
        m_logs.addError("Erreur l'adresse n'est pas initialisée.");
        return false;
    }
    if(!m_port) {
        m_logs.addError("Erreur le port n'est pas initialisé.");
        return false;
    }
    if(!m_backlog) {
        m_logs.addError("Erreur le backlog n'est pas initialisé.");
        return false;
    }

    m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(m_socket == -1) {
        m_logs.addError(GFORMAT("Erreur lors de l'initialisation du socket.\n[%d]:%s", errno, strerror(errno)));
        return false;
    }

    struct sockaddr_in lAddressIn;
    bzero(&lAddressIn, sizeof(lAddressIn));
    lAddressIn.sin_family = AF_INET;
    lAddressIn.sin_addr.s_addr = inet_addr(m_hostname.c_str());
    lAddressIn.sin_port = htons(m_port);

    int lBindOk = bind(m_socket, (struct sockaddr*)&lAddressIn, sizeof(lAddressIn));
    if(lBindOk == -1) {
        m_logs.addError(GFORMAT("Erreur lors de la liaison du socket.\n[%d]:%s", errno, strerror(errno)));
        return false;
    }

    int lListenOk = listen(m_socket, m_backlog);
    if(lListenOk == -1) {
        m_logs.addError(GFORMAT("Erreur lors de l'initialisation du backlog.\n[%d]:%s", errno, strerror(errno)));
        return false;
    }

    return !m_logs.hasErrors();
}
//===============================================
bool GSocket::run() {
    if(m_module == "") {
        m_logs.addError("Erreur le module est obligatoire.");
    }
    else if(m_module == "server_tcp") {
        runServerTcp();
    }
    else {
        m_logs.addError("Erreur le module est inconnu.");
    }
    return !m_logs.hasErrors();
}
//===============================================
bool GSocket::runServerTcp() {
    if(!createSocketX()) return false;
    printf("\n%s\n", m_startMessage.c_str());

    struct sockaddr_in lAddress2;
    socklen_t lSize = sizeof(lAddress2);

    GThread lThread;
    lThread.setThreadCB((void*)onThreadCB);

    while(1) {
        m_logs.showErrors();
        m_logs.clearMap();
        GSocket* lClient = new GSocket;
        lClient->m_socket = accept(m_socket, (struct sockaddr*)&lAddress2, &lSize);
        if(lClient->m_socket == -1) {
            m_logs.addError(GFORMAT("Erreur lors de l'acceptation de la connexion client.\n[%d]:%s", errno, strerror(errno)));
            continue;
        }
        lThread.setParams((void*)lClient);
        if(!lThread.run()) {
            m_logs.addLogs(lThread.getLogs());
            continue;
        }
    }

    printf("\n%s\n", m_stopMessage.c_str());

    closeSocket();
    return !m_logs.hasErrors();
}
//===============================================
void* GSocket::onThreadCB(void* _params) {
    GSocket* lClient = (GSocket*)_params;
    lClient->runThreadCB();
    lClient->closeSocket();
    delete lClient;
    return 0;
}
//===============================================
bool GSocket::runThreadCB() {
    GString lRequest;
    readData(lRequest);
    GLOGT(eGMSG, "RECEPTION [%d] :\n%s\n", lRequest.size(), lRequest.c_str());
    sendEchoHttp();
    return !m_logs.hasErrors();
}
//===============================================
void GSocket::closeSocket() {
    m_logs.showErrors();
    m_logs.clearMap();
    if(m_socket > 0) {close(m_socket); m_socket = 0;}
}
//===============================================
bool GSocket::readData(GString& _dataOut) {
    char lBuffer[BUFFER_SIZE + 1];
    int lSize = 0;
    while(1) {
        int lBytes = recv(m_socket, lBuffer, BUFFER_SIZE, 0);
        lSize += lBytes;
        if(lSize >= BUFFER_MAX) {
            m_logs.addError("Erreur le nombre d'octets maximal a été atteint.");
            break;
        }
        if(lBytes <= 0) break;
        lBuffer[lBytes] = 0;
        _dataOut += lBuffer;
        int lIoctlOk = ioctl(m_socket, FIONREAD, &lBytes);
        if(lIoctlOk == -1) break;
        if(lBytes <= 0) break;
    }
    return !m_logs.hasErrors();
}
//===============================================
bool GSocket::sendData(const GString& _dataIn) {
    if(_dataIn.isEmpty()) return true;
    int lSize = _dataIn.size();
    const char* lBuffer = _dataIn.c_str();
    int lIndex = 0;

    while(1) {
        int lBytes = send(m_socket, &lBuffer[lIndex], lSize - lIndex, 0);
        if(lBytes <= 0) break;
        lIndex += lBytes;
        if(lIndex >= lSize) break;
    }

    return !m_logs.hasErrors();
}
//===============================================
bool GSocket::sendEchoHttp() {
    GHttp lHttp;
    lHttp.setModule("response");
    lHttp.setContentText("Bonjour tout le monde !");
    lHttp.run();
    m_logs.addLogs(lHttp.getLogs());
    GString lResponse = lHttp.getResponseText();
    GLOGT(eGMSG, "EMISSION [%d] :\n%s\n", lResponse.size(), lResponse.c_str());
    sendData(lResponse);
    return !m_logs.hasErrors();
}
//===============================================
