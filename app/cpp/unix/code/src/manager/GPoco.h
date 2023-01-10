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
    GPoco();
    ~GPoco();

public:
    void initModule();
    void cleanModule();

    void initPoco();
    bool initSSL();

    void setPoco(const GPoco& _poco);
    void setProtocol(const GString& _protocol);
    void setVerb(const GString& _verb);
    void setPort(int _port);
    void setHasUserPass(bool _hasUserPass);
    void setHasContentType(bool _hasContentType);

    int getPort() const;
    GString getProtocol() const;
    GString getStartMessage() const;
    GString getStopMessage() const;

    bool run(int _argc, char** _argv);
    bool onRequest(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response);
    bool doResponse();
    bool onResponse(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response);

private:
    bool onHttpPostUsernamePassword(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response);
    bool onHttpPostNoUsernamePassword(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response);
    bool onHttpGetUsernamePassword(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response);
    bool onGetNoUsernamePasswordContentType(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response);
    bool onGetNoUsernamePasswordNoContentType(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response);
    bool onGetXml(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response);

    bool onHttpsPostCertificateUsernamePassword(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response);
    bool onHttpsPostCertificateNoUsernamePassword(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response);
    bool onHttpsGetCertificateUsernamePassword(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response);
    bool onHttpsGetCertificateNoUsernamePassword(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response);
    bool onHttpsGetNoCertificateUsernamePassword(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response);
    bool onHttpsGetNoCertificateNoUsernamePassword(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response);


protected:
    GString m_protocol;
    GString m_verb;
    bool m_hasUserPass;
    bool m_hasContentType;

    bool m_isTestEnv;

    GString m_apiKey;
    GString m_apiKeyProd;
    GString m_apiKeyTest;
    GString m_apiUsername;
    GString m_apiPassword;
    GString m_method;

    GString m_charset;
    GString m_contentType;

    GString m_headers;
    GString m_request;
    GString m_response;

    GString m_startMessage;
    GString m_stopMessage;

    GString m_privateKeyFile;
    GString m_certificateFile;
    GString m_cacertFile;

    int m_port;
    int m_portProd;
    int m_portTest;
    Poco::Net::HTTPResponse::HTTPStatus m_status;

    GLog m_logsTech;
};
//==============================================
#endif
//==============================================
