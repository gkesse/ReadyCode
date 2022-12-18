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

    int getPort() const;
    GString getMsgStarting() const;
    GString getMsgShutdown() const;
    eGModule getModule() const;

    bool doGet(const GString& _url, GString& _response);
    bool runServer(int _argc, char** _argv);
    void onRequest(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response);

private:
    void initPoco();
    bool initPoco(Poco::Net::HTTPServerRequest& _request);

    void onGet(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response);
    void onPost(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response);
    void onRequestHttp(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response);
    void onRequestHttps(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response);

private:
    eGModule m_module;

    GString m_username;
    GString m_password;
    GString m_method;
    GString m_uri;

    GString m_contentType;
    GString m_charset;

    GString m_request;
    GString m_response;

    GString m_msgStarting;
    GString m_msgShutdown;

    int m_port;
    int m_status;
};
//==============================================
#endif
//==============================================
