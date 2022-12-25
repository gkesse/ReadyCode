//===============================================
#include "GCurl.h"
#include "GEnv.h"
#include "GMap.h"
#include "GCode.h"
#include "GApp.h"
//===============================================
GCurl::GCurl(const GString& _code)
: GObject(_code) {
    initCurl();
}
//===============================================
GCurl::~GCurl() {

}
//===============================================
void GCurl::initCurl() {
    m_mode              = GCurl::MODE_NO_AUTENTICATION;
    m_isTestEnv         = GEnv().isTestEnv();

    m_contentType       = GAPP->getData("curl", "content_type");
    m_apiUsername       = GAPP->getData("curl", "username");
    m_apiPassword       = GAPP->getData("curl", "password");
    m_apiKeyProd        = GAPP->getData("curl", "api_key_prod");
    m_apiKeyTest        = GAPP->getData("curl", "api_key_test");
    m_apiKey            = (m_isTestEnv ? m_apiKeyTest : m_apiKeyProd);
    m_certificateFile   = GAPP->getData("curl", "certificate_file");
    m_urlProd           = GAPP->getData("curl", "url_prod");
    m_urlTest           = GAPP->getData("curl", "url_test");
    m_url               = (m_isTestEnv ? m_urlProd : m_urlTest);
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
bool GCurl::doCall(GString& _response) {
    CURL* lCurl = curl_easy_init();
    char lError[CURL_ERROR_SIZE];
    std::string lBuffer;

    GString lProtocol       = "http";
    GString lFullUrl        = "http://readydev.ovh:9071/readydev/com/v1";
    GString lUrl            = "http://readydev.ovh:9071";
    GString lVerb           = "readydev/com/v1";
    GString lMethod         = "post";
    GString lMethodAuth     = "bearer";
    GString lBearer         = "1ab9cb22ba269a7";
    GString lContentType    = "application/xml";
    bool lHasCertificate    = true;
    bool lIsFullUrl         = false;

    if(!lIsFullUrl) {
        lFullUrl = lUrl + "/" + lVerb;
    }

    if(lCurl) {
        // http
        if(lProtocol == "http") {
            // post
            if(lMethod == "post") {
                if(lMethodAuth == "userpass") {
                    curl_easy_setopt(lCurl, CURLOPT_USERNAME, m_apiUsername.c_str());
                    curl_easy_setopt(lCurl, CURLOPT_PASSWORD, m_apiPassword.c_str());
                }

                curl_easy_setopt(lCurl, CURLOPT_HTTPPOST, 1L);
                curl_easy_setopt(lCurl, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_1_1);
                curl_easy_setopt(lCurl, CURLOPT_ERRORBUFFER, lError);
                curl_easy_setopt(lCurl, CURLOPT_URL, lFullUrl.c_str());
                curl_easy_setopt(lCurl, CURLOPT_FOLLOWLOCATION, 1L);
                curl_easy_setopt(lCurl, CURLOPT_WRITEFUNCTION, onWrite);
                curl_easy_setopt(lCurl, CURLOPT_WRITEDATA, &lBuffer);
                curl_easy_setopt (lCurl, CURLOPT_VERBOSE, 0L);
                curl_easy_setopt(lCurl, CURLOPT_POSTFIELDS, m_contents.c_str());
                curl_easy_setopt(lCurl, CURLOPT_POSTFIELDSIZE, m_contents.size());

                addHeader("Content-Type", m_contentType);

                struct curl_slist* lHeaders = NULL;
                lHeaders = m_headers.toHeaders(lCurl, lHeaders);
                curl_easy_setopt(lCurl, CURLOPT_HTTPHEADER, lHeaders);

                CURLcode lCurlOk = curl_easy_perform(lCurl);

                if(lCurlOk != CURLE_OK) {
                    m_logs.addError(GFORMAT("Erreur lors de la connexion au serveur.\n%s", curl_easy_strerror(lCurlOk)));
                }

                curl_easy_getinfo(lCurl, CURLINFO_RESPONSE_CODE, &m_responseCode);
                curl_easy_cleanup(lCurl);
                curl_slist_free_all(lHeaders);

                _response = lBuffer;
            }
            // get
            if(lMethod == "get") {
                if(lMethodAuth == "userpass") {
                    curl_easy_setopt(lCurl, CURLOPT_USERNAME, m_apiUsername.c_str());
                    curl_easy_setopt(lCurl, CURLOPT_PASSWORD, m_apiPassword.c_str());
                }

                curl_easy_setopt(lCurl, CURLOPT_HTTPPOST, 1L);
                curl_easy_setopt(lCurl, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_1_1);
                curl_easy_setopt(lCurl, CURLOPT_ERRORBUFFER, lError);
                curl_easy_setopt(lCurl, CURLOPT_URL, lFullUrl.c_str());
                curl_easy_setopt(lCurl, CURLOPT_FOLLOWLOCATION, 1L);
                curl_easy_setopt(lCurl, CURLOPT_WRITEFUNCTION, onWrite);
                curl_easy_setopt(lCurl, CURLOPT_WRITEDATA, &lBuffer);
                curl_easy_setopt (lCurl, CURLOPT_VERBOSE, 0L);
                curl_easy_setopt(lCurl, CURLOPT_POSTFIELDS, m_contents.c_str());
                curl_easy_setopt(lCurl, CURLOPT_POSTFIELDSIZE, m_contents.size());

                addHeader("Content-Type", m_contentType);

                struct curl_slist* lHeaders = NULL;
                lHeaders = m_headers.toHeaders(lCurl, lHeaders);
                curl_easy_setopt(lCurl, CURLOPT_HTTPHEADER, lHeaders);

                CURLcode lCurlOk = curl_easy_perform(lCurl);

                if(lCurlOk != CURLE_OK) {
                    m_logs.addError(GFORMAT("Erreur lors de la connexion au serveur.\n%s", curl_easy_strerror(lCurlOk)));
                }

                curl_easy_getinfo(lCurl, CURLINFO_RESPONSE_CODE, &m_responseCode);
                curl_easy_cleanup(lCurl);
                curl_slist_free_all(lHeaders);

                _response = lBuffer;
            }
            // methode inconnue
            else {
                m_logs.addError("Erreur la méthode n'est pas prise en charge.");
            }
        }
        // https
        else if(lProtocol == "https") {
            // post
            if(lMethod == "POST") {
                if(lHasCertificate) {
                    curl_easy_setopt(lCurl, CURLOPT_SSL_VERIFYPEER, 1L);
                    curl_easy_setopt(lCurl, CURLOPT_SSL_VERIFYHOST, 1L);
                    curl_easy_setopt(lCurl, CURLOPT_CAINFO, m_certificateFile.c_str());
                }

                if(lMethodAuth == "userpass") {
                    curl_easy_setopt(lCurl, CURLOPT_USERNAME, m_apiUsername.c_str());
                    curl_easy_setopt(lCurl, CURLOPT_PASSWORD, m_apiPassword.c_str());
                }
                else if(lMethodAuth == "bearer") {
                    curl_easy_setopt(lCurl, CURLOPT_XOAUTH2_BEARER, lBearer.c_str());
                }

                curl_easy_setopt(lCurl, CURLOPT_HTTPPOST, 1L);
                curl_easy_setopt(lCurl, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_1_1);
                curl_easy_setopt(lCurl, CURLOPT_ERRORBUFFER, lError);
                curl_easy_setopt(lCurl, CURLOPT_URL, lFullUrl.c_str());
                curl_easy_setopt(lCurl, CURLOPT_FOLLOWLOCATION, 1L);
                curl_easy_setopt(lCurl, CURLOPT_WRITEFUNCTION, onWrite);
                curl_easy_setopt(lCurl, CURLOPT_WRITEDATA, &lBuffer);
                curl_easy_setopt (lCurl, CURLOPT_VERBOSE, 0L);
                curl_easy_setopt(lCurl, CURLOPT_POSTFIELDS, m_contents.c_str());
                curl_easy_setopt(lCurl, CURLOPT_POSTFIELDSIZE, m_contents.size());

                addHeader("Content-Type", m_contentType);

                struct curl_slist* lHeaders = NULL;
                lHeaders = m_headers.toHeaders(lCurl, lHeaders);
                curl_easy_setopt(lCurl, CURLOPT_HTTPHEADER, lHeaders);

                CURLcode lCurlOk = curl_easy_perform(lCurl);

                if(lCurlOk != CURLE_OK) {
                    m_logs.addError(GFORMAT("Erreur lors de la connexion au serveur.\n%s", curl_easy_strerror(lCurlOk)));
                }

                curl_easy_getinfo(lCurl, CURLINFO_RESPONSE_CODE, &m_responseCode);
                curl_easy_cleanup(lCurl);
                curl_slist_free_all(lHeaders);

                _response = lBuffer;
            }
            // methode inconnue
            else {
                m_logs.addError("Erreur la méthode n'est pas prise en charge.");
            }
        }
        // protocole inconnu
        else {
            m_logs.addError("Erreur le protocole n'est pas géré.");
        }
    }
    // module non initialise
    else {
        m_logs.addError("Erreur le module n'a pas été initialisé.");
    }

    if(lContentType == "application/xml") {
        GCode lResponseDom;
        lResponseDom.createDoc();
        lResponseDom.loadXml(_response);
        lResponseDom.loadData(m_logs.serialize());
        _response = lResponseDom.toString();
    }

    return !m_logs.hasErrors();
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
bool GCurl::doPost(const GString& _url, GString& _response) {
    m_logs.clearMap();

    if(m_mode == GCurl::MODE_CERTIFICATE) {
        doPostCertificate(_url, _response);
    }
    else {
        m_logs.addError("Error le mode n'est pas pris en charge");
        return false;
    }

    return !m_logs.hasErrors();
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
    curl_easy_setopt(lCurl, CURLOPT_USERNAME, m_apiUsername.c_str());
    curl_easy_setopt(lCurl, CURLOPT_PASSWORD, m_apiPassword.c_str());
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

    struct curl_slist* lHeaders = NULL;
    lHeaders = m_headers.toHeaders(lCurl, lHeaders);
    curl_easy_setopt(lCurl, CURLOPT_HTTPHEADER, lHeaders);

    curl_easy_setopt(lCurl, CURLOPT_ERRORBUFFER, lError);
    curl_easy_setopt(lCurl, CURLOPT_URL, _url.c_str());
    curl_easy_setopt(lCurl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(lCurl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(lCurl, CURLOPT_SSL_VERIFYHOST, 0L);
    curl_easy_setopt(lCurl, CURLOPT_USERNAME, m_apiKey.c_str());
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
bool GCurl::doPostNoAuthentication(const GString& _url, GString& _response) {
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
    if(!m_apiUsername.isEmpty()) {
        curl_easy_setopt(lCurl, CURLOPT_USERNAME, m_apiUsername.c_str());
    }
    if(!m_apiPassword.isEmpty()) {
        curl_easy_setopt(lCurl, CURLOPT_PASSWORD, m_apiPassword.c_str());
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
bool GCurl::doGetCertificate(const GString& _url, GString& _response) {
    char lError[CURL_ERROR_SIZE];
    std::string lBuffer;

    CURL* lCurl = curl_easy_init();
    curl_easy_setopt(lCurl, CURLOPT_HTTPGET, 1L);
    curl_easy_setopt(lCurl, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_1_1);

    addHeader("Content-Type", m_contentType);

    struct curl_slist* lHeaders = NULL;
    lHeaders = m_headers.toHeaders(lCurl, lHeaders);
    curl_easy_setopt(lCurl, CURLOPT_HTTPHEADER, lHeaders);

    curl_easy_setopt(lCurl, CURLOPT_ERRORBUFFER, lError);
    curl_easy_setopt(lCurl, CURLOPT_URL, _url.c_str());
    curl_easy_setopt(lCurl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(lCurl, CURLOPT_SSL_VERIFYPEER, 1L);
    curl_easy_setopt(lCurl, CURLOPT_SSL_VERIFYHOST, 1L);
    curl_easy_setopt(lCurl, CURLOPT_CAINFO, m_certificateFile.c_str());
    curl_easy_setopt(lCurl, CURLOPT_USERNAME, m_apiKey.c_str());
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
bool GCurl::doPostCertificate(const GString& _url, GString& _response) {
    char lError[CURL_ERROR_SIZE];
    std::string lBuffer;

    CURL* lCurl = curl_easy_init();
    curl_easy_setopt(lCurl, CURLOPT_HTTPPOST, 1L);
    curl_easy_setopt(lCurl, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_1_1);

    addHeader("Content-Type", m_contentType);

    struct curl_slist* lHeaders = NULL;
    lHeaders = m_headers.toHeaders(lCurl, lHeaders);
    curl_easy_setopt(lCurl, CURLOPT_HTTPHEADER, lHeaders);

    curl_easy_setopt(lCurl, CURLOPT_ERRORBUFFER, lError);
    curl_easy_setopt(lCurl, CURLOPT_URL, _url.c_str());
    curl_easy_setopt(lCurl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(lCurl, CURLOPT_SSL_VERIFYPEER, 1L);
    curl_easy_setopt(lCurl, CURLOPT_SSL_VERIFYHOST, 1L);
    curl_easy_setopt(lCurl, CURLOPT_CAINFO, m_certificateFile.c_str());
    curl_easy_setopt(lCurl, CURLOPT_USERNAME, m_apiKey.c_str());
    curl_easy_setopt(lCurl, CURLOPT_POSTFIELDS, m_contents.c_str());
    curl_easy_setopt(lCurl, CURLOPT_POSTFIELDSIZE, m_contents.size());
    curl_easy_setopt(lCurl, CURLOPT_WRITEFUNCTION, onWrite);
    curl_easy_setopt(lCurl, CURLOPT_WRITEDATA, &lBuffer);
    curl_easy_setopt (lCurl, CURLOPT_VERBOSE, 0L);

    CURLcode lCurlOk = curl_easy_perform(lCurl);

    if(lCurlOk != CURLE_OK) {
        m_logs.addError(GFORMAT("Erreur lors de la connexion au serveur.\n%s", curl_easy_strerror(lCurlOk)));
    }

    curl_easy_getinfo(lCurl, CURLINFO_RESPONSE_CODE, &m_responseCode);
    curl_easy_cleanup(lCurl);
    curl_slist_free_all(lHeaders);

    _response = lBuffer;
    return !m_logs.hasErrors();
}
//===============================================
int GCurl::onWrite(char* _data, size_t _size, size_t _nmemb, std::string* _writerData) {
    if(_writerData == NULL) return 0;
    _writerData->append(_data, _size * _nmemb);
    return _size * _nmemb;
}
//===============================================
