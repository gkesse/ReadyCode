//===============================================
#ifndef _GServer_
#define _GServer_
//===============================================
#include "GSocket2.h"
//===============================================
class GServer : public GSocket2 {
public:
    GServer();
    ~GServer();

    void setMethod(const GString2& _method);
    void setApiKey(const GString2& _apiKey);
    void setUsername(const GString2& _username);
    void setPassword(const GString2& _password);
    void setResponse(const GString2& _response);

    void run(int _argc, char** _argv);

    bool onRunServerTcp();

    bool onReadyApp();
    bool isReadyApp();
    bool readRequest();

    bool createData();

private:
    static constexpr const char* API_METHOD     = "RDVAPP";
    static constexpr const char* API_KEY        = "admin";
    static constexpr const char* API_USERNAME   = "admin";
    static constexpr const char* API_PASSWORD   = "admin";

    GString2 m_method;
    GString2 m_apiKey;
    GString2 m_username;
    GString2 m_password;
    GString2 m_request;
    GString2 m_response;

    int m_dataSize;
    int m_headerSize;
    int m_diffSize;
};
//==============================================
#endif
//==============================================
