//===============================================
#ifndef _GOpenSSL_
#define _GOpenSSL_
//===============================================
#include "GObject.h"
//===============================================
class GOpenSSL : public GObject {
public:
    typedef struct _sGData sGData;

public:
    GOpenSSL();
    ~GOpenSSL();

    void initModule();
    void clearModule();

    void setOpenSSL(const GOpenSSL& _obj);
    void setVerify(const GString& _verify);
    void setDepth(int _depth);
    void setStartMessage(const GString& _startMessage);
    void setStopMessage(const GString& _startMessage);
    void setHostname(const GString& _hostname);
    void setPort(int _port);
    void setBacklog(int _backlog);
    void setHasGenerateCertificate(bool _hasGenerateCertificate);
    void setCertificateFile(const GString& _certificateFile);
    void setPrivateKeyFile(const GString& _privateKeyFile);

    void setCountry(const GString& _country);
    void setLocality(const GString& _locality);
    void setState(const GString& _state);
    void setOrganisation(const GString& _organisation);
    void setOrganisationalUnit(const GString& _organisationalUnit);
    void setCommonName(const GString& _commonName);

    bool generatePrivateKey();
    bool generateCertificate();
    bool generateRSA();

    bool readData(GString& _dataOut);
    bool sendData(const GString& _dataIn);

    bool run();
    static int onPasswordCB(char* _buf, int _size, int _rwflag, void* _password);
    static void* onThreadCB(void* _params);
    bool initSSL();
    static int onPeerClientCB(int _preverifyOk, X509_STORE_CTX* _ctx);
    bool acceptSSL();
    bool runThreadCB();
    void closeSSL();
    void cleanSSL();

private:
    static const int BUFFER_SIZE = 1024;
    static const int BUFFER_MAX = 1024*1024;

    static int m_dataIndex;

    SSL* m_ssl;
    EVP_PKEY* m_privateKey;
    X509* m_certificate;
    SSL_CTX* m_context;

    GString m_verify;
    GString m_startMessage;
    GString m_stopMessage;

    GString m_hostname;
    GString m_certificateFile;
    GString m_privateKeyFile;
    GString m_rsaKey;

    GString m_country;
    GString m_state;
    GString m_locality;
    GString m_organisation;
    GString m_organisationalUnit;
    GString m_commonName;

    int m_socket;
    int m_port;
    int m_backlog;
    int m_depth;
    bool m_hasGenerateCertificate;
};
//==============================================
#endif
//==============================================
