//===============================================
#ifndef _GPoco_
#define _GPoco_
//===============================================
#include "GObject.h"
//===============================================
class GPoco : public GObject {
public:
    GPoco(const GString& _code = "poco");
    ~GPoco();

    void initPoco();
    void initPoco(Poco::Net::HTTPServerRequest& _request);

    void setUri(const GString& _uri);

    int getPort() const;
    GString getMsgStarting() const;
    GString getMsgShutdown() const;

    bool extractCredentials();

    bool doGet();
    bool doGet(const GString& _uri);
    bool runServer(int _argc, char** _argv);
    void onRequest(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response);
    void onGet(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response);
    void onPost(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response);

    bool doRequest(Poco::Net::HTTPClientSession& _session, Poco::Net::HTTPRequest& _request, Poco::Net::HTTPResponse& _response);

private:
    GString m_uri;
    GString m_username;
    GString m_password;
    GString m_reason;
    GString m_method;
    GString m_host;
    GString m_contentType;
    GString m_charset;
    GString m_response;

    GString m_msgStarting;
    GString m_msgShutdown;

    int m_status;
    int m_port;
};
//==============================================
#endif
//==============================================
