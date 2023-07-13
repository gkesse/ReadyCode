//===============================================
#ifndef _GOpenSSL_
#define _GOpenSSL_
//===============================================
#include "GObject.h"
//===============================================
class GOpenSSL : public GObject {
public:
    GOpenSSL();
    ~GOpenSSL();
    GString toHostname(const GString& _facade) const;
    int toPort(const GString& _facade) const;
    int toPortCpp() const;
    void checkErrors(GString& _data);
    bool initContext(SSL_CTX** _context);
    bool initSSL();
    void showCerts(SSL* _ssl);
    void closeSocket();
    void runServer();
    void runSocket();
    static void* onThreadCB(void* _params);
    static int onPasswordCB(char* _buf, int _size, int _rwflag, void* _password);
    static int onVerifyCB(int preverify_ok, X509_STORE_CTX *ctx);
    GString callSocket(const GString& _data, const GString& _facade = "facade");
    GString callServer(const GString& _data, const GString& _facade = "facade");
    GString callFacade(const GString& _module, const GString& _method, const GString& _data = "");
    void sendData(const GString& _data);
    GString readData();

private:
    static const int BUFFER_SIZE = 1024;        // 1 Ko
    static const int BUFFER_MAX = 1*1024*1024;  // 1 Mo

private:
    int m_socket;
    SSL* m_ssl;
    SSL_CTX* m_context;
};
//===============================================
#endif
//===============================================
