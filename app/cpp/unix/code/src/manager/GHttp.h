//===============================================
#ifndef _GHttp_
#define _GHttp_
//===============================================
#include "GObject.h"
//===============================================
class GHttp : public GObject {
public:
    GHttp();
    ~GHttp();
    //
    void setMethod(const std::string& _method);
    void setUrl(const std::string& _url);
    void setVerion(const std::string& _version);
    void setStatus(const std::string& _status);
    void setReason(const std::string& _reason);
    void setContentType(const std::string& _contentType);
    void setContentLength(const std::string& _contentLength);
    void setContentLength(int _contentLength);
    void setDate(const std::string& _date);
    void setServer(const std::string& _server);
    void setLastModified(const std::string& _lastModified);
    void setConnection(const std::string& _connection);
    //
    bool getRequest(std::string& _request);
    bool getResponse(std::string& _response);

private:
    std::string m_method;
    std::string m_url;
    std::string m_version;
    std::string m_status;
    std::string m_reason;
    std::string m_contentType;
    std::string m_date;
    std::string m_server;
    std::string m_lastModified;
    std::string m_connection;
    std::string m_content;
    int m_contentLength;
};
//==============================================
#endif
//==============================================
