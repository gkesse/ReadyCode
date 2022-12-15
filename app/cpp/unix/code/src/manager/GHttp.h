//===============================================
#ifndef _GHttp_
#define _GHttp_
//===============================================
#include "GManager.h"
//===============================================
class GHttp : public GManager {
public:
    GHttp(const GString& _code = "http");
    ~GHttp();
    //
    void setMethod(const GString& _method);
    void setUrl(const GString& _url);
    GString getUrl() const;
    void setVersion(const GString& _version);
    void setHostname(const GString& _hostname);
    void setPort(int _port);
    void setStatus(int _status);
    void setReason(const GString& _reason);
    void setContent(const GString& _content);
    void setContentType(const GString& _contentType);
    void setContentLength(int _contentLength);
    void setCacheControl(const GString& _cacheControl);
    void setUpgradeInsecureRequests(const GString& _upgradeInsecureRequests);
    void setUserAgent(const GString& _userAgent);
    void setAccept(const GString& _accept);
    void setAcceptEncoding(const GString& m_acceptEncoding);
    void setAcceptLanguage(const GString& _acceptLanguage);
    void setDate(const GString& _date);
    void setServer(const GString& _server);
    void setLastModified(const GString& _lastModified);
    void setConnection(const GString& _connection);
    //
    bool isLine(char _char, int& _index) const;
    bool isHeader(char _char, int& _index) const;
    //
    void runHttp();
    bool analyzeHeader();
    bool analyzeMethod();
    bool analyzeGet();
    bool analyzePost();
    void onGetIndex();
    //
    bool createGetData();

private:
    static const int HEADER_SIZE = 1024;
    //
    GString m_method;
    GString m_url;
    GString m_version;
    GString m_hostname;
    GString m_reason;
    GString m_contentType;
    GString m_date;
    GString m_servers;
    GString m_lastModified;
    GString m_content;
    GString m_cacheControl;
    GString m_upgradeInsecureRequests;
    GString m_userAgent;
    GString m_accept;
    GString m_acceptEncoding;
    GString m_acceptLanguage;
    GString m_connection;
    int m_status;
    int m_contentLength;
    int m_port;
};
//==============================================
#endif
//==============================================
