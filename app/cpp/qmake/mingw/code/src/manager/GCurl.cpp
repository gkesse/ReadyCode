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
    m_protocol          = "http";
    m_method            = "post";
    m_fullUrlHttp       = "http://readydev.ovh:9071/readydev/com/v1";
    m_fullUrlHttps      = "https://readydev.ovh:9071/readydev/com/v1";
    m_fullUrl           = (m_protocol == "http" ? m_fullUrlHttp : m_fullUrlHttps);
    m_serverUrlHttp     = "http://readydev.ovh:9071";
    m_serverUrlHttps    = "https://readydev.ovh:9071";
    m_serverUrl         = (m_protocol == "http" ? m_serverUrlHttp : m_serverUrlHttps);
    m_verbPost          = "readydev/com/v1";
    m_verbGet           = "readydev/api/v1";
    m_verb              = (m_method == "get" ? m_verbGet : m_verbPost);
    m_methodAuth        = "bearer";
    m_apiBearer         = "1ab9cb22ba269a7";
    m_contentType       = "application/xml";
    m_hasCertificate    = true;
    m_hasUserPass       = false;
    m_isFullUrl         = false;

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

    if(!m_isFullUrl) {
        m_fullUrl = m_serverUrl + "/" + m_verb;
    }

    if(lCurl) {
        // http
        if(m_protocol == "http") {
            // http : post
            if(m_method == "post") {
                if(m_hasUserPass) {
                    curl_easy_setopt(lCurl, CURLOPT_USERNAME, m_apiUsername.c_str());
                    curl_easy_setopt(lCurl, CURLOPT_PASSWORD, m_apiPassword.c_str());
                }

                curl_easy_setopt(lCurl, CURLOPT_HTTPPOST, 1L);
                curl_easy_setopt(lCurl, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_1_1);
                curl_easy_setopt(lCurl, CURLOPT_ERRORBUFFER, lError);
                curl_easy_setopt(lCurl, CURLOPT_URL, m_fullUrl.c_str());
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
            // http : get
            else if(m_method == "get") {
                if(m_hasUserPass) {
                    curl_easy_setopt(lCurl, CURLOPT_USERNAME, m_apiUsername.c_str());
                    curl_easy_setopt(lCurl, CURLOPT_PASSWORD, m_apiPassword.c_str());
                }

                curl_easy_setopt(lCurl, CURLOPT_HTTPGET, 1L);
                curl_easy_setopt(lCurl, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_1_1);
                curl_easy_setopt(lCurl, CURLOPT_ERRORBUFFER, lError);
                curl_easy_setopt(lCurl, CURLOPT_URL, m_fullUrl.c_str());
                curl_easy_setopt(lCurl, CURLOPT_FOLLOWLOCATION, 1L);
                curl_easy_setopt(lCurl, CURLOPT_WRITEFUNCTION, onWrite);
                curl_easy_setopt(lCurl, CURLOPT_WRITEDATA, &lBuffer);
                curl_easy_setopt (lCurl, CURLOPT_VERBOSE, 0L);

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
            // http : unknown method
            else {
                m_logs.addError("Erreur la méthode n'est pas prise en charge.");
            }
        }
        // https
        else if(m_protocol == "https") {
            // https : post
            if(m_method == "POST") {
                if(m_hasCertificate) {
                    curl_easy_setopt(lCurl, CURLOPT_SSL_VERIFYPEER, 1L);
                    curl_easy_setopt(lCurl, CURLOPT_SSL_VERIFYHOST, 1L);
                    curl_easy_setopt(lCurl, CURLOPT_CAINFO, m_certificateFile.c_str());
                }

                if(m_methodAuth == "userpass") {
                    curl_easy_setopt(lCurl, CURLOPT_USERNAME, m_apiUsername.c_str());
                    curl_easy_setopt(lCurl, CURLOPT_PASSWORD, m_apiPassword.c_str());
                }
                else if(m_methodAuth == "bearer") {
                    curl_easy_setopt(lCurl, CURLOPT_XOAUTH2_BEARER, m_apiBearer.c_str());
                }

                curl_easy_setopt(lCurl, CURLOPT_HTTPPOST, 1L);
                curl_easy_setopt(lCurl, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_1_1);
                curl_easy_setopt(lCurl, CURLOPT_ERRORBUFFER, lError);
                curl_easy_setopt(lCurl, CURLOPT_URL, m_fullUrl.c_str());
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
            // https : methode inconnue
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
