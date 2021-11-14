//===============================================
#ifndef _GCurlUi_
#define _GCurlUi_
//===============================================
#include "GInclude.h"
//===============================================
class GCurlUi {
public:
    GCurlUi();
    virtual ~GCurlUi();
    static GCurlUi* Create(const std::string& key);
    virtual void run(int argc, char** argv);
    static size_t onWriteFunc(void* _content, size_t _size, size_t _nmemb, void* _params);
};
//==============================================
#endif
//==============================================
