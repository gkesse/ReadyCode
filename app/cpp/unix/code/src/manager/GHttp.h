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
    void setUrl(const GString2& _url);
    GString2 getUrl() const;
    void setVersion(const GString2& _version);
    void setHostname(const GString2& _hostname);
    void setPort(int _port);
    void setStatus(const GString2& _status);
    void setReason(const GString2& _reason);
    void setContentType(const GString2& _contentType);
    void setContentLength(int _contentLength);
    void setCacheControl(const GString2& _cacheControl);
    void setUpgradeInsecureRequests(const GString2& _upgradeInsecureRequests);
    void setUserAgent(const GString2& _userAgent);
    void setAccept(const GString2& _accept);
    void setAcceptEncoding(const GString2& m_acceptEncoding);
    void setAcceptLanguage(const GString2& _acceptLanguage);
    void setDate(const GString2& _date);
    void setServer(const GString2& _server);
    void setLastModified(const GString2& _lastModified);
    void setConnection(const GString2& _connection);
    //
    void onModule();
    void onIndex();
    void setSocket(int _socket);
    //
    bool getRequest(GString2& _request);
    bool getResponse(GString2& _response);

private:
    GString2 m_method;
    GString2 m_url;
    GString2 m_version;
    GString2 m_hostname;
    GString2 m_status;
    GString2 m_reason;
    GString2 m_contentType;
    GString2 m_date;
    GString2 m_server;
    GString2 m_lastModified;
    GString2 m_connection;
    GString2 m_content;
    GString2 m_cacheControl;
    GString2 m_upgradeInsecureRequests;
    GString2 m_userAgent;
    GString2 m_accept;
    GString2 m_acceptEncoding;
    GString2 m_acceptLanguage;
    int m_contentLength;
    int m_port;
    //
    int m_socket;
};
//==============================================
#endif
//==============================================