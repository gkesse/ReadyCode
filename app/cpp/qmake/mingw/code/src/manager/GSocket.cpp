//===============================================
#include "GSocket.h"
#include "GXml.h"
#include "GLog.h"
#include "GPath.h"
#include "GThread.h"
#include "GCode.h"
#include "GEnv.h"
//===============================================
GSocket::GSocket() {
    createDoms();
    m_server = 0;
}
//===============================================
GSocket::~GSocket() {

}
//===============================================
void GSocket::createDoms() {
    m_dom.reset(new GXml);
    m_dom->loadXmlFile(GRES("xml", "pad.xml"));
    m_dom->createXPath();
    //
    m_domWsaError.reset(new GXml);
    m_domWsaError->loadXmlFile(GRES("xml", "wsa_error.xml"));
    m_domWsaError->createXPath();
    //
    m_res.reset(new GCode);
    m_res->createCode();
}
//===============================================
QString GSocket::getItem(const QString& _key, const QString& _data) const {
    m_dom->queryXPath(QString("/rdv/datas/data[code='%1']/%2").arg(_key).arg(_data));
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
QString GSocket::getErrorMsg(const QString& _code, const QString& _lang) const {
    m_domWsaError->queryXPath(QString("/rdv/datas/data[code='%1']/%2").arg(_code).arg(_lang));
    m_domWsaError->getNodeXPath();
    QString lData = m_domWsaError->getNodeValue();
    return lData;
}
//===============================================
int GSocket::loadDomain() const {
    int lDomain = AF_INET;
    QString lName = getItem("socket", "domain");
    if(lName == "AF_INET") {
        lDomain = AF_INET;
    }
    return lDomain;
}
//===============================================
int GSocket::loadType() const {
    int lType = SOCK_STREAM;
    QString lName = getItem("socket", "type");
    if(lName == "SOCK_STREAM") {
        lType = SOCK_STREAM;
    }
    return lType;
}
//===============================================
int GSocket::loadProtocol() const {
    int lProtocol = IPPROTO_TCP;
    QString lName = getItem("socket", "type");
    if(lName == "IPPROTO_TCP") {
        lProtocol = IPPROTO_TCP;
    }
    return lProtocol;
}
//===============================================
int GSocket::loadFamily() const {
    int lFamily = AF_INET;
    QString lName = getItem("socket", "domain");
    if(lName == "AF_INET") {
        lFamily = AF_INET;
    }
    return lFamily;
}
//===============================================
int GSocket::loadPort() const {
    return loadPort(GEnv().isTestEnv());
}
//===============================================
int GSocket::loadPort(int _isTestEnv) const {
    int lPort = getItem("socket", "prod_port").toInt();
    if(_isTestEnv) lPort = getItem("socket", "test_port").toInt();
    return lPort;
}
//===============================================
QString GSocket::loadErrorMsg() const {
    QString lErrorCode = QString("%1").arg(WSAGetLastError());
    QString lLang = getErrorMsg("lang", "lang");
    QString lErrorMsg = getErrorMsg(lErrorCode, lLang);
    return lErrorMsg;
}
//===============================================
GSocket& GSocket::initSocket(int _major, int _minor) {
    WSADATA lWsaData;
    WSAStartup(MAKEWORD(_major, _minor), &lWsaData);
    return *this;
}
//===============================================
GSocket& GSocket::createSocket(int _domain, int _type, int _protocol) {
    m_socket = socket(_domain, _type, _protocol);
    if(m_socket == INVALID_SOCKET) {
        GERROR(eGERR, QString(""
                "Erreur lors de la creation du socket.\n"
                "erreur_code..: %1\n"
                "error_msg....: %2\n")
                .arg(WSAGetLastError()).arg(loadErrorMsg()));
        return *this;
    }
    return *this;
}
//===============================================
GSocket& GSocket::createAddress(int _family, const QString& _addressIp, int _port) {
    m_address.sin_family = _family;
    m_address.sin_addr.s_addr = inet_addr(_addressIp.toStdString().c_str());
    m_address.sin_port = htons(_port);
    memset(&m_address.sin_zero, 0, sizeof(m_address.sin_zero));
    return *this;
}
//===============================================
GSocket& GSocket::listenSocket(int _backlog) {
    int lAnswer = listen(m_socket, _backlog);
    if(lAnswer == SOCKET_ERROR) {
        GERROR(eGERR, QString(""
                "Erreur lors de l'init du nombre de connexion a ecouter.\n"
                "erreur_code..: %1\n"
                "error_msg....: %2\n")
                .arg(WSAGetLastError()).arg(loadErrorMsg()));
        return *this;
    }
    return *this;
}
//===============================================
GSocket& GSocket::bindSocket() {
    int lAnswer = bind(m_socket, (SOCKADDR*)&m_address, sizeof(m_address));
    if(lAnswer == SOCKET_ERROR) {
        GERROR(eGERR, QString(""
                "Erreur lors de la liaison du socket a l'adresse.\n"
                "erreur_code..: %1\n"
                "error_msg....: %2\n")
                .arg(WSAGetLastError()).arg(loadErrorMsg()));
        return *this;
    }
    return *this;
}
//===============================================
GSocket& GSocket::connectSocket() {
    int lAnswer = connect(m_socket, (SOCKADDR*)(&m_address), sizeof(m_address));
    if(lAnswer == SOCKET_ERROR) {
        GERROR(eGERR, QString(""
                "Erreur lors de la connexion au serveur.\n"
                "erreur_code..: %1\n"
                "error_msg....: %2\n")
                .arg(WSAGetLastError()).arg(loadErrorMsg()));
        return *this;
    }
    return *this;
}
//===============================================
void GSocket::startMessage() {
    GLOGT(eGMSG, QString("demarrage du serveur..."));
}
//===============================================
GSocket& GSocket::acceptSocket(GSocket& _socket) {
    int lSize = sizeof(_socket.m_address);
    _socket.m_socket = accept(m_socket, (SOCKADDR*)&_socket.m_address, &lSize);
    if(_socket.m_socket == INVALID_SOCKET) {
        GERROR(eGERR, QString(""
                "Erreur lors de l'acceptation d'un client.\n"
                "erreur_code..: %1\n"
                "error_msg....: %2\n")
                .arg(WSAGetLastError()).arg(loadErrorMsg()));
        return *this;
    }
    return *this;
}
//===============================================
GSocket& GSocket::acceptSocket(GSocket* _socket) {
    int lSize = sizeof(_socket->m_address);
    _socket->m_socket = accept(m_socket, (SOCKADDR*)&_socket->m_address, &lSize);
    if(_socket->m_socket == INVALID_SOCKET) {
        GERROR(eGERR, QString(""
                "Erreur lors de l'acceptation d'un client.\n"
                "erreur_code..: %1\n"
                "error_msg....: %2\n")
                .arg(WSAGetLastError()).arg(loadErrorMsg()));
        return *this;
    }
    return *this;
}
//===============================================
int GSocket::recvData(QString& _data) {
    return recvData(_data, BUFFER_DATA_SIZE);
}
//===============================================
int GSocket::recvData(QString& _data, int _size) {
    _data.clear();
    char lBuffer[BUFFER_DATA_SIZE + 1];
    int lBytes = recv(m_socket, lBuffer, _size, 0);
    GLOGT(eGOFF, QString("SIZE.........: %1\n").arg(lBytes));
    if(lBytes == -1) {
        GERROR(eGERR, QString(""
                "Erreur lors de la reception des donnees.\n"
                "erreur_code..: %1\n"
                "error_msg....: %2\n")
                .arg(WSAGetLastError()).arg(loadErrorMsg()));
        return -1;
    }
    lBuffer[lBytes] = 0;
    _data = lBuffer;
    return lBytes;
}
//===============================================
int GSocket::recvData(GSocket& _socket, QString& _data) {
    _data.clear();
    char lBuffer[BUFFER_DATA_SIZE + 1];
    int lSize = sizeof(_socket.m_address);
    int lBytes = recvfrom(m_socket, lBuffer, BUFFER_DATA_SIZE, 0, (SOCKADDR*)&_socket.m_address, &lSize);
    if(lBytes == -1) {
        GERROR(eGERR, QString(""
                "Erreur lors de la reception des donnees.\n"
                "erreur_code..: %1\n"
                "error_msg....: %2\n")
                .arg(WSAGetLastError()).arg(loadErrorMsg()));
        return -1;
    }
    return lBytes;
}
//===============================================
int GSocket::readData(QString& _data) {
    _data.clear();
    QString lBuffer;
    recvData(lBuffer, BUFFER_NDATA_SIZE);
    GLOGT(eGOFF, QString("[%1]").arg(lBuffer));
    int lSize = lBuffer.toInt();
    int lBytes = 0;

    for(int i = 0; i < lSize; i++) {
        int iBytes = recvData(lBuffer);
        if(iBytes == -1) {
            GERROR(eGERR, QString(""
                    "Erreur lors de la reception des donnees.\n"
                    "bytes........: %1\n"
                    "ibytes.......: %2\n"
                    "erreur_code..: %3\n"
                    "error_msg....: %4\n")
                    .arg(lBytes).arg(iBytes).arg(WSAGetLastError()).arg(loadErrorMsg()));
            return -1;
        }
        _data += lBuffer;
        lBytes += iBytes;
    }
    GLOGT(eGOFF, QString("[RECEPTION]..: %1\n%2").arg(_data.size()).arg(_data));
    return lBytes;
}
//===============================================
int GSocket::readPack(QString& _data) {
    _data.clear();
    QString lBuffer;
    recvData(lBuffer, BUFFER_NDATA_SIZE);
    GLOGT(eGOFF, QString("[%1]").arg(lBuffer));
    int lSize = lBuffer.toInt();
    int lBytes = 0;
    GLOGT(eGOFF, QString("LENGTH.......: %1 : %2\n").arg(lBuffer.size()).arg(lSize));

    while(1) {
        if(lBytes >= lSize) break;
        int iBytes = recvData(lBuffer);
        GLOGT(eGOFF, QString("SIZE.........: %1\n").arg(iBytes));
        if(iBytes == -1) {
            GERROR(eGERR, QString(""
                    "Erreur lors de la reception des donnees.\n"
                    "bytes........: %1\n"
                    "ibytes.......: %2\n"
                    "erreur_code..: %3\n"
                    "error_msg....: %4\n")
                    .arg(lBytes).arg(iBytes).arg(WSAGetLastError()).arg(loadErrorMsg()));
            return -1;
        }
        _data += lBuffer;
        lBytes += iBytes;
    }
    GLOGT(eGOFF, QString("[RECEPTION]..: %1\n%2").arg(_data.size()).arg(_data));
    return lBytes;
}
//===============================================
int GSocket::sendData(const QString& _data) {
    int lBytes = send(m_socket, _data.toStdString().c_str(), _data.size(), 0);
    GLOGT(eGOFF, QString("SIZE.........: %1\n").arg(lBytes));
    if(lBytes == -1) {
        GERROR(eGERR, QString(""
                "Erreur lors de l'emission des donnees.\n"
                "bytes........: %1\n"
                "erreur_code..: %2\n"
                "error_msg....: %3\n")
                .arg(lBytes).arg(WSAGetLastError()).arg(loadErrorMsg()));
        return -1;
    }
    return lBytes;
}
//===============================================
int GSocket::sendData(GSocket& _socket, const QString& _data) {
    int lSize = sizeof(_socket.m_address);
    int lBytes = sendto(m_socket, _data.toStdString().c_str(), _data.size(), 0, (SOCKADDR*)&_socket.m_address, lSize);
    if(lBytes == -1) {
        GERROR(eGERR, QString(""
                "Erreur lors de l'emission des donnees.\n"
                "bytes........: %1\n"
                "erreur_code..: %2\n"
                "error_msg....: %3\n")
                .arg(lBytes).arg(WSAGetLastError()).arg(loadErrorMsg()));
        return -1;
    }
    return lBytes;
}
//===============================================
int GSocket::writeData(const QString& _data) {
    int lBytes = 0;
    int lLength = _data.size();
    int lSize = (int)ceil((double)lLength/BUFFER_DATA_SIZE);
    QString lBuffer = QString("%1").arg(lSize);
    lBuffer = lBuffer.leftJustified(BUFFER_NDATA_SIZE);
    GLOGT(eGOFF, QString("[%1]").arg(lBuffer));
    sendData(lBuffer);

    GLOGT(eGOFF, QString("[EMISSION]...: %1\n%2").arg(_data.size()).arg(_data));
    for(int i = 0; i < lSize; i++) {
        QString lBuffer = _data.mid(lBytes, BUFFER_DATA_SIZE);
        int iBytes = sendData(lBuffer);
        if(iBytes == -1) {
            GERROR(eGERR, QString(""
                    "Erreur lors de l'emission des donnees.\n"
                    "bytes........: %1.\n"
                    "ibytes.......: %2.\n"
                    "erreur_code..: %3\n"
                    "error_msg....: %4\n")
                    .arg(lBytes).arg(iBytes).arg(WSAGetLastError()).arg(loadErrorMsg()));
            return -1;
        }
        lBytes += iBytes;
    }

    return lBytes;
}
//===============================================
int GSocket::writePack(const QString& _data) {
    int lBytes = 0;
    int lSize = _data.size();
    QString lBuffer = QString("%1").arg(lSize);
    lBuffer = lBuffer.leftJustified(BUFFER_NDATA_SIZE);
    GLOGT(eGOFF, QString("[%1]").arg(lBuffer));
    sendData(lBuffer);
    GLOGT(eGOFF, QString("LENGTH.......: %1 : %2\n").arg(lBuffer.size()).arg(lSize));

    GLOGT(eGOFF, QString("[EMISSION]...: %1\n%2").arg(_data.size()).arg(_data));

    while(1) {
        if(lBytes >= lSize) break;
        QString lBuffer = _data.mid(lBytes, BUFFER_DATA_SIZE);
        int iBytes = sendData(lBuffer);
        GLOGT(eGOFF, QString("SIZE.........: %1\n").arg(iBytes));
        if(iBytes == -1) {
            GERROR(eGERR, QString(""
                    "Erreur lors de l'emission des donnees.\n"
                    "bytes........: %1\n"
                    "ibytes.......: %2\n"
                    "erreur_code..: %3\n"
                    "error_msg....: %4\n")
                    .arg(lBytes).arg(iBytes).arg(WSAGetLastError()).arg(loadErrorMsg()));
            return -1;
        }
        lBytes += iBytes;
    }

    return lBytes;
}
//===============================================
QString GSocket::loadAddressIp() const {
    QString lAddressIp = inet_ntoa(m_address.sin_addr);
    return lAddressIp;
}
//===============================================
QString GSocket::getHostname() const {
    char lBuffer[BUFFER_HOSTNAME_SIZE + 1];
    gethostname(lBuffer, BUFFER_HOSTNAME_SIZE);
    QString lHostname = lBuffer;
    return lHostname;
}
//===============================================
void GSocket::closeSocket() {
    closesocket(m_socket);
}
//===============================================
void GSocket::cleanSocket() {
    WSACleanup();
}
//===============================================
void GSocket::startServer(void* _onServerThread) {
    int lMajor = getItem("socket", "major").toInt();
    int lMinor = getItem("socket", "minor").toInt();
    int lDomain = loadDomain();
    int lType = loadType();
    int lProtocol = loadProtocol();
    int lFamily = loadFamily();
    QString lClientIp = getItem("socket", "client_ip");
    int lPort = loadPort();
    int lBacklog = getItem("socket", "backlog").toInt();

    GLOGT(eGMSG, QString(""
            "domain.......: %1\n"
            "type.........: %2\n"
            "protocol.....: %3\n"
            "family.......: %4\n"
            "port.........: %5\n"
            "backlog......: %6\n"
            "env..........: %7\n"
            "").arg(lDomain)
            .arg(lType)
            .arg(lProtocol)
            .arg(lFamily)
            .arg(lPort)
            .arg(lBacklog)
            .arg(GEnv().getEnvType())
    );

    initSocket(lMajor, lMinor);
    createSocket(lDomain, lType, lProtocol);
    createAddress(lFamily, lClientIp, lPort);
    bindSocket();
    listenSocket(lBacklog);
    startMessage();

    GThread lThread;

    while(1) {
        GSocket* lClient = new GSocket;
        lClient->m_server = this;
        acceptSocket(lClient);
        lThread.createThread(_onServerThread, lClient);
    }

    closeSocket();
    cleanSocket();
}
//===============================================
DWORD WINAPI GSocket::onServerThread(LPVOID _params) {
    GSocket* lClient = (GSocket*)_params;
    GSocket* lServer = lClient->m_server;
    QStack<GSocket*>& lClientIns = lServer->m_clientIns;

    QString lDataIn;
    if(lClient->readPack(lDataIn) == -1) {
        delete lClient;
        return 0;
    }

    lClient->setReq(lDataIn);
    lClientIns.push(lClient);
    return 0;
}
//===============================================
QString GSocket::callServer(const QString& _module, const QString& _method) {
    GCode lReq;
    lReq.createRequest(_module, _method);
    lReq.addPseudo();
    QString lDataOut = callServer(lReq.toString());
    return lDataOut;
}
//===============================================
QString GSocket::callServer(const QString& _module, const QString& _method, const QString& _params) {
    GCode lReq;
    lReq.createRequest(_module, _method);
    lReq.loadCode(_params);
    lReq.addPseudo();
    QString lDataOut = callServer(lReq.toString());
    return lDataOut;
}
//===============================================
QString GSocket::callServer(const QString& _dataIn) {
    int lMajor = getItem("socket", "major").toInt();
    int lMinor = getItem("socket", "minor").toInt();
    int lDomain = loadDomain();
    int lType = loadType();
    int lProtocol = loadProtocol();
    int lFamily = loadFamily();
    QString lServerIp = getItem("socket", "server_ip");
    int lPort = loadPort();

    initSocket(lMajor, lMinor);
    createSocket(lDomain, lType, lProtocol);
    createAddress(lFamily, lServerIp, lPort);
    connectSocket();

    QString lDataOut;
    writePack(_dataIn);
    readPack(lDataOut);

    GLOGT(eGOFF, QString("[EMISSION]...: %1\n%2").arg(_dataIn.size()).arg(_dataIn));
    GLOGT(eGOFF, QString("[RECEPTION]..: %1\n%2").arg(lDataOut.size()).arg(lDataOut));

    GERROR_LOAD(eGERR, lDataOut);

    if(GLOGI->hasErrors()) {
        GLOGI->clearErrors();
        GERROR(eGERR, "Erreur lors de la connexion au serveur.\n");
    }

    closeSocket();
    cleanSocket();
    return lDataOut;
}
//===============================================
void GSocket::setReq(const QString& _req) {
    m_req.reset(new GCode(_req));
}
//===============================================
QSharedPointer<GCode>& GSocket::getReq() {
    return m_req;
}
//===============================================
QStack<GSocket*>& GSocket::getClientIns() {
    return m_clientIns;
}
//===============================================
QSharedPointer<GCode>& GSocket::getResponse(){
    return m_res;
}
//===============================================
