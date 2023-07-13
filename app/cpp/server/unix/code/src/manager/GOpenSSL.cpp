//===============================================
#include "GOpenSSL.h"
#include "GServer.h"
#include "GCode.h"
//===============================================
typedef struct _sGData sGData;
//===============================================
struct _sGData {
    int verbose_mode;
    int verify_depth;
    int always_continue;
};
//===============================================
GOpenSSL::GOpenSSL()
: GObject() {
    m_socket = -1;
    m_ssl = 0;
    m_context = 0;
}
//===============================================
GOpenSSL::~GOpenSSL() {

}
//===============================================
GString GOpenSSL::toHostname(const GString& _facade) const {
    if(_facade == "server_c") return "127.0.0.1";
    if(_facade == "server_cpp") return "127.0.0.1";
    if(_facade == "server_python") return "127.0.0.1";
    if(_facade == "server_java") return "127.0.0.1";
    return "127.0.0.1";
}
//===============================================
int GOpenSSL::toPort(const GString& _facade) const {
    if(_facade == "server_c") return 9020;
    if(_facade == "server_cpp") return toPortCpp();
    if(_facade == "server_python") return 9030;
    if(_facade == "server_java") return 9040;
    return 9010;
}
//===============================================
int GOpenSSL::toPortCpp() const {
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
            m_logs.addError("Le serveur n'est pas disponible.");
            _data = "";
        }
    }
}
//===============================================
bool GOpenSSL::initContext(SSL_CTX** _context) {
    GString lCaFile = spath("/data/app/certs/ca/ca_cert.pem");
    GString lCertificateFile = spath("/data/app/certs/server/server_cert.pem");
    GString lPrivateFile = spath("/data/app/certs/server/private/server_key.pem");
    bool lHasVerify = true;


    const SSL_METHOD* lMethod = SSLv23_server_method();

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

    SSL_CTX_set_client_CA_list(lContext, SSL_load_client_CA_file(lCaFile.c_str()));

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
        SSL_CTX_set_verify(lContext, SSL_VERIFY_PEER | SSL_VERIFY_FAIL_IF_NO_PEER_CERT, 0);
        SSL_CTX_set_verify_depth(lContext, 1);
    }
    else {
        SSL_CTX_set_verify(lContext, SSL_VERIFY_NONE, 0);
    }

    (*_context) = lContext;
    return true;
}
//===============================================
bool GOpenSSL::initSSL() {
    bool lHasShowCerts = true;

    m_ssl = SSL_new(m_context);

    if(!m_ssl) {
        m_dataLogs.addError(sformat("Le socket ssl n'est pas initialisé.\n[%lu]:%s", ERR_get_error(), ERR_error_string(ERR_get_error(), NULL)));
        return false;
    }

    if(SSL_set_fd(m_ssl, m_socket) == -1) {
        m_dataLogs.addError(sformat("La liaison du socket ssl n'est pas initialisé.\n[%lu]:%s", ERR_get_error(), ERR_error_string(ERR_get_error(), NULL)));
        return false;
    }

    if(SSL_accept(m_ssl) == -1) {
        m_dataLogs.addError(sformat("La connexion au socket ssl n'est pas acceptée.\n[%lu]:%s", ERR_get_error(), ERR_error_string(ERR_get_error(), NULL)));
        return false;
    }

    if(lHasShowCerts) {
        showCerts(m_ssl);
    }

    return true;
}
//===============================================
void GOpenSSL::closeSocket() {
    SSL_free(m_ssl);
    close(m_socket);
}
//===============================================
void GOpenSSL::showCerts(SSL* _ssl) {
    X509* lCertificate = SSL_get_peer_certificate(_ssl);

    if(lCertificate) {
        printf("Server certificates:\n");

        const int lSize = 256;
        char lLine[lSize];

        X509_NAME_oneline(X509_get_subject_name(lCertificate), lLine, 1024);
        printf("Subject: %s\n", lLine);

        X509_NAME_oneline(X509_get_issuer_name(lCertificate), lLine, 1024);
        printf("Issuer: %s\n", lLine);

        X509_free(lCertificate);
    }
    else {
        printf("Info: No client certificates configured.\n");
    }
}
//===============================================
void GOpenSSL::runServer() {
    runSocket();
    if(m_dataLogs.hasErrors()) {
        m_logs.addError("Le serveur n'est pas disponible.");
    }
}
//===============================================
void GOpenSSL::runSocket() {
    int lPort = toPortCpp();
    int lBacklog = 10;
    GString lHostname = "0.0.0.0";

    int lServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if(lServer == -1) {
        m_dataLogs.addError("Le socket n'est pas initialisé.");
        return;
    }

    struct sockaddr_in lAddress;
    bzero(&lAddress, sizeof(lAddress));
    lAddress.sin_family = AF_INET;
    lAddress.sin_addr.s_addr = inet_addr(lHostname.c_str());
    lAddress.sin_port = htons(lPort);

    int lBindOk = bind(lServer, (struct sockaddr*)&lAddress, sizeof(lAddress));

    if(lBindOk == -1) {
        m_dataLogs.addError("La liaison du socket server a échoué.");
        return;
    }

    int lListenOk = listen(lServer, lBacklog);

    if(lListenOk == -1) {
        m_dataLogs.addError("L'initialisation du nombre de connexions à écouter a échoué.");
        return;
    }

    SSL_CTX* lContext = 0;
    if(!initContext(&lContext)) return;

    printf("Démarrage du serveur...\n");

    struct sockaddr_in lAddressC;
    socklen_t lAddressCL = sizeof(lAddressC);

    while(1) {
        GOpenSSL* lClient = new GOpenSSL;
        lClient->m_socket = accept(lServer, (struct sockaddr*)&lAddressC, &lAddressCL);
        lClient->m_context = lContext;

        pthread_t lThreadH;
        int lOk = pthread_create(&lThreadH, 0, onThreadCB, lClient);

        if(lOk == -1) {
            m_dataLogs.addError("Le thread n'est pas initialisé.");
            break;
        }
    }

    close(lServer);
    SSL_CTX_free(lContext);
}
//===============================================
void* GOpenSSL::onThreadCB(void* _params) {
    GOpenSSL* lClient = (GOpenSSL*)_params;
    if(lClient->initSSL()) {
        GString lData = lClient->readData();
        GServer lServer;
        lServer.run(lData);
        lServer.sendResponse(lClient);
    }
    lClient->closeSocket();
    delete lClient;
    return 0;
}
//===============================================
int GOpenSSL::onPasswordCB(char* _buf, int _size, int _rwflag, void* _password) {
    strncpy(_buf, (char*)(_password), _size);
    _buf[_size - 1] = '\0';
    return (int)strlen(_buf);
}
//===============================================
int GOpenSSL::onVerifyCB(int preverify_ok, X509_STORE_CTX *ctx) {
    return 0;
}
//===============================================
GString GOpenSSL::callSocket(const GString& _dataIn, const GString& _facade) {
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
GString GOpenSSL::callServer(const GString& _dataIn, const GString& _facade) {
    GString lData = callSocket(_dataIn, _facade);
    checkErrors(lData);
    return lData;
}
//===============================================
GString GOpenSSL::callFacade(const GString& _module, const GString& _method, const GString& _data) {
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
