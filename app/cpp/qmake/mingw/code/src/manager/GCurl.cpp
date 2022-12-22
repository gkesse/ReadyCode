//===============================================
#include "GCurl.h"
#include "GMap.h"
#include "GCode.h"
#include "GLog.h"
//===============================================
GCurl::GCurl(const GString& _code)
: GObject(_code) {
    createDoms();
    initCurl();
}
//===============================================
GCurl::~GCurl() {

}
//===============================================
void GCurl::initCurl() {
    m_mode              = GCurl::MODE_NO_AUTENTICATION;
    m_contentType       = "application/xml";
    m_username          = m_dom->getData("curl", "username");
    m_password          = m_dom->getData("curl", "password");
    m_apiKey            = m_dom->getData("curl", "api_key");
    m_certificateFile   = m_dom->getData("curl", "certificate_file");
}
//===============================================
void GCurl::initModule() {
    curl_global_init(CURL_GLOBAL_DEFAULT);
}
//===============================================
void GCurl::cleanModule() {
    curl_global_cleanup();
}
//===============================================
void GCurl::setMode(GCurl::eGMode _mode) {
    m_mode = _mode;
}
//===============================================
void GCurl::setContentType(const GString& _contentType) {
    m_contentType = _contentType;
}
//===============================================
void GCurl::setApiKey(const GString& _apiKey) {
    m_apiKey = _apiKey;
}
//===============================================
long GCurl::getResponseCode() const {
    return m_responseCode;
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
    if(m_mode == GCurl::MODE_NO_AUTENTICATION) return doGetNoAuthentication(_url, _response);
    if(m_mode == GCurl::MODE_USERNAME_PASSWORD) return doGetUsernamePassword(_url, _response);
    if(m_mode == GCurl::MODE_API_KEY) return doGetApiKey(_url, _response);
    if(m_mode == GCurl::MODE_CERTIFICATE) return doGetCertificate(_url, _response);
    return doGetNoAuthentication(_url, _response);
}
//===============================================
bool GCurl::doGetNoAuthentication(const GString& _url, GString& _response) {
    char lError[CURL_ERROR_SIZE];
    std::string lBuffer;

    CURL* lCurl = curl_easy_init();

    addHeader("Content-Type", m_contentType);

    struct curl_slist* lHeaders = NULL;
    lHeaders = m_headers.toHeaders(lCurl, lHeaders);
    curl_easy_setopt(lCurl, CURLOPT_HTTPHEADER, lHeaders);

    curl_easy_setopt(lCurl, CURLOPT_ERRORBUFFER, lError);
    curl_easy_setopt(lCurl, CURLOPT_URL, _url.c_str());
    curl_easy_setopt(lCurl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(lCurl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(lCurl, CURLOPT_SSL_VERIFYHOST, 0L);
    curl_easy_setopt(lCurl, CURLOPT_WRITEFUNCTION, onWrite);
    curl_easy_setopt(lCurl, CURLOPT_WRITEDATA, &lBuffer);
    curl_easy_setopt(lCurl, CURLOPT_VERBOSE, 0L);

    CURLcode lCurlOk = curl_easy_perform(lCurl);
    if(lCurlOk != CURLE_OK) {GLOGT(eGMSG, "Erreur lors de la connexion au serveur.\n%s", curl_easy_strerror(lCurlOk));}
    curl_easy_getinfo(lCurl, CURLINFO_RESPONSE_CODE, &m_responseCode);
    curl_easy_cleanup(lCurl);
    curl_slist_free_all(lHeaders);

    _response = lBuffer;
    return true;
}
//===============================================
bool GCurl::doGetUsernamePassword(const GString& _url, GString& _response) {
    char lError[CURL_ERROR_SIZE];
    std::string lBuffer;

    CURL* lCurl = curl_easy_init();

    addHeader("Content-Type", m_contentType);

    struct curl_slist* lHeaders = NULL;
    lHeaders = m_headers.toHeaders(lCurl, lHeaders);
    curl_easy_setopt(lCurl, CURLOPT_HTTPHEADER, lHeaders);

    curl_easy_setopt(lCurl, CURLOPT_ERRORBUFFER, lError);
    curl_easy_setopt(lCurl, CURLOPT_URL, _url.c_str());
    curl_easy_setopt(lCurl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(lCurl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(lCurl, CURLOPT_SSL_VERIFYHOST, 0L);
    curl_easy_setopt(lCurl, CURLOPT_USERNAME, m_username.c_str());
    curl_easy_setopt(lCurl, CURLOPT_PASSWORD, m_password.c_str());
    curl_easy_setopt(lCurl, CURLOPT_WRITEFUNCTION, onWrite);
    curl_easy_setopt(lCurl, CURLOPT_WRITEDATA, &lBuffer);
    curl_easy_setopt(lCurl, CURLOPT_VERBOSE, 0L);

    CURLcode lCurlOk = curl_easy_perform(lCurl);
    if(lCurlOk != CURLE_OK) {GLOGT(eGMSG, "Erreur lors de la connexion au serveur.\n%s", curl_easy_strerror(lCurlOk));}
    curl_easy_getinfo(lCurl, CURLINFO_RESPONSE_CODE, &m_responseCode);
    curl_easy_cleanup(lCurl);
    curl_slist_free_all(lHeaders);

    _response = lBuffer;
    return true;
}
//===============================================
bool GCurl::doGetApiKey(const GString& _url, GString& _response) {
    char lError[CURL_ERROR_SIZE];
    std::string lBuffer;

    CURL* lCurl = curl_easy_init();

    addHeader("Content-Type", m_contentType);
    addHeader("X-Api-Key", m_apiKey);

    struct curl_slist* lHeaders = NULL;
    lHeaders = m_headers.toHeaders(lCurl, lHeaders);
    curl_easy_setopt(lCurl, CURLOPT_HTTPHEADER, lHeaders);

    curl_easy_setopt(lCurl, CURLOPT_ERRORBUFFER, lError);
    curl_easy_setopt(lCurl, CURLOPT_URL, _url.c_str());
    curl_easy_setopt(lCurl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(lCurl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(lCurl, CURLOPT_SSL_VERIFYHOST, 0L);
    curl_easy_setopt(lCurl, CURLOPT_WRITEFUNCTION, onWrite);
    curl_easy_setopt(lCurl, CURLOPT_WRITEDATA, &lBuffer);
    curl_easy_setopt (lCurl, CURLOPT_VERBOSE, 0L);

    CURLcode lCurlOk = curl_easy_perform(lCurl);
    if(lCurlOk != CURLE_OK) {GLOGT(eGMSG, "Erreur lors de la connexion au serveur.\n%s", curl_easy_strerror(lCurlOk));}
    curl_easy_getinfo(lCurl, CURLINFO_RESPONSE_CODE, &m_responseCode);
    curl_easy_cleanup(lCurl);
    curl_slist_free_all(lHeaders);

    _response = lBuffer;
    return true;
}
//===============================================
bool GCurl::doGetCertificate(const GString& _url, GString& _response) {
    char lError[CURL_ERROR_SIZE];
    std::string lBuffer;

    CURL* lCurl = curl_easy_init();
    curl_easy_setopt(lCurl, CURLOPT_HTTPGET, 1L);
    curl_easy_setopt(lCurl, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_2_0);

    addHeader("Content-Type", m_contentType);

    struct curl_slist* lHeaders = NULL;
    lHeaders = m_headers.toHeaders(lCurl, lHeaders);
    curl_easy_setopt(lCurl, CURLOPT_HTTPHEADER, lHeaders);

    curl_easy_setopt(lCurl, CURLOPT_ERRORBUFFER, lError);
    curl_easy_setopt(lCurl, CURLOPT_URL, _url.c_str());
    curl_easy_setopt(lCurl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(lCurl, CURLOPT_SSL_VERIFYPEER, 1L);
    curl_easy_setopt(lCurl, CURLOPT_CAINFO, m_certificateFile.c_str());
    curl_easy_setopt(lCurl, CURLOPT_SSL_VERIFYHOST, 1L);
    curl_easy_setopt(lCurl, CURLOPT_WRITEFUNCTION, onWrite);
    curl_easy_setopt(lCurl, CURLOPT_WRITEDATA, &lBuffer);
    curl_easy_setopt (lCurl, CURLOPT_VERBOSE, 0L);

    CURLcode lCurlOk = curl_easy_perform(lCurl);
    if(lCurlOk != CURLE_OK) {GLOGT(eGMSG, "Erreur lors de la connexion au serveur.\n%s", curl_easy_strerror(lCurlOk));}
    curl_easy_getinfo(lCurl, CURLINFO_RESPONSE_CODE, &m_responseCode);
    curl_easy_cleanup(lCurl);
    curl_slist_free_all(lHeaders);

    _response = lBuffer;
    return true;
}
//===============================================
bool GCurl::doPost(const GString& _url, GString& _response) {
    char lError[CURL_ERROR_SIZE];
    std::string lBuffer;
    struct curl_slist* lHeaders = NULL;

    CURL* lCurl = curl_easy_init();

    m_contents +=  m_forms.toParams();
    lHeaders = m_headers.toHeaders(lCurl, lHeaders);

    curl_easy_setopt(lCurl, CURLOPT_HTTPHEADER, lHeaders);
    curl_easy_setopt(lCurl, CURLOPT_ERRORBUFFER, lError);
    curl_easy_setopt(lCurl, CURLOPT_URL, _url.c_str());
    curl_easy_setopt(lCurl, CURLOPT_POSTFIELDS, m_contents.c_str());
    curl_easy_setopt(lCurl, CURLOPT_POSTFIELDSIZE, m_contents.size());
    if(!m_username.isEmpty()) {
        curl_easy_setopt(lCurl, CURLOPT_USERNAME, m_username.c_str());
    }
    if(!m_password.isEmpty()) {
        curl_easy_setopt(lCurl, CURLOPT_PASSWORD, m_password.c_str());
    }
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
