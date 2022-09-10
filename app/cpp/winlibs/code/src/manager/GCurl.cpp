//===============================================
#include "GCurl.h"
//===============================================
GCurl::GCurl()
: GObject()
, m_url("")
, m_option(0)
{

}
//===============================================
GCurl::~GCurl()
{

}
//===============================================
void GCurl::initModule()
{

}
//===============================================
void GCurl::cleanModule()
{

}
//===============================================
void GCurl::setUrl(const std::string& _url)
{
    m_url = _url;
}
//===============================================
void GCurl::setOption(int _option)
{
    m_option = _option;
}
//===============================================
bool GCurl::getInfo(std::string& _info)
{
    CURL* lCurl;
    CURLcode lRes;

    lCurl = curl_easy_init();
    if(lCurl) {
        curl_easy_setopt(lCurl, CURLOPT_URL, m_url.c_str());
        lRes = curl_easy_perform(lCurl);

        if(CURLE_OK == lRes)
        {
            char* lInfo;
            lRes = curl_easy_getinfo(lCurl, (CURLINFO)m_option, &lInfo);

            if((CURLE_OK == lRes) && lInfo)
            {
                _info = lInfo;
                return true;
            }
        }

        curl_easy_cleanup(lCurl);
    }

    return false;
}
//===============================================
