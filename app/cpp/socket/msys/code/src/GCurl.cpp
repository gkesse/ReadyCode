//===============================================
#include "GCurl.h"
//===============================================
GCurl::GCurl() {
    m_curl = 0;
    m_code = CURLcode::CURL_LAST;
}
//===============================================
GCurl::~GCurl() {

}
//===============================================
void GCurl::init() {
    m_curl = curl_easy_init();
}
//===============================================
void GCurl::url(const std::string& _url) {
    curl_easy_setopt(m_curl, CURLOPT_URL, _url.c_str());
}
//===============================================
void GCurl::writeFunc(onWriteFuncCB _onWriteFunc) {
    curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, _onWriteFunc);
}
//===============================================
void GCurl::writeData() {
    curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, &m_data);
}
//===============================================
void GCurl::perform() {
    m_code = curl_easy_perform(m_curl);
}
//===============================================
void GCurl::clean() {
    curl_easy_cleanup(m_curl);
}
//===============================================
void GCurl::print() const {
    std::cout << m_data << "\n";
}
//===============================================
size_t GCurl::append(void* _content, size_t _size, size_t _nmemb, void* _params) {
    std::string* lData = (std::string*)_params;
    char* lContent = (char*)_content;
    lData->append(lContent, _size * _nmemb);
    return _size * _nmemb;
}
//===============================================
