//===============================================
#ifndef _GPoco_
#define _GPoco_
//===============================================
#include "GObject.h"
//===============================================
class GPoco : public GObject {
public:
    enum eGModule {
        UNKNOWN
        , POCO_SERVER_HTTP
        , POCO_SERVER_HTTPS
    };

    enum eGMode {
        MODE_NO_AUTHENTICATION
        , MODE_USERNAME_PASSWORD
        , MODE_API_KEY
        , MODE_CERTIFICATE
    };

public:
    GPoco(const GString& _code = "poco");
    ~GPoco();

public:
    void initModule();
    void cleanModule();

    void initSSL();

    void setPoco(const GPoco& _poco);
    void setPoco(GPoco* _poco);
    void setModule(eGModule _module);
    void setMode(eGMode _mode);

    int getPort() const;
    GString getStartMessage() const;
    GString getStopMessage() const;
    eGModule getModule() const;

    bool doGet(const GString& _url, GString& _response);
    bool runServer(int _argc, char** _argv);
    void onRequest(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response);

private:
    void initPoco();
    bool initPoco(Poco::Net::HTTPServerRequest& _request);
    bool initPocoNoAuthentication(Poco::Net::HTTPServerRequest& _request);
    bool initPocoCertificate(Poco::Net::HTTPServerRequest& _request);
    void initSSLNoAuthentication();
    void initSSLUsernamePassword();
    void initSSLApiKey();
    void initSSLCertificate();

    void onGet(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response);
    void onPost(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response);
    void onRequestHttp(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response);
    void onRequestHttps(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response);

private:
    eGModule m_module;
    bool m_isTestEnv;

    GString m_apiKey;
    GString m_apiKeyProd;
    GString m_apiKeyTest;
    GString m_apiUsername;
    GString m_apiPassword;
    GString m_method;
    GString m_uri;

    GString m_contentType;
    GString m_charset;

    GString m_request;
    GString m_response;

    GString m_startMessage;
    GString m_stopMessage;

    GString m_privatekeyFile;
    GString m_certificateFile;

    int m_port;
    int m_portProd;
    int m_portTest;
    int m_status;

    eGMode m_mode;
};
//==============================================
#endif
//==============================================
