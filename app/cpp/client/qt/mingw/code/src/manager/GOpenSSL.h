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
    int toPort() const;
    void checkErrors(GString& _data);
    void showCerts(SSL* _ssl);
    bool initContext(SSL_CTX** _context);
    bool initSSL(SSL** _ssl, SSL_CTX* _context, SOCKET _socket);
    GString callServer(const GString& _data);
    GString callSocket(const GString& _data);
    GString callFacade(const GString& _module, const GString& _method, const GString& _data = "");
    void sendData(const GString& _data);
    GString readData();

private:
    static const int BUFFER_SIZE = 1*1024;      // l Ko
    static const int BUFFER_MAX = 1*1024*1024;  // l Mo

private:
    SSL* m_ssl;
};
//===============================================
#endif
//===============================================
