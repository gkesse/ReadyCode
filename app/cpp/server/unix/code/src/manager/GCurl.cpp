//===============================================
#include "GCurl.h"
//===============================================
GCurl::GCurl()
: GObject() {
    m_codeHttp = 0;
    m_url = "https://127.0.0.1/php/req/server.php";
    m_contentType = "application/xml";
}
//===============================================
GCurl::~GCurl() {

}
//===============================================
bool GCurl::checkErrors(const GString& _data) {
    if(m_dataLogs.hasErrors()) {
        m_logs.addError("Le serveur n'est pas disponible.");
        return false;
    }
    m_logs.deserialize(_data);
    return !m_logs.hasErrors();
}
//===============================================
GString GCurl::postHttpsFormFacade(const GString& _module, const GString& _method, const GString& _data) {
    GCode lDom;
    lDom.createDoc();
    lDom.addData("manager", "module", _module);
    lDom.addData("manager", "method", _method);
    lDom.addData("server", "type", "local");
    lDom.loadData(_data);
    GString lData = lDom.toString();
    lData = postHttpsForm(lData);
    checkErrors(lData);
    return lData;
}
//===============================================
GString GCurl::postHttpsForm(const GString& _dataIn) {
    GString lUsername = "admin";
    GString lPassword = "admin";
    GString lUrl = m_url;
    GString lUserAgent = "readyapi/1.0";

    bool lHasUserPass = true;
    bool lHasUserAgent = true;

    CURL* lCurl = curl_easy_init();

    if(!lCurl) {
        m_dataLogs.addError("Le module cURL n'est pas initialisé.");
        return "";
    }

    std::string lBuffer;
    char lError[CURL_ERROR_SIZE];

    if(lHasUserPass) {
        curl_easy_setopt(lCurl, CURLOPT_USERNAME, lUsername.c_str());
        curl_easy_setopt(lCurl, CURLOPT_PASSWORD, lPassword.c_str());
    }

    if(lHasUserAgent) {
        curl_easy_setopt(lCurl, CURLOPT_USERAGENT, lUserAgent.c_str());
    }

    curl_httppost* lPost = NULL;
    curl_httppost* lLast = NULL;

    curl_formadd(&lPost, &lLast,
    CURLFORM_COPYNAME, "req",
    CURLFORM_COPYCONTENTS, _dataIn.c_str(),
    CURLFORM_END);

    curl_easy_setopt(lCurl, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_1_1);
    curl_easy_setopt(lCurl, CURLOPT_ERRORBUFFER, lError);
    curl_easy_setopt(lCurl, CURLOPT_URL, lUrl.c_str());
    curl_easy_setopt(lCurl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(lCurl, CURLOPT_CONNECTTIMEOUT, 30L);              //Connect timeout in secs
    curl_easy_setopt(lCurl, CURLOPT_TIMEOUT, 30L);                     //Maximum time the request is allowed to take in secs
    curl_easy_setopt(lCurl, CURLOPT_NOSIGNAL, 1L);                     //Avoid threading issues with rest of application threads
    curl_easy_setopt(lCurl, CURLOPT_WRITEFUNCTION, onWrite);
    curl_easy_setopt(lCurl, CURLOPT_WRITEDATA, &lBuffer);
    curl_easy_setopt(lCurl, CURLOPT_VERBOSE, 0L);
    curl_easy_setopt(lCurl, CURLOPT_HTTPPOST, lPost);
    curl_easy_setopt(lCurl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(lCurl, CURLOPT_SSL_VERIFYHOST, 0L);

    CURLcode lCurlOk = curl_easy_perform(lCurl);

    if(lCurlOk != CURLE_OK) {
        m_dataLogs.addError(sformat("Le serveur n'est pas disponible.\n%s", curl_easy_strerror(lCurlOk)));
        return "";
    }

    curl_easy_getinfo(lCurl, CURLINFO_RESPONSE_CODE, &m_codeHttp);
    curl_easy_cleanup(lCurl);
    curl_formfree(lPost);

    return lBuffer;
}
//===============================================
int GCurl::onWrite(char* _data, size_t _size, size_t _nmemb, std::string* _writerData) {
    if(_writerData == NULL) return 0;
    _writerData->append(_data, _size * _nmemb);
    return _size * _nmemb;
}
//===============================================
