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

    static constexpr char* METHOD_RDVAPP        = "RDVAPP";
    static constexpr char* METHOD_HTTP_GET      = "GET";
    static constexpr char* METHOD_HTTP_POST     = "POST";

public:
    GSocket();
    ~GSocket();

    void setModule(eGModule _module);
    void setProtocol(eGProtocol _protocol);

    bool runServer();

    virtual GString getRequest() const;
    virtual bool addResponse(const GString& _data);

protected:
    void initSocket();
    GSocket* createSocket();

    GString& getDataIn();
    GString& getDataOut();

    int readData(char* _data, int _size);
    bool readData(int _diffSize);
    int sendData(const char* _data, int _size);

    bool runServerTcp();
    static void* onThreadCB(void* _params);
    virtual bool runThreadCB();

    bool sendResponse();

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
