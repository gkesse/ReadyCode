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

public:
    int getPort() const;
    GString getMsgStarting() const;
    GString getMsgShutdown() const;

    bool doGet(const GString& _url, GString& _response);
    bool runServer(int _argc, char** _argv);

private:
    void initPoco();
    bool initPoco(Poco::Net::HTTPServerRequest& _request);

    void onRequest(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response);
    void onGet(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response);
    void onPost(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response);

private:
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
