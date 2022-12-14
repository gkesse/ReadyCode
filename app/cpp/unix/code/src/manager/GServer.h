//===============================================
#ifndef _GServer_
#define _GServer_
//===============================================
#include "GSocket.h"
//===============================================
#define GSERVERI        GServer::Instance()
#define GRUN_SERVER     GSERVERI->run
//===============================================
class GServer : public GSocket {
public:
    GServer();
    ~GServer();

    GSocket* clone() const;
    static GServer* Instance();
    bool createDoms();

    void setResponse(const GString& _response);

    void setRequest(const GString& _request);
    GString getRequest() const;
    GString toResponse() const;

    void run(int _argc, char** _argv);

    bool onRunServerTcp();

    bool onReadyApp();
    bool onHttpApp();

    bool isReadyApp();
    bool readRequest();
    bool analyzeRequest();
    bool integrateErrors();
    bool createResponse();
    bool createData();

    bool addResponse(const GString& _data);

private:
    static GServer* m_instance;

    GString m_request;
    GString m_response;

    std::shared_ptr<GCode> m_domResponse;

    int m_dataSize;
    int m_headerSize;
    int m_diffSize;
};
//==============================================
#endif
//==============================================
