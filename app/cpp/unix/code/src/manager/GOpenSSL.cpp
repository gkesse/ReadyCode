//===============================================
#include "GOpenSSL.h"
#include "GSocket.h"
#include "GThread.h"
#include "GHttp.h"
//===============================================
GOpenSSL::GOpenSSL()
: GObject() {
    m_ssl = 0;
    m_privateKey = 0;
    m_certificate = 0;
    m_port = 0;
    m_backlog = 0;
    m_hasGenerateCertificate = false;
    m_socket = 0;
    m_context = 0;
}
//===============================================
GOpenSSL::~GOpenSSL() {

}
//===============================================
void GOpenSSL::initModule() {
    SSL_load_error_strings();
    ERR_load_crypto_strings();
    OpenSSL_add_all_algorithms();
    SSL_library_init();
}
//===============================================
void GOpenSSL::clearModule() {
    ERR_free_strings();
    EVP_cleanup();
}
//===============================================
void GOpenSSL::setOpenSSL(const GOpenSSL& _obj) {
    m_context = _obj.m_context;
}
//===============================================
void GOpenSSL::setStartMessage(const GString& _startMessage) {
    m_startMessage = _startMessage;
}
//===============================================
void GOpenSSL::setStopMessage(const GString& _stopMessage) {
    m_stopMessage = _stopMessage;
}
//===============================================
void GOpenSSL::setHostname(const GString& _hostname) {
    m_hostname = _hostname;
}
//===============================================
void GOpenSSL::setPort(int _port) {
    m_port = _port;
}
//===============================================
void GOpenSSL::setBacklog(int _backlog) {
    m_backlog = _backlog;
}
//===============================================
void GOpenSSL::setHasGenerateCertificate(bool _hasGenerateCertificate) {
    m_hasGenerateCertificate = _hasGenerateCertificate;
}
//===============================================
void GOpenSSL::setCertificateFile(const GString& _certificateFile) {
    m_certificateFile = _certificateFile;
}
//===============================================
void GOpenSSL::setPrivateKeyFile(const GString& _privateKeyFile) {
    m_privateKeyFile = _privateKeyFile;
}
//===============================================
void GOpenSSL::setCountry(const GString& _country) {
    m_country = _country;
}
//===============================================
void GOpenSSL::setLocality(const GString& _locality) {
    m_locality = _locality;
}
//===============================================
void GOpenSSL::setState(const GString& _state) {
    m_state = _state;
}
//===============================================
void GOpenSSL::setOrganisation(const GString& _organisation) {
    m_organisation = _organisation;
}
//===============================================
void GOpenSSL::setOrganisationalUnit(const GString& _organisationalUnit) {
    m_organisationalUnit = _organisationalUnit;
}
//===============================================
void GOpenSSL::setCommonName(const GString& _commonName) {
    m_commonName = _commonName;
}
//===============================================
bool GOpenSSL::generatePrivateKey() {
    EVP_PKEY_CTX* lContext = EVP_PKEY_CTX_new_id(EVP_PKEY_RSA, NULL);
    if(!lContext) {
        m_logs.addError("Erreur lors de l'initialisation du contexte.");
        return false;
    }

    EVP_PKEY_keygen_init(lContext);
    EVP_PKEY_CTX_set_rsa_keygen_bits(lContext, 2048);
    EVP_PKEY_keygen(lContext, &m_privateKey);
    return !m_logs.hasErrors();
}
//===============================================
bool GOpenSSL::generateCertificate() {
    if(!m_privateKey) {
        m_logs.addError("Erreur la clé privée n'est pas initialisée.");
        return false;
    }
    if(m_country.isEmpty()) {
        m_logs.addError("Erreur le pays n'est pas initialisé.");
        return false;
    }
    if(m_commonName.isEmpty()) {
        m_logs.addError("Erreur le nom usuel n'est pas initialisé.");
        return false;
    }

    m_certificate = X509_new();
    if(!m_certificate) {
        m_logs.addError("Erreur le certificat n'est pas initialisé.");
        return false;
    }

    X509_set_version(m_certificate, X509_VERSION_3);
    ASN1_INTEGER_set(X509_get_serialNumber(m_certificate), 0);
    X509_gmtime_adj(X509_get_notBefore(m_certificate), 0);
    X509_gmtime_adj(X509_get_notAfter(m_certificate), (long)60*60*24*365);
    X509_set_pubkey(m_certificate, m_privateKey);

    X509_NAME* lName = X509_get_subject_name(m_certificate);

    X509_NAME_add_entry_by_txt(lName, "C", MBSTRING_ASC, (const unsigned char*)m_country.c_str(), -1, -1, 0);
    X509_NAME_add_entry_by_txt(lName, "CN", MBSTRING_ASC, (const unsigned char*)m_commonName.c_str(), -1, -1, 0);

    if(!m_state.isEmpty()) {
        X509_NAME_add_entry_by_txt(lName, "ST", MBSTRING_ASC, (const unsigned char*)m_state.c_str(), -1, -1, 0);
    }
    if(!m_locality.isEmpty()) {
        X509_NAME_add_entry_by_txt(lName, "L", MBSTRING_ASC, (const unsigned char*)m_locality.c_str(), -1, -1, 0);
    }
    if(!m_organisation.isEmpty()) {
        X509_NAME_add_entry_by_txt(lName, "O", MBSTRING_ASC, (const unsigned char*)m_organisation.c_str(), -1, -1, 0);
    }
    if(!m_organisationalUnit.isEmpty()) {
        X509_NAME_add_entry_by_txt(lName, "OU", MBSTRING_ASC, (const unsigned char*)m_organisationalUnit.c_str(), -1, -1, 0);
    }

    X509_set_issuer_name(m_certificate, lName);
    X509_sign(m_certificate, m_privateKey, EVP_md5());
    return !m_logs.hasErrors();
}
//===============================================
bool GOpenSSL::generateRSA() {
    const int kBits = 1024;
    const int kExp = 3;
    int lKeyLen;
    char* lPemKey;

    RSA* lRsa = RSA_generate_key(kBits, kExp, 0, 0);
    BIO* lBio = BIO_new(BIO_s_mem());
    PEM_write_bio_RSAPrivateKey(lBio, lRsa, NULL, NULL, 0, NULL, NULL);

    lKeyLen = BIO_pending(lBio);
    lPemKey = (char*)calloc(lKeyLen + 1, 1);
    BIO_read(lBio, lPemKey, lKeyLen);

    m_rsaKey = lPemKey;

    BIO_free_all(lBio);
    RSA_free(lRsa);
    free(lPemKey);
    return !m_logs.hasErrors();
}
//===============================================
bool GOpenSSL::readData(GString& _dataOut, int _size) {
    if(_size <= 0) return false;
    char lBuffer[BUFFER_SIZE + 1];
    int lSize = 0;
    while(1) {
        int lBytes = SSL_read(m_ssl, lBuffer, BUFFER_SIZE);
        if(lBytes <= 0) return false;
        lBuffer[lBytes] = 0;
        _dataOut += lBuffer;
        lSize += lBytes;
        if(lSize >= _size) return true;
    }
    return true;
}
//===============================================
bool GOpenSSL::sendData(const GString& _dataIn) {
    if(_dataIn.isEmpty()) return false;
    int lSize = _dataIn.size();
    const char* lBuffer = _dataIn.c_str();
    int lIndex = 0;

    while(1) {
        int lBytes = SSL_write(m_ssl, &lBuffer[lIndex], lSize - lIndex);
        if(lBytes <= 0) return false;
        lIndex += lBytes;
        if(lIndex >= lSize) break;
    }

    return true;
}
//===============================================
bool GOpenSSL::sendHttp() {
    GHttp lHttp;
    lHttp.setModule("response");
    lHttp.setContentText("Hello World!");
    lHttp.run();
    lHttp.getResponseText().print();
    sendData(lHttp.getResponseText());
    return !m_logs.hasErrors();
}
//===============================================
bool GOpenSSL::run() {
    GSocket lSocket;
    lSocket.setHostname(m_hostname);
    lSocket.setPort(m_port);
    lSocket.setBacklog(m_backlog);
    if(!lSocket.createSocketX()) {
        m_logs.addLogs(lSocket.getLogs());
        return false;
    }

    m_socket = lSocket.getSocket();

    struct sockaddr_in lClientAddress;
    socklen_t lClientAddressSize = sizeof(lClientAddress);

    if(!initSSL()) return false;

    GThread lThread;
    lThread.setThreadCB((void*)onThreadCB);

    printf("\n%s\n", m_startMessage.c_str());

    while(1) {
        m_logs.showErrors();
        m_logs.clearMap();
        GOpenSSL* lClient = new GOpenSSL;
        lClient->m_socket = accept(m_socket, (struct sockaddr*)&lClientAddress, &lClientAddressSize);
        if(lClient->m_socket <= 0) {
            m_logs.addError(GFORMAT("Erreur lors de l'acceptation de la connexion client.\n[%lu]:%s", errno, strerror(errno)));
            continue;
        }
        lClient->setOpenSSL(*this);
        lThread.setParams((void*)lClient);
        if(!lThread.run()) {
            m_logs.addLogs(lThread.getLogs());
            continue;
        }
    }

    printf("\n%s\n", m_stopMessage.c_str());

    cleanSSL();
    return !m_logs.hasErrors();
}
//===============================================
int GOpenSSL::onPasswordCB(char* _buf, int _size, int _rwflag, void* _password) {
    strncpy(_buf, (char*)(_password), _size);
    _buf[_size - 1] = '\0';
    return (int)strlen(_buf);
}
//===============================================
void* GOpenSSL::onThreadCB(void* _params) {
    GOpenSSL* lClient = (GOpenSSL*)_params;
    lClient->acceptSSL();
    lClient->runThreadCB();
    lClient->closeSSL();
    delete lClient;
    return 0;
}
//===============================================
bool GOpenSSL::initSSL() {
    m_context = SSL_CTX_new(SSLv23_server_method());
    if(!m_context) {
        m_logs.addError(GFORMAT("Erreur lors de l'initialisation du contexte.\n[%lu]:%s", ERR_get_error(), ERR_error_string(ERR_get_error(), NULL)));
        return false;
    }

    SSL_CTX_set_options(m_context, SSL_OP_SINGLE_DH_USE);

    if(m_hasGenerateCertificate) {
        if(!generatePrivateKey()) return false;
        if(!generateCertificate()) return false;

        int lCertificateOk = SSL_CTX_use_certificate(m_context, m_certificate);
        if(lCertificateOk <= 0) {
            m_logs.addError(GFORMAT("Erreur lors de l'initialisation du certificat.\n[%lu]:%s", ERR_get_error(), ERR_error_string(ERR_get_error(), NULL)));
            return false;
        }

        SSL_CTX_set_default_passwd_cb(m_context, onPasswordCB);

        int lPrivateKeyOk = SSL_CTX_use_PrivateKey(m_context, m_privateKey);
        if(lPrivateKeyOk <= 0) {
            m_logs.addError(GFORMAT("Erreur lors de l'initialisation de la clé privée.\n[%lu]:%s", ERR_get_error(), ERR_error_string(ERR_get_error(), NULL)));
            return false;
        }
    }
    else {
        int lCertificateOk = SSL_CTX_use_certificate_file(m_context, m_certificateFile.c_str() , SSL_FILETYPE_PEM);
        if(lCertificateOk <= 0) {
            m_logs.addError(GFORMAT("Erreur lors de l'initialisation du certificat.\n[%lu]:%s", ERR_get_error(), ERR_error_string(ERR_get_error(), NULL)));
            return false;
        }

        SSL_CTX_set_default_passwd_cb(m_context, onPasswordCB);

        int lPrivateKeyOk = SSL_CTX_use_PrivateKey_file(m_context, m_privateKeyFile.c_str(), SSL_FILETYPE_PEM);
        if(lPrivateKeyOk <= 0) {
            m_logs.addError(GFORMAT("Erreur lors de l'initialisation de la clé privée.\n[%lu]:%s", ERR_get_error(), ERR_error_string(ERR_get_error(), NULL)));
            return false;
        }
    }

    SSL_CTX_set_verify(m_context, SSL_VERIFY_NONE, 0);

    return !m_logs.hasErrors();
}
//===============================================
bool GOpenSSL::acceptSSL() {
    m_ssl = SSL_new(m_context);
    if(!m_ssl) {
        m_logs.addError(GFORMAT("Erreur lors de l'initialisation du socket sécurisé.\n[%lu]:%s", ERR_get_error(), ERR_error_string(ERR_get_error(), NULL)));
        return false;
    }

    int lSetOk = SSL_set_fd(m_ssl, m_socket);
    if(lSetOk <= 0) {
        m_logs.addError(GFORMAT("Erreur lors de l'initialisation du descripteur.\n[%lu]:%s", ERR_get_error(), ERR_error_string(ERR_get_error(), NULL)));
        return false;
    }

    int lAcceptOk = SSL_accept(m_ssl);
    if(lAcceptOk <= 0) {
        m_logs.addError(GFORMAT("Erreur lors de l'acceptation de la connexion.\n[%lu]:%s", ERR_get_error(), ERR_error_string(ERR_get_error(), NULL)));
        return false;
    }

    return !m_logs.hasErrors();
}
//===============================================
bool GOpenSSL::runThreadCB() {
    if(m_logs.hasErrors()) return false;
    GString lRequest;
    readData(lRequest, 500);
    lRequest.print();
    sendHttp();
    return true;
}
//===============================================
void GOpenSSL::closeSSL() {
    m_logs.showErrors();
    m_logs.clearMap();
    if(m_ssl) {SSL_free(m_ssl); m_ssl = 0;}
    if(m_socket > 0) {close(m_socket); m_socket = 0;}
}
//===============================================
void GOpenSSL::cleanSSL() {
    if(m_socket > 0) {close(m_socket); m_socket = 0;}
    if(m_context) {SSL_CTX_free(m_context); m_context = 0;}
}
//===============================================
