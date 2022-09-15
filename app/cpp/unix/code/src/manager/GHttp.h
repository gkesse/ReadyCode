//===============================================
#ifndef _GHttp_
#define _GHttp_
//===============================================
#include "GObject.h"
#include "GString2.h"
//===============================================
class GHttp : public GObject {
public:
    GHttp();
    ~GHttp();
    //
    void setMethod(const GString2& _method);
    void setUrl(const std::string& _url);
    void setVersion(const std::string& _version);
    void setHostname(const std::string& _hostname);
    void setPort(int _port);
    void setStatus(const std::string& _status);
    void setReason(const std::string& _reason);
    void setContentType(const std::string& _contentType);
    void setContentLength(int _contentLength);
    void setCacheControl(const std::string& _cacheControl);
    void setUpgradeInsecureRequests(const std::string& _upgradeInsecureRequests);
    void setUserAgent(const std::string& _userAgent);
    void setAccept(const std::string& _accept);
    void setAcceptEncoding(const std::string& m_acceptEncoding);
    void setAcceptLanguage(const std::string& _acceptLanguage);
    void setDate(const std::string& _date);
    void setServer(const std::string& _server);
    void setLastModified(const std::string& _lastModified);
    void setConnection(const std::string& _connection);
    //
    bool getRequest(std::string& _request);
    bool getResponse(std::string& _response);

private:
    GString2 m_method;
    std::string m_url;
    std::string m_version;
    std::string m_hostname;
    std::string m_status;
    std::string m_reason;
    std::string m_contentType;
    std::string m_date;
    std::string m_server;
    std::string m_lastModified;
    std::string m_connection;
    std::string m_content;
    std::string m_cacheControl;
    std::string m_upgradeInsecureRequests;
    std::string m_userAgent;
    std::string m_accept;
    std::string m_acceptEncoding;
    std::string m_acceptLanguage;
    int m_contentLength;
    int m_port;
};
//==============================================
#endif
//==============================================
