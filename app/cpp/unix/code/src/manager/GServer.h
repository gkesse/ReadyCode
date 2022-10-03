//===============================================
#ifndef _GServer_
#define _GServer_
//===============================================
#include "GSocket.h"
//===============================================
#define GSERVERI    GServer::Instance()
//===============================================
class GServer : public GSocket {
public:
    GServer();
    ~GServer();

    bool createDoms();
    static GServer* Instance();
    GSocket* clone() const;

    void setMethod(const GString& _method);
    void setApiKey(const GString& _apiKey);
    void setUsername(const GString& _username);
    void setPassword(const GString& _password);
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

    GString m_method;
    GString m_apiKey;
    GString m_username;
    GString m_password;
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
