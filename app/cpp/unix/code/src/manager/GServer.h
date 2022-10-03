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
    void initServer();
    bool createDoms();

    void setResponse(const GString& _response);

    GString getRequest() const;

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
    static constexpr const char* API_METHOD     = "RDVAPP";
    static constexpr const char* API_KEY        = "admin";
    static constexpr const char* API_USERNAME   = "admin";
    static constexpr const char* API_PASSWORD   = "admin";

    static GServer* m_instance;

    GString m_apiMethod;
    GString m_apiKey;
    GString m_apiUsername;
    GString m_apiPassword;
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
