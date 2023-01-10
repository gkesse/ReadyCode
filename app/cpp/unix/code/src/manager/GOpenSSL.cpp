//===============================================
#include "GOpenSSL.h"
#include "GCode.h"
#include "GApp.h"
//===============================================
GOpenSSL::GOpenSSL()
: GObject() {
    initOpenSSL();
}
//===============================================
GOpenSSL::~GOpenSSL() {

}
//===============================================
bool GOpenSSL::initOpenSSL() {
    m_ssl = 0;
    m_certificateFile = GAPP->getData("openssl", "certificate_file");
    m_privateKeyFile = GAPP->getData("openssl", "private_key_file");
    return true;
}
//===============================================
bool GOpenSSL::initModule() {
    SSL_load_error_strings();
    SSL_library_init();
    OpenSSL_add_all_algorithms();
    return true;
}
//===============================================
bool GOpenSSL::clearModule() {
    ERR_free_strings();
    EVP_cleanup();
    return true;
}
//===============================================
bool GOpenSSL::initSSL(int _socket) {
    SSL_CTX* lContext = SSL_CTX_new( SSLv23_server_method());
    SSL_CTX_set_options(lContext, SSL_OP_SINGLE_DH_USE);
    int lCertOk = SSL_CTX_use_certificate_file(lContext, m_certificateFile.c_str() , SSL_FILETYPE_PEM);
    if(lCertOk <= 0) {GERROR_ADD(eGERR, "Erreur lors de l'initialisation du certificat."); return false;}
    int lPrivOk = SSL_CTX_use_PrivateKey_file(lContext, m_privateKeyFile.c_str(), SSL_FILETYPE_PEM);
    if(lPrivOk <= 0) {GERROR_ADD(eGERR, "Erreur lors de l'initialisation de la clé privée."); return false;}

    m_ssl = SSL_new(lContext);
    SSL_set_fd(m_ssl, _socket );

    int lAcceptOk = SSL_accept(m_ssl);
    if(lAcceptOk <= 0) {
        SSL_shutdown(m_ssl);
        SSL_free(m_ssl);
        GERROR_ADD(eGERR, "Erreur lors de l'acceptation du certificat.");
        return false;
    }

    return true;
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
