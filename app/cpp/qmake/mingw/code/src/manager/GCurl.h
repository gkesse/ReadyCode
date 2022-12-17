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
    bool initCurl();
    bool cleanCurl();

    void addHeader(const GString& _key, const GString& _value);
    void addForm(const GString& _key, const GString& _value);
    void addContent(const GString& _content);
    bool doGet(const GString& _url, GString& _response);
    bool doPost(const GString& _url, GString& _response);

private:
    static int onWrite(char* _data, size_t _size, size_t _nmemb, std::string* _writerData);

private:
    GMap m_forms;
    GMap m_headers;
    GString m_contents;
};
//==============================================
#endif
//==============================================
