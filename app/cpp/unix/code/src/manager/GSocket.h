//===============================================
#ifndef _GSocket_
#define _GSocket_
//===============================================
#include "GObject.h"
//===============================================
class GSocket : public GObject {
public:
    GSocket();
    virtual ~GSocket();

    virtual GSocket* clone() const;

    void initSocket();
    int loadDomain() const;
    int loadType() const;
    int loadProtocol() const;
    int loadFamily() const;

    GString& getDataIn();
    GString& getDataOut();

    int readData(char* _data, int _size);
    bool readData(int _diffSize);
    bool readMethod();

    int sendData(const char* _data, int _size);
    bool sendResponse();

    bool runServer();
    bool runServerTcp();

    static void* onThreadCB(void* _params);
    bool runThreadCB();
    bool runThreadTcp();

    virtual bool onRunServerTcp();

protected:
    static const int BUFFER_SIZE = 1024;
    static const int METHOD_SIZE = 1024;

    bool m_isTestEnv;

    int m_domain;
    int m_type;
    int m_protocol;
    int m_family;
    int m_port;
    int m_backlog;

    int m_portProd;
    int m_portTest;

    GString m_module;
    GString m_hostname;
    GString m_startMessage;
    GString m_apiMethod;
    GString m_apiKey;
    GString m_apiUsername;
    GString m_apiPassword;

    GString m_serverIp;
    GString m_clientIp;
    GString m_domainName;
    GString m_typeName;
    GString m_protocolName;
    GString m_familyName;
    GString m_apiKeyProd;
    GString m_apiKeyTest;

    GString m_content;

    int m_socket;
    GString m_dataIn;
    GString m_dataOut;
};
//==============================================
#endif
//==============================================
