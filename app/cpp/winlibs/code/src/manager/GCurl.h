//===============================================
#ifndef _GCurl_
#define _GCurl_
//===============================================
#include "GObject.h"
//===============================================
class GCurl : public GObject
{
public:
    GCurl();
    ~GCurl();
    void initModule();
    void cleanModule();
    void setUrl(const std::string& _url);
    void setOption(int _option);
    bool getInfo(std::string& _info);

private:
    std::string m_url;
    int m_option;
};
//===============================================
#endif
//===============================================
