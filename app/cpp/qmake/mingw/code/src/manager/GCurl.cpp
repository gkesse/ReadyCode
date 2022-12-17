//===============================================
#include "GCurl.h"
#include "GLog.h"
#include "GMap.h"
//===============================================
GCurl::GCurl(const GString& _code)
: GObject(_code) {

}
//===============================================
GCurl::~GCurl() {

}
//===============================================
bool GCurl::initCurl() {
    curl_global_init(CURL_GLOBAL_DEFAULT);
    return true;
}
//===============================================
bool GCurl::cleanCurl() {
    curl_global_cleanup();
    return true;
}
//===============================================
void GCurl::addHeader(const GString& _key, const GString& _value) {
    m_headers[_key] = _value;
}
//===============================================
void GCurl::addForm(const GString& _key, const GString& _value) {
    m_forms[_key] = _value;
}
//===============================================
void GCurl::addContent(const GString& _content) {
    m_contents += _content;
}
//===============================================
bool GCurl::doGet(const GString& _url, GString& _response) {
    char lError[CURL_ERROR_SIZE];
    std::string lBuffer;

    CURL* lCurl = curl_easy_init();

    curl_easy_setopt(lCurl, CURLOPT_ERRORBUFFER, lError);
    curl_easy_setopt(lCurl, CURLOPT_URL, _url.c_str());
    curl_easy_setopt(lCurl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(lCurl, CURLOPT_WRITEFUNCTION, onWrite);
    curl_easy_setopt(lCurl, CURLOPT_WRITEDATA, &lBuffer);
    curl_easy_setopt (lCurl, CURLOPT_VERBOSE, 0L);

    curl_easy_perform(lCurl);
    curl_easy_cleanup(lCurl);

    _response = lBuffer;
    return true;
}
//===============================================
bool GCurl::doPost(const GString& _url, GString& _response) {
    char lError[CURL_ERROR_SIZE];
    std::string lBuffer;

    CURL* lCurl = curl_easy_init();

    m_contents +=  m_forms.toParams();

    struct curl_slist *hs=NULL;
    hs = curl_slist_append(hs, "Content-Type: application/xml");
    curl_easy_setopt(lCurl, CURLOPT_HTTPHEADER, hs);

    curl_easy_setopt(lCurl, CURLOPT_ERRORBUFFER, lError);
    curl_easy_setopt(lCurl, CURLOPT_URL, _url.c_str());
    curl_easy_setopt(lCurl, CURLOPT_POSTFIELDS, m_contents.c_str());
    curl_easy_setopt(lCurl, CURLOPT_POSTFIELDSIZE, m_contents.size());
    curl_easy_setopt(lCurl, CURLOPT_WRITEFUNCTION, onWrite);
    curl_easy_setopt(lCurl, CURLOPT_WRITEDATA, &lBuffer);
    curl_easy_setopt (lCurl, CURLOPT_VERBOSE, 0L);

    curl_easy_perform(lCurl);
    curl_easy_cleanup(lCurl);

    _response = lBuffer;
    return true;
}
//===============================================
int GCurl::onWrite(char* _data, size_t _size, size_t _nmemb, std::string* _writerData) {
    if(_writerData == NULL) return 0;
    _writerData->append(_data, _size * _nmemb);
    return _size * _nmemb;
}
//===============================================
