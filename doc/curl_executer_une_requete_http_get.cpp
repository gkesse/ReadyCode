// envoi de la requete
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

// lecture de la reponse
int GCurl::onWrite(char* _data, size_t _size, size_t _nmemb, std::string* _writerData) {
    if(_writerData == NULL) return 0;
    _writerData->append(_data, _size * _nmemb);
    return _size * _nmemb;
}
