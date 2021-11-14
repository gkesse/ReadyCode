//===============================================
#ifndef _GCurl_
#define _GCurl_
//===============================================
#include "GInclude.h"
//===============================================
class GCurl {
public:
	typedef size_t (*onWriteFuncCB)(void* _content, size_t _size, size_t _nmemb, void* _params);

public:
    GCurl();
    ~GCurl();
    void init();
    void url(const std::string& _url);
    void writeFunc(onWriteFuncCB _onWriteFunc);
    void writeData();
    void perform();
    void clean();
    void print() const;
    size_t append(void* _content, size_t _size, size_t _nmemb, void* _params);

protected:
    CURL* m_curl;
    CURLcode m_code;
    std::string m_data;
};
//==============================================
#endif
//==============================================
