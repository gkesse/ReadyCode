//===============================================
#ifndef _GOpenSSL_
#define _GOpenSSL_
//===============================================
#include "GObject.h"
//===============================================
class GOpenSSL : public GObject {
public:
    GOpenSSL(const GString& _code = "openssl");
    ~GOpenSSL();

    bool initModule();
    bool clearModule();
    bool initSSL(int _socket);
    bool readData(GString& _dataOut, int _size);
    bool sendData(const GString& _dataIn);

protected:
    bool initOpenSSL();

protected:
    static const int BUFFER_SIZE = 1024;

protected:
    GString m_certificateFile;
    GString m_privateKeyFile;
    SSL* m_ssl;
};
//==============================================
#endif
//==============================================
