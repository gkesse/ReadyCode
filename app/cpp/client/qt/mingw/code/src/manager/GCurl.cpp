//===============================================
#include "GCurl.h"
//===============================================
GCurl::GCurl()
: GObject() {
    m_codeHttp = 0;
}
//===============================================
GCurl::~GCurl() {

}
//===============================================
int GCurl::toPort() const {
    GString lEnv = getEnv("GPROJECT_ENV");
    if(lEnv == "TEST") return 9011;
    return 9010;
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
GString GCurl::postHttpFacade(const GString& _module, const GString& _method, const GString& _data) {
    GCode lDom;
    lDom.createDoc();
    lDom.addData("manager", "module", _module);
    lDom.addData("manager", "method", _method);
    lDom.addData("facade", "facade", "server_cpp");
    lDom.loadData(_data);
    GString lData = lDom.toString();
    lData = postHttp("Bonjour tout le monde");
    checkErrors(lData);
    return lData;
}
//===============================================
GString GCurl::postHttp(const GString& _dataIn) {
    GString lUsername = "admin";
    GString lPassword = "admin";
    GString lUrl = "http://readydev.ovh";
    GString lUserAgent = "readyapi/1.0";

    bool lHasUserPass = true;
    bool lHasUserAgent = true;

    lUrl = sformat("%s:%d", lUrl.c_str(), toPort());

    CURL* lCurl = curl_easy_init();

    if(!lCurl) {
        m_dataLogs.addError("L'initialisation du module cURL a échoué.");
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

    curl_easy_setopt(lCurl, CURLOPT_HTTPPOST, 1L);
    curl_easy_setopt(lCurl, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_1_1);
    curl_easy_setopt(lCurl, CURLOPT_ERRORBUFFER, lError);
    curl_easy_setopt(lCurl, CURLOPT_URL, lUrl.c_str());
    curl_easy_setopt(lCurl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(lCurl, CURLOPT_WRITEFUNCTION, onWrite);
    curl_easy_setopt(lCurl, CURLOPT_WRITEDATA, &lBuffer);
    curl_easy_setopt(lCurl, CURLOPT_VERBOSE, 0L);
    curl_easy_setopt(lCurl, CURLOPT_POSTFIELDS, _dataIn.c_str());
    curl_easy_setopt(lCurl, CURLOPT_POSTFIELDSIZE, _dataIn.size());

    struct curl_slist* lHeaders = NULL;
    lHeaders = curl_slist_append(lHeaders, sformat("Content-Type: application/xml").c_str());
    curl_easy_setopt(lCurl, CURLOPT_HTTPHEADER, lHeaders);

    CURLcode lCurlOk = curl_easy_perform(lCurl);

    if(lCurlOk != CURLE_OK) {
        m_dataLogs.addError(sformat("Le serveur n'est pas disponible.\n%s", curl_easy_strerror(lCurlOk)));
        return "";
    }

    curl_easy_getinfo(lCurl, CURLINFO_RESPONSE_CODE, &m_codeHttp);
    curl_easy_cleanup(lCurl);
    curl_slist_free_all(lHeaders);

    return lBuffer;
}
//===============================================
int GCurl::onWrite(char* _data, size_t _size, size_t _nmemb, std::string* _writerData) {
    if(_writerData == NULL) return 0;
    _writerData->append(_data, _size * _nmemb);
    return _size * _nmemb;
}
//===============================================
