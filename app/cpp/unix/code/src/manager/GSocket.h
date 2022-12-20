//===============================================
#ifndef _GSocket_
#define _GSocket_
//===============================================
#include "GObject.h"
//===============================================
class GSocket : public GObject {
public:
    enum eGModule {
        SOCKET_SERVER_UDP
        , SOCKET_SERVER_TCP
    };

    enum eGProtocol {
        PROTOCOL_ECHO
        , PROTOCOL_RDVAPP
        , PROTOCOL_HTTP
    };

    static const char* METHOD_RDVAPP;
    static const char* METHOD_HTTP_GET;
    static const char* METHOD_HTTP_POST;

public:
    GSocket();
    ~GSocket();

    void setModule(eGModule _module);
    void setProtocol(eGProtocol _protocol);
    GSocket* createSocket();
    bool runServer();

    virtual void setRequest(const GString& _request);
    virtual GString getRequest() const;
    virtual bool addResponse(const GString& _data);
    virtual bool createResponse();
    virtual GString getResponse() const;

protected:
    void initSocket();
    bool runServerTcp();
    static void* onThreadCB(void* _params);
    bool readData(GString& _dataOut, int _size);
    int sendData(const GString& _dataIn, int _size);
    bool sendResponse();

    virtual bool runThreadCB();

protected:
    static const int BUFFER_SIZE = 1024;
    static const int METHOD_SIZE = 1024;

    eGModule m_module;
    eGProtocol m_protocol;

    bool m_isTestEnv;

    int m_backlog;
    int m_port;
    int m_portProd;
    int m_portTest;

    GString m_hostname;
    GString m_startMessage;
    GString m_stopMessage;

    GString m_serverIp;
    GString m_clientIp;

    int m_socket;
    GString m_dataIn;
    GString m_dataOut;
};
//==============================================
#endif
//==============================================
