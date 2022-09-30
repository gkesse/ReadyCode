//===============================================
#ifndef _GClient_
#define _GClient_
//===============================================
#include "GSocket2.h"
//===============================================
#define GCLIENTI        GClient::Instance()
#define GCALL_SERVER    GCLIENTI->callServer
//===============================================
class GClient : public GSocket2 {
public:
    GClient();
    ~GClient();

    static GClient* Instance();

    void setMethod(const GString& _method);
    void setApiKey(const GString& _apiKey);
    void setUsername(const GString& _username);
    void setPassword(const GString& _password);
    void setRequest(const GString& _request);

    GString callServer(const GString& _module, const GString& _method, const GString& _data = "");

    bool createData();
    bool onCallServer();
    bool onReadyApp();
    bool isReadyApp();
    bool readResponse();
    bool loadErrors();

private:
    static const int BUFFER_SIZE = 1024;
    static const int METHOD_SIZE = 1024;

    static constexpr const char* API_METHOD     = "RDVAPP";
    static constexpr const char* API_KEY        = "admin";
    static constexpr const char* API_USERNAME   = "admin";
    static constexpr const char* API_PASSWORD   = "admin";

    static GClient* m_instance;

    GString m_method;
    GString m_apiKey;
    GString m_username;
    GString m_password;
    GString m_request;
    GString m_response;

    int m_dataSize;
    int m_headerSize;
    int m_diffSize;
};
//==============================================
#endif
//==============================================
