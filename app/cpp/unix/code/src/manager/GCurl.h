//===============================================
#ifndef _GCurl_
#define _GCurl_
//===============================================
#include "GObject.h"
//===============================================
class GCurl : public GObject {
public:
    GCurl();
    ~GCurl();

    bool initGet(CURL*& _curl, const GString& _url, std::string* _buffer);
    bool doGet(const GString& _url, GString& _response);
    static int onWrite(char* _data, size_t _size, size_t _nmemb, std::string* _writerData);
};
//==============================================
#endif
//==============================================
