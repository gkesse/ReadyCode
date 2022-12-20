//===============================================
#ifndef _GSocket_
#define _GSocket_
//===============================================
#include "GObject.h"
//===============================================
class GSocket : public GObject {
public:
    enum eGModule {
        SOCKET_CLIENT_TCP
        , SOCKET_CLIENT_UDP
    };

    enum eGProtocol {
        PROTOCOL_ECHO
        , PROTOCOL_RDVAPP
        , PROTOCOL_HTTP
    };

public:
    GSocket(const GString& _code = "socket");
    virtual ~GSocket();

    void setModule(eGModule _module);
    void setProtocol(eGProtocol _protocol);
    bool callServer(const GString& _dataIn, GString& _dataOut);

protected:
    void initSocket();
    void setSocket(const GSocket& _socket);
    void setSocket(GSocket* _socket);
    GSocket* createSocket();
    bool callServerTcp(const GString& _dataIn, GString& _dataOut);
    bool callServerUdp(const GString& _dataIn, GString& _dataOut);
    virtual bool onCallServer(const GString& _dataIn, GString& _dataOut);
    bool sendData(const GString& _dataIn);
    bool readData(GString& _dataOut, int _size);

protected:
    static const int BUFFER_SIZE = 1024;
    static const int METHOD_SIZE = 1024;

    eGModule m_module;
    eGProtocol m_protocol;

    bool m_isTestEnv;

    int m_port;
    int m_portProd;
    int m_portTest;
    int m_backlog;


    GString m_hostname;
    GString m_serverIp;
    GString m_clientIp;
    GString m_apiMethod;
    GString m_apiKey;
    GString m_apiKeyProd;
    GString m_apiKeyTest;
    GString m_apiUsername;
    GString m_apiPassword;

    SOCKET m_socket;
};
//==============================================
#endif
//==============================================
