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

    void addParam(const GString& _key, const GString& _value);
    bool doGet(const GString& _url, GString& _response);
    bool doPost(const GString& _url, GString& _response);

private:
    bool initGet(CURL*& _curl, const GString& _url, std::string* _buffer);
    bool initPost(CURL*& _curl, const GString& _url, std::string* _buffer);

    static int onGet(char* _data, size_t _size, size_t _nmemb, std::string* _writerData);

private:
    GMap m_params;
};
//==============================================
#endif
//==============================================
