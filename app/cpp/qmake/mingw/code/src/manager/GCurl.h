//===============================================
#ifndef _GCurl_
#define _GCurl_
//===============================================
#include "GObject.h"
//===============================================
class GCurl : public GObject {
public:
    GCurl(const GString& _code = "curl");
    ~GCurl();

public:
    void initModule();
    void cleanModule();

    void setContentType(const GString& _contentType);
    void setApiKey(const GString& _apiKey);
    void addHeader(const GString& _key, const GString& _value);
    void addForm(const GString& _key, const GString& _value);
    void addContent(const GString& _content);

    long getResponseCode() const;

    bool doCall(GString& _response);

private:
    void initCurl();
    bool onHttpPost(CURL* _curl, GString& _response);
    bool onHttpGet(CURL* _curl, GString& _response);
    bool onHttpsPost(CURL* _curl, GString& _response);
    bool onHttpsGet(CURL* _curl, GString& _response);
    static int onWrite(char* _data, size_t _size, size_t _nmemb, std::string* _writerData);

private:
    GString m_protocol;
    GString m_fullUrl;
    GString m_fullUrlHttp;
    GString m_fullUrlHttps;
    GString m_serverUrl;
    GString m_serverUrlHttp;
    GString m_serverUrlHttps;
    GString m_verb;
    GString m_verbPost;
    GString m_verbGet;
    GString m_method;
    GString m_methodAuth;
    GString m_apiBearer;
    bool m_hasCertificate;
    bool m_hasUserPass;
    bool m_isFullUrl;

    bool m_isTestEnv;

    GMap m_forms;
    GMap m_headers;
    GString m_contents;

    GString m_apiUsername;
    GString m_apiPassword;
    GString m_apiKey;
    GString m_apiKeyProd;
    GString m_apiKeyTest;
    GString m_certificateFile;
    GString m_cacertFile;
    GString m_contentType;
    GString m_url;
    GString m_urlProd;
    GString m_urlTest;

    long m_responseCode;

    GLog m_logs;
};
//==============================================
#endif
//==============================================
