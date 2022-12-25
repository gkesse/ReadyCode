//===============================================
#ifndef _GPoco_
#define _GPoco_
//===============================================
#include "GObject.h"
//===============================================
class GCode;
//===============================================
class GPoco : public GObject {
public:
    GPoco(const GString& _code = "poco");
    ~GPoco();

public:
    void initModule();
    void cleanModule();

    bool initSSL();

    void setPoco(const GPoco& _poco);
    void setPoco(GPoco* _poco);

    int getPort() const;
    GString getProtocol() const;
    GString getStartMessage() const;
    GString getStopMessage() const;

    bool doGet(const GString& _url, GString& _response);
    bool runServer(int _argc, char** _argv);
    bool onRequest(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response);
    bool addResponse(const GString& _data);
    bool doResponse();
    bool onResponse(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response);

private:
    void initPoco();
    bool initPocoNoAuthentication(Poco::Net::HTTPServerRequest& _request);
    bool initPocoCertificate(Poco::Net::HTTPServerRequest& _request);

    void onGet(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response);
    void onPost(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response);
    void onRequestHttp(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response);
    void onRequestHttps(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response);

private:
    GString m_protocol;
    bool m_hasCertificate;

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

    GString m_headers;
    GString m_request;
    GString m_response;
    std::shared_ptr<GCode> m_responseXml;

    GString m_startMessage;
    GString m_stopMessage;

    GString m_privateKeyFile;
    GString m_certificateFile;

    int m_port;
    int m_portProd;
    int m_portTest;
    Poco::Net::HTTPResponse::HTTPStatus m_status;

    GLog m_logsTech;

public:
    GLog m_logs;
};
//==============================================
#endif
//==============================================
