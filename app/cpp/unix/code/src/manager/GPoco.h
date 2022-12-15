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

    void setUri(const GString& _uri);
    bool extractCredentials();

    bool doGet();
    bool doGet(const GString& _uri);

    bool doRequest(Poco::Net::HTTPClientSession& _session, Poco::Net::HTTPRequest& _request, Poco::Net::HTTPResponse& _response);

private:
    GString m_uri;
    GString m_username;
    GString m_password;
    GString m_reason;
    int m_status;
};
//==============================================
#endif
//==============================================
