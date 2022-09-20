//===============================================
#ifndef _GServer_
#define _GServer_
//===============================================
#include "GModule2.h"
//===============================================
class GServer : public GModule2 {
public:
    GServer();
    ~GServer();

    void setMethod(const GString2& _method);
    void setApiKey(const GString2& _apiKey);
    void setUsername(const GString2& _username);
    void setPassword(const GString2& _password);

    void run(int _argc, char** _argv);

    static void* onThreadCB(void* _params);

    bool onReadyApp();
    bool isReadyApp();
    bool readRequest();

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

    int m_dataSize;
    int m_headerSize;
    int m_diffSize;
};
//==============================================
#endif
//==============================================
