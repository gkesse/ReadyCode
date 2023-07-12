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
    int toPort() const;
    bool checkErrors(const GString& _data);
    GString postHttpFacade(const GString& _module, const GString& _method, const GString& _data = "");
    GString postHttp(const GString& _dataIn);
    static int onWrite(char* _data, size_t _size, size_t _nmemb, std::string* _writerData);

private:
    long m_codeHttp;
};
//===============================================
#endif
//===============================================
