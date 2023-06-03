//===============================================
#include "GCurl.h"
#include "GEnv.h"
#include "GMap.h"
#include "GCode.h"
#include "GApp.h"
//===============================================
GCurl::GCurl()
: GObject() {
    initCurl();
}
//===============================================
GCurl::~GCurl() {

}
//===============================================
void GCurl::initCurl() {
    m_protocol          = "https";
    m_method            = "post";
    m_hasCertificate    = true;
    m_hasUserPass       = false;
    m_isFullUrl         = true;

    m_fullUrlHttp       = "http://readydev.ovh";
    m_fullUrlHttps      = "https://readydev.ovh";
    m_fullUrlHttp       = "http://readydev.ovh:9071/readydev/com/v1";
    m_fullUrlHttps      = "https://readydev.ovh:443/readydev/com/v1";
    m_fullUrl           = (m_protocol == "http" ? m_fullUrlHttp : m_fullUrlHttps);
    m_serverUrlHttp     = "http://readydev.ovh:9071";
    m_serverUrlHttps    = "https://readydev.ovh:9071";
    m_serverUrl         = (m_protocol == "http" ? m_serverUrlHttp : m_serverUrlHttps);
    m_verbPost          = "readydev/com/v1";
    m_verbGet           = "readydev/api/v1";
    m_verb              = (m_method == "get" ? m_verbGet : m_verbPost);
    m_methodAuth        = "no_authentication";
    m_apiBearer         = "1ab9cb22ba269a7";
    m_contentType       = "application/xml";

    m_isTestEnv         = GEnv().isTestEnv();

    m_contentType       = GAPP->getData("curl", "content_type");
    m_apiUsername       = GAPP->getData("curl", "username");
    m_apiPassword       = GAPP->getData("curl", "password");
    m_apiKeyProd        = GAPP->getData("curl", "api_key_prod");
    m_apiKeyTest        = GAPP->getData("curl", "api_key_test");
    m_apiKey            = (m_isTestEnv ? m_apiKeyTest : m_apiKeyProd);
    m_certificateFile   = GAPP->getData("curl", "certificate_file");
    m_privateKeyFile    = GAPP->getData("curl", "private_key_file");
    m_cacertFile        = GAPP->getData("curl", "cacert_file");
    m_cacertPath        = GAPP->getData("curl", "cacert_path");
    m_urlProd           = GAPP->getData("curl", "url_prod");
    m_urlTest           = GAPP->getData("curl", "url_test");
    m_url               = (m_isTestEnv ? m_urlProd : m_urlTest);
}
//===============================================
bool GCurl::onHttpPost(CURL* _curl, GString& _response) {
    char lError[CURL_ERROR_SIZE];
    std::string lBuffer;

    // http : post : username password
    if(m_hasUserPass) {
        curl_easy_setopt(_curl, CURLOPT_USERNAME, m_apiUsername.c_str());
        curl_easy_setopt(_curl, CURLOPT_PASSWORD, m_apiPassword.c_str());
    }

    curl_easy_setopt(_curl, CURLOPT_HTTPPOST, 1L);
    curl_easy_setopt(_curl, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_1_1);
    curl_easy_setopt(_curl, CURLOPT_ERRORBUFFER, lError);
    curl_easy_setopt(_curl, CURLOPT_URL, m_fullUrl.c_str());
    curl_easy_setopt(_curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, onWrite);
    curl_easy_setopt(_curl, CURLOPT_WRITEDATA, &lBuffer);
    curl_easy_setopt (_curl, CURLOPT_VERBOSE, 0L);
    curl_easy_setopt(_curl, CURLOPT_POSTFIELDS, m_contents.c_str());
    curl_easy_setopt(_curl, CURLOPT_POSTFIELDSIZE, m_contents.size());

    addHeader("Content-Type", m_contentType);

    struct curl_slist* lHeaders = NULL;
    lHeaders = m_headers.toHeaders(_curl, lHeaders);
    curl_easy_setopt(_curl, CURLOPT_HTTPHEADER, lHeaders);

    CURLcode lCurlOk = curl_easy_perform(_curl);

    if(lCurlOk != CURLE_OK) {
        m_logs.addError(GFORMAT("Erreur lors de la connexion au serveur.\n%s", curl_easy_strerror(lCurlOk)));
    }

    curl_easy_getinfo(_curl, CURLINFO_RESPONSE_CODE, &m_responseCode);
    curl_easy_cleanup(_curl);
    curl_slist_free_all(lHeaders);

    _response = lBuffer;
    return !m_logs.hasErrors();
}
//===============================================
bool GCurl::onHttpGet(CURL* _curl, GString& _response) {
    char lError[CURL_ERROR_SIZE];
    std::string lBuffer;

    // http : get : username password
    if(m_hasUserPass) {
        curl_easy_setopt(_curl, CURLOPT_USERNAME, m_apiUsername.c_str());
        curl_easy_setopt(_curl, CURLOPT_PASSWORD, m_apiPassword.c_str());
    }

    curl_easy_setopt(_curl, CURLOPT_HTTPGET, 1L);
    curl_easy_setopt(_curl, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_1_1);
    curl_easy_setopt(_curl, CURLOPT_ERRORBUFFER, lError);
    curl_easy_setopt(_curl, CURLOPT_URL, m_fullUrl.c_str());
    curl_easy_setopt(_curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, onWrite);
    curl_easy_setopt(_curl, CURLOPT_WRITEDATA, &lBuffer);
    curl_easy_setopt(_curl, CURLOPT_VERBOSE, 0L);

    addHeader("Content-Type", m_contentType);

    struct curl_slist* lHeaders = NULL;
    lHeaders = m_headers.toHeaders(_curl, lHeaders);
    curl_easy_setopt(_curl, CURLOPT_HTTPHEADER, lHeaders);

    CURLcode lCurlOk = curl_easy_perform(_curl);

    if(lCurlOk != CURLE_OK) {
        m_logs.addError(GFORMAT("Erreur lors de la connexion au serveur.\n%s", curl_easy_strerror(lCurlOk)));
    }

    curl_easy_getinfo(_curl, CURLINFO_RESPONSE_CODE, &m_responseCode);
    curl_easy_cleanup(_curl);
    curl_slist_free_all(lHeaders);

    _response = lBuffer;
    return !m_logs.hasErrors();
}
//===============================================
bool GCurl::onHttpsPost(CURL* _curl, GString& _response) {
    char lError[CURL_ERROR_SIZE];
    std::string lBuffer;

    curl_easy_setopt(_curl, CURLOPT_VERBOSE, 1L);
    curl_easy_setopt(_curl, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_1_1);
    curl_easy_setopt(_curl, CURLOPT_HTTPPOST, 1L);
    curl_easy_setopt(_curl, CURLOPT_ERRORBUFFER, lError);
    curl_easy_setopt(_curl, CURLOPT_URL, m_fullUrl.c_str());
    curl_easy_setopt(_curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, onWrite);
    curl_easy_setopt(_curl, CURLOPT_WRITEDATA, &lBuffer);
    curl_easy_setopt(_curl, CURLOPT_POSTFIELDS, m_contents.c_str());
    curl_easy_setopt(_curl, CURLOPT_POSTFIELDSIZE, m_contents.size());

    // https : post : certificate
    if(m_hasCertificate) {
        curl_easy_setopt(_curl, CURLOPT_SSL_VERIFYPEER, 1L);
        curl_easy_setopt(_curl, CURLOPT_SSL_VERIFYHOST, 1L);
        //curl_easy_setopt(_curl, CURLOPT_SSLCERTTYPE, "PEM");
        //curl_easy_setopt(_curl, CURLOPT_SSLCERT, m_certificateFile.c_str());
        //curl_easy_setopt(_curl, CURLOPT_SSLKEY, m_privateKeyFile.c_str());
        curl_easy_setopt(_curl, CURLOPT_CAINFO, m_certificateFile.c_str());
    }
    // https : post : no certificate
    else {
        curl_easy_setopt(_curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(_curl, CURLOPT_SSL_VERIFYHOST, 0L);
    }

    // https : post : username password
    if(m_methodAuth == "userpass") {
        curl_easy_setopt(_curl, CURLOPT_USERNAME, m_apiUsername.c_str());
        curl_easy_setopt(_curl, CURLOPT_PASSWORD, m_apiPassword.c_str());
    }
    // https : post : bearer
    else if(m_methodAuth == "bearer") {
        curl_easy_setopt(_curl, CURLOPT_HTTPAUTH, CURLAUTH_BEARER);
        curl_easy_setopt(_curl, CURLOPT_XOAUTH2_BEARER, m_apiBearer.c_str());
    }

    addHeader("Content-Type", m_contentType);

    struct curl_slist* lHeaders = NULL;
    lHeaders = m_headers.toHeaders(_curl, lHeaders);
    curl_easy_setopt(_curl, CURLOPT_HTTPHEADER, lHeaders);

    CURLcode lCurlOk = curl_easy_perform(_curl);

    if(lCurlOk != CURLE_OK) {
        m_logs.addError(GFORMAT("Erreur lors de la connexion au serveur.\n%s", curl_easy_strerror(lCurlOk)));
    }

    curl_easy_getinfo(_curl, CURLINFO_RESPONSE_CODE, &m_responseCode);
    curl_easy_cleanup(_curl);
    curl_slist_free_all(lHeaders);

    _response = lBuffer;
    return !m_logs.hasErrors();
}
//===============================================
bool GCurl::onHttpsGet(CURL* _curl, GString& _response) {
    char lError[CURL_ERROR_SIZE];
    std::string lBuffer;

    // https : get : certificate
    if(m_hasCertificate) {
        curl_easy_setopt(_curl, CURLOPT_SSL_VERIFYPEER, 1L);
        curl_easy_setopt(_curl, CURLOPT_SSL_VERIFYHOST, 1L);
        curl_easy_setopt(_curl, CURLOPT_CAINFO, m_certificateFile.c_str());
    }
    // https : get : no certificate
    else {
        curl_easy_setopt(_curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(_curl, CURLOPT_SSL_VERIFYHOST, 0L);
    }

    // https : get : username password
    if(m_methodAuth == "userpass") {
        curl_easy_setopt(_curl, CURLOPT_USERNAME, m_apiUsername.c_str());
        curl_easy_setopt(_curl, CURLOPT_PASSWORD, m_apiPassword.c_str());
    }
    // https : get : bearer
    else if(m_methodAuth == "bearer") {
        curl_easy_setopt(_curl, CURLOPT_HTTPAUTH, CURLAUTH_BEARER);
        curl_easy_setopt(_curl, CURLOPT_XOAUTH2_BEARER, m_apiBearer.c_str());
    }

    curl_easy_setopt(_curl, CURLOPT_HTTPGET, 1L);
    curl_easy_setopt(_curl, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_1_1);
    curl_easy_setopt(_curl, CURLOPT_ERRORBUFFER, lError);
    curl_easy_setopt(_curl, CURLOPT_URL, m_fullUrl.c_str());
    curl_easy_setopt(_curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, onWrite);
    curl_easy_setopt(_curl, CURLOPT_WRITEDATA, &lBuffer);
    curl_easy_setopt (_curl, CURLOPT_VERBOSE, 0L);

    addHeader("Content-Type", m_contentType);

    struct curl_slist* lHeaders = NULL;
    lHeaders = m_headers.toHeaders(_curl, lHeaders);
    curl_easy_setopt(_curl, CURLOPT_HTTPHEADER, lHeaders);

    CURLcode lCurlOk = curl_easy_perform(_curl);

    if(lCurlOk != CURLE_OK) {
        m_logs.addError(GFORMAT("Erreur lors de la connexion au serveur.\n%s", curl_easy_strerror(lCurlOk)));
    }

    curl_easy_getinfo(_curl, CURLINFO_RESPONSE_CODE, &m_responseCode);
    curl_easy_cleanup(_curl);
    curl_slist_free_all(lHeaders);

    _response = lBuffer;
    return !m_logs.hasErrors();
}
//===============================================
void GCurl::initModule() {
    curl_global_init(CURL_GLOBAL_ALL);
}
//===============================================
void GCurl::cleanModule() {
    curl_global_cleanup();
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
bool GCurl::doCall(GString& _response) {
    CURL* lCurl = curl_easy_init();

    if(!m_isFullUrl) {
        m_fullUrl = m_serverUrl + "/" + m_verb;
    }

    if(lCurl) {
        // http
        if(m_protocol == "http") {
            // http : post
            if(m_method == "post") {
                onHttpPost(lCurl, _response);
            }
            // http : get
            else if(m_method == "get") {
                onHttpGet(lCurl, _response);
            }
            // http : unknown method
            else {
                m_logs.addError("Erreur la méthode n'est pas prise en charge.");
            }
        }
        // https
        else if(m_protocol == "https") {
            // https : post
            if(m_method == "post") {
                onHttpsPost(lCurl, _response);
            }
            // https : get
            else if(m_method == "get") {
                onHttpsGet(lCurl, _response);
            }
            // https : unknown method
            else {
                m_logs.addError("Erreur la méthode n'est pas prise en charge.");
            }
        }
        // unknown protocol
        else {
            m_logs.addError("Erreur le protocole n'est pas géré.");
        }
    }
    // unknown module
    else {
        m_logs.addError("Erreur le module n'a pas été initialisé.");
    }

    // application/xml
    if(m_contentType == "application/xml") {
        GCode lResponseDom;
        lResponseDom.createDoc();
        lResponseDom.loadXml(_response);
        lResponseDom.loadData(m_logs.serialize());
        _response = lResponseDom.toString();
    }

    return !m_logs.hasErrors();
}
//===============================================
int GCurl::onWrite(char* _data, size_t _size, size_t _nmemb, std::string* _writerData) {
    if(_writerData == NULL) return 0;
    _writerData->append(_data, _size * _nmemb);
    return _size * _nmemb;
}
//===============================================
