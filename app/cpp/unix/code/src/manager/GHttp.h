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
    void initHttp();
    void initReason();

    void setModule(const GString& _module);
    void setVersion(const GString& _version);
    void setStatus(int _status);
    void setContentType(const GString& _contentType);
    void setContentText(const GString& _contentText);
    void setConnection(const GString& _connection);

    GString getResponseText() const;

    bool run();
    bool runResponse();

public:
    static const char* HTTP_1_0;
    static const char* HTTP_1_1;
    static const int HTTP_OK = 200;
    static const int HTTP_NOT_FOUND = 404;

private:
    GString m_module;
    GString m_version;
    int m_status;
    GString m_reason;
    GString m_contentType;
    int m_contentLength;
    GString m_contentText;
    GString m_connection;

    GString m_responseText;
};
//==============================================
#endif
//==============================================
