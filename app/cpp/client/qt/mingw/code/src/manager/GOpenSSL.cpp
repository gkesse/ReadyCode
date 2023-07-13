//===============================================
#include "GOpenSSL.h"
#include "GCode.h"
//===============================================
GOpenSSL::GOpenSSL()
: GObject() {
    m_ssl = 0;
}
//===============================================
GOpenSSL::~GOpenSSL() {

}
//===============================================
int GOpenSSL::toPort() const {
    GString lEnv = getEnv("GPROJECT_ENV");
    if(lEnv == "TEST") return 9011;
    return 9010;
}
//===============================================
void GOpenSSL::checkErrors(GString& _data) {
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
void GOpenSSL::showCerts(SSL* _ssl) {
    X509* lCertificate = SSL_get_peer_certificate(_ssl);

    if(lCertificate) {
        printf("Server certificates:\n");

        const int lSize = 256;
        char lLine[lSize];

        X509_NAME_oneline(X509_get_subject_name(lCertificate), lLine, lSize);
        printf("Subject: %s\n", lLine);

        X509_NAME_oneline(X509_get_issuer_name(lCertificate), lLine, lSize);
        printf("Issuer: %s\n", lLine);

        X509_free(lCertificate);
    }
    else {
        printf("Info: No client certificates configured.\n");
    }
}
//===============================================
bool GOpenSSL::initContext(SSL_CTX** _context) {
    GString lCaFile = "C:/Users/tiaka/.readydev/data/app/certs/ca/ca_cert.pem";
    GString lCertificateFile = "C:/Users/tiaka/.readydev/data/app/certs/client/client_cert.pem";
    GString lPrivateFile = "C:/Users/tiaka/.readydev/data/app/certs/client/private/client_key.pem";
    bool lHasVerify = false;

    const SSL_METHOD* lMethod = SSLv23_client_method();

    if(!lMethod) {
        m_dataLogs.addError("La méthode n'est pas initialisée.");
        return false;
    }

    SSL_CTX* lContext = SSL_CTX_new(lMethod);

    if(!lContext) {
        m_dataLogs.addError("Le contexte n'est pas initialisé.");
        return false;
    }

    if(SSL_CTX_load_verify_locations(lContext, lCaFile.c_str(), 0) == -1) {
        m_dataLogs.addError(sformat("Le certificat racine n'est pas initialisé.\n[%lu]:%s", ERR_get_error(), ERR_error_string(ERR_get_error(), NULL)));
        return false;
    }

    if(SSL_CTX_use_certificate_file(lContext, lCertificateFile.c_str(), SSL_FILETYPE_PEM) == -1) {
        m_dataLogs.addError(sformat("Le certificat n'est pas initialisé.\n[%lu]:%s", ERR_get_error(), ERR_error_string(ERR_get_error(), NULL)));
        return false;
    }


    if(SSL_CTX_use_PrivateKey_file(lContext, lPrivateFile.c_str(), SSL_FILETYPE_PEM) == -1) {
        m_dataLogs.addError(sformat("La clé privée n'est pas initialisé.\n[%lu]:%s", ERR_get_error(), ERR_error_string(ERR_get_error(), NULL)));
        return false;
    }

    if(SSL_CTX_check_private_key(lContext) == -1) {
        m_dataLogs.addError(sformat("Le certificat et la clé privée ne sont pas liés.\n[%lu]:%s", ERR_get_error(), ERR_error_string(ERR_get_error(), NULL)));
        return false;
    }

    if(lHasVerify) {
        SSL_CTX_set_mode(lContext, SSL_MODE_AUTO_RETRY);
        SSL_CTX_set_verify(lContext, SSL_VERIFY_PEER, 0);
        SSL_CTX_set_verify_depth(lContext, 1);
    }
    else {
        SSL_CTX_set_verify(lContext, SSL_VERIFY_NONE, 0);
    }

    (*_context) = lContext;
    return true;
}
//===============================================
bool GOpenSSL::initSSL(SSL** _ssl, SSL_CTX* _context, SOCKET _socket) {
    bool lHasShowCerts = true;

    SSL* lSSL = SSL_new(_context);

    if(!lSSL) {
        m_dataLogs.addError(sformat("Le socket ssl n'est pas initialisé.\n[%lu]:%s", ERR_get_error(), ERR_error_string(ERR_get_error(), NULL)));
        return false;
    }

    if(SSL_set_fd(lSSL, _socket) == -1) {
        m_dataLogs.addError(sformat("La liaison du socket ssl n'est pas initialisé.\n[%lu]:%s", ERR_get_error(), ERR_error_string(ERR_get_error(), NULL)));
        return false;
    }

    if(SSL_connect(lSSL) == -1) {
        m_dataLogs.addError(sformat("La connexion au socket ssl n'est pas initialisé.\n[%lu]:%s", ERR_get_error(), ERR_error_string(ERR_get_error(), NULL)));
        return false;
    }

    if(lHasShowCerts) {
        showCerts(lSSL);
    }

    (*_ssl) = lSSL;
    return true;
}
//===============================================
GString GOpenSSL::callServer(const GString& _dataIn) {
    GString lData = callSocket(_dataIn);
    checkErrors(lData);
    return lData;
}
//===============================================
GString GOpenSSL::callSocket(const GString& _dataIn) {
    int lMajor = 2;
    int lMinor = 2;
    GString lHostname = "readydev.ovh";
    int lPort = toPort();
    GString lMode = "dns";

    WSADATA lWsaData;

    if(WSAStartup(MAKEWORD(lMajor, lMinor), &lWsaData) == SOCKET_ERROR) {
        m_dataLogs.addError("L'initialisation des données socket a échoué.");
        return "";
    }

    SOCKET lClient = socket(AF_INET, SOCK_STREAM, 0);

    if(lClient == INVALID_SOCKET) {
        m_dataLogs.addError("La création du socket a échoué.");
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
                m_dataLogs.addError("Le traitement du nom de domaine a échoué.");
                return "";
            }

            lHostname = inet_ntoa(((sockaddr_in *)lAddrs->ai_addr)->sin_addr);
        }
        else {
            m_dataLogs.addError("Le traitement du nom de domaine a échoué.");
            return "";
        }
    }

    SOCKADDR_IN lAddress;
    lAddress.sin_family = AF_INET;
    lAddress.sin_addr.s_addr = inet_addr(lHostname.c_str());
    lAddress.sin_port = htons(lPort);
    memset(&lAddress.sin_zero, 0, sizeof(lAddress.sin_zero));

    int lConnectOk = connect(lClient, (SOCKADDR*)(&lAddress), sizeof(lAddress));

    if(lConnectOk == SOCKET_ERROR) {
        m_dataLogs.addError("La connexion au socket n'est pas initialisé.");
        return "";
    }

    SSL_CTX* lContext = 0;

    if(!initContext(&lContext)) return "";
    if(!initSSL(&m_ssl, lContext, lClient)) return "";

    sendData(_dataIn);
    GString lDataOut = readData();

    SSL_free(m_ssl);
    SSL_CTX_free(lContext);

    closesocket(lClient);
    WSACleanup();

    return lDataOut;
}
//===============================================
GString GOpenSSL::callFacade(const GString& _module, const GString& _method, const GString& _data) {
    GCode lDom;
    lDom.createDoc();
    lDom.addData("manager", "module", _module);
    lDom.addData("manager", "method", _method);
    lDom.loadData(_data);
    GString lData = callServer(lDom.toString());
    checkErrors(lData);
    return lData;
}
//===============================================
void GOpenSSL::sendData(const GString& _dataIn) {
    if(_dataIn.isEmpty()) return;
    int lSize = _dataIn.size();
    const char* lBuffer = _dataIn.c_str();
    int lIndex = 0;

    while(1) {
        int lBytes = SSL_write(m_ssl, &lBuffer[lIndex], lSize - lIndex);
        if(lBytes == -1) {
            m_dataLogs.addError("L'envoi des données n'est pas terminé.");
            break;
        }
        lIndex += lBytes;
        if(lIndex >= lSize) break;
    }
}
//===============================================
GString GOpenSSL::readData() {
    GString lData = "";
    while(1) {
        char lBuffer[BUFFER_SIZE];
        int lBytes = SSL_read(m_ssl, lBuffer, BUFFER_SIZE - 1);

        if(lBytes == -1) {
            m_dataLogs.addError("La réception des données n'est pas terminé.");
            break;
        }

        lBuffer[lBytes] = '\0';
        lData += lBuffer;

        if(lData.size() >= BUFFER_MAX) {
            m_dataLogs.addError("Le nombre maximal de données en lecture est atteinte.");
            break;
        }

        lBytes = SSL_pending(m_ssl);

        if(lBytes <= 0) break;
    }
    return lData;
}
//===============================================
