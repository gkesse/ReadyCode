//===============================================
#ifndef _GCurl_
#define _GCurl_
//===============================================
#include "GObject.h"
//===============================================
class GCurl : public GObject {
public:
    enum eGMode {
        MODE_NO_AUTENTICATION
        , MODE_USERNAME_PASSWORD
        , MODE_API_KEY
        , MODE_CERTIFICATE
    };

public:
    GCurl(const GString& _code = "curl");
    ~GCurl();

public:
    void initModule();
    void cleanModule();

    void setMode(eGMode _mode);
    void setContentType(const GString& _contentType);
    void setApiKey(const GString& _apiKey);

    long getResponseCode() const;

    void addHeader(const GString& _key, const GString& _value);
    void addForm(const GString& _key, const GString& _value);
    void addContent(const GString& _content);

    bool doGet(const GString& _url, GString& _response);
    bool doPost(const GString& _url, GString& _response);

private:
    void initCurl();
    bool doGetNoAuthentication(const GString& _url, GString& _response);
    bool doGetUsernamePassword(const GString& _url, GString& _response);
    bool doGetApiKey(const GString& _url, GString& _response);
    bool doGetCertificate(const GString& _url, GString& _response);
    static int onWrite(char* _data, size_t _size, size_t _nmemb, std::string* _writerData);

private:
    eGMode m_mode;

    GMap m_forms;
    GMap m_headers;
    GString m_contents;

    GString m_username;
    GString m_password;
    GString m_apiKey;
    GString m_certificateFile;
    GString m_certificatePath;
    GString m_contentType;

    long m_responseCode;
};
//==============================================
#endif
//==============================================
