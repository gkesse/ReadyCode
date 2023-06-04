//===============================================
#ifndef _GClient_
#define _GClient_
//===============================================
#include "GSocket.h"
//===============================================
#define GCLIENTI        GClient::Instance()
#define GCALL_SERVER    GCLIENTI->callServer
//===============================================
class GClient : public GSocket {
public:
    GClient();
    ~GClient();

    static GClient* Instance();

    void setRequest(const GString& _request);

    GString callServer(const GString& _modules, const GString& _method, const GString& _data = "");

    bool createData();
    bool onCallServer();
    bool onReadyApp();
    bool isReadyApp();
    bool readResponse();
    bool loadErrors();

private:
    static const int BUFFER_SIZE = 1024;
    static const int METHOD_SIZE = 1024;

    static GClient* m_instance;

    GString m_request;
    GString m_response;
    GString m_dataOut;
    GString m_dataIn;

    int m_dataSize;
    int m_headerSize;
    int m_diffSize;
};
//==============================================
#endif
//==============================================
