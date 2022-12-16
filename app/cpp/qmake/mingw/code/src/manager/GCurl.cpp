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
bool GCurl::initGet(CURL*& _curl, const GString& _url, std::string* _buffer) {
    CURLcode lCode;
    char lError[CURL_ERROR_SIZE];
    _curl = curl_easy_init();
    if(_curl == NULL) {GERROR_ADD(eGERR, "Erreur lors de l'initialisation de cURL."); return false;}
    lCode = curl_easy_setopt(_curl, CURLOPT_ERRORBUFFER, lError);
    if(lCode != CURLE_OK) {GERROR_ADD(eGERR, "Erreur lors de l'initialisation de cURL [%d].", lCode); return false;}
    lCode = curl_easy_setopt(_curl, CURLOPT_URL, _url.c_str());
    if(lCode != CURLE_OK) {GERROR_ADD(eGERR, "Erreur lors de l'initialisation de cURL [%s].", lError); return false;}
    lCode = curl_easy_setopt(_curl, CURLOPT_FOLLOWLOCATION, 1L);
    if(lCode != CURLE_OK) {GERROR_ADD(eGERR, "Erreur lors de l'initialisation de cURL [%s].", lError); return false;}
    lCode = curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, onGet);
    if(lCode != CURLE_OK) {GERROR_ADD(eGERR, "Erreur lors de l'initialisation de cURL [%s].", lError); return false;}
    lCode = curl_easy_setopt(_curl, CURLOPT_WRITEDATA, _buffer);
    if(lCode != CURLE_OK) {GERROR_ADD(eGERR, "Erreur lors de l'initialisation de cURL [%s].", lError); return false;}
    return true;
}
//===============================================
bool GCurl::initPost(CURL*& _curl, const GString& _url, std::string* _buffer) {
    CURLcode lCode;
    char lError[CURL_ERROR_SIZE];
    _curl = curl_easy_init();
    if(_curl == NULL) {GERROR_ADD(eGERR, "Erreur lors de l'initialisation de cURL."); return false;}
    lCode = curl_easy_setopt(_curl, CURLOPT_ERRORBUFFER, lError);
    if(lCode != CURLE_OK) {GERROR_ADD(eGERR, "Erreur lors de l'initialisation de cURL [%d].", lCode); return false;}
    lCode = curl_easy_setopt(_curl, CURLOPT_URL, _url.c_str());
    if(lCode != CURLE_OK) {GERROR_ADD(eGERR, "Erreur lors de l'initialisation de cURL [%s].", lError); return false;}
    lCode = curl_easy_setopt(_curl, CURLOPT_FOLLOWLOCATION, 1L);
    if(lCode != CURLE_OK) {GERROR_ADD(eGERR, "Erreur lors de l'initialisation de cURL [%s].", lError); return false;}
    lCode = curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, onGet);
    if(lCode != CURLE_OK) {GERROR_ADD(eGERR, "Erreur lors de l'initialisation de cURL [%s].", lError); return false;}
    lCode = curl_easy_setopt(_curl, CURLOPT_WRITEDATA, _buffer);
    if(lCode != CURLE_OK) {GERROR_ADD(eGERR, "Erreur lors de l'initialisation de cURL [%s].", lError); return false;}
    return true;
}
//===============================================
void GCurl::addParam(const GString& _key, const GString& _value) {
    m_params[_key] = _value;
}

//===============================================
bool GCurl::doGet(const GString& _url, GString& _response) {
    CURL* lCurl = NULL;
    CURLcode lCode;
    char lError[CURL_ERROR_SIZE];
    std::string lBuffer;
    if(!initGet(lCurl, _url, &lBuffer)) return false;
    lCode = curl_easy_perform(lCurl);
    curl_easy_cleanup(lCurl);
    if(lCode != CURLE_OK) {GERROR_ADD(eGERR, "Erreur lors de l'exécution de cURL [%s].", lError); return false;}
    _response = lBuffer;
    return true;
}
//===============================================
bool GCurl::doPost(const GString& _url, GString& _response) {
    CURL* lCurl = curl_easy_init();
    if(lCurl == NULL) {GERROR_ADD(eGERR, "Erreur lors de l'initialisation de cURL."); return false;}

    CURLcode lCode;
    char lError[CURL_ERROR_SIZE];

    lCode = curl_easy_setopt(lCurl, CURLOPT_URL, _url.c_str());
    if(lCode != CURLE_OK) {GERROR_ADD(eGERR, "Erreur lors de l'initialisation de CURLOPT_URL [%s].", lError); return false;}
    lCode = curl_easy_setopt(lCurl, CURLOPT_POSTFIELDS, m_params.toParams().c_str());
    if(lCode != CURLE_OK) {GERROR_ADD(eGERR, "Erreur lors de l'initialisation de CURLOPT_POSTFIELDS [%s].", lError); return false;}
    lCode = curl_easy_perform(lCurl);
    if(lCode != CURLE_OK) {GERROR_ADD(eGERR, "Erreur lors de l'exécution de cURL [%s].", lError); return false;}
    curl_easy_cleanup(lCurl);
    return true;
}
//===============================================
int GCurl::onGet(char* _data, size_t _size, size_t _nmemb, std::string* _writerData) {
    if(_writerData == NULL) return 0;
    _writerData->append(_data, _size * _nmemb);
    return _size * _nmemb;
}
//===============================================
