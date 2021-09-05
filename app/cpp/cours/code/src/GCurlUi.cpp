//===============================================
#include "GCurlUi.h"
//===============================================
GCurlUi::GCurlUi(QObject* parent) :
QObject(parent) {

}
//===============================================
GCurlUi::~GCurlUi() {

}
//===============================================
GCurlUi* GCurlUi::Create(const QString& key) {
    if(key == "default") {return new GCurlUi;}
    // default
    return new GCurlUi;
}
//===============================================
void GCurlUi::run(int argc, char** argv) {
    CURL *curl;
    std::string readBuffer;

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "http://www.google.com");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, onWriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        std::cout << readBuffer << std::endl;
    }
}
//===============================================
size_t GCurlUi::onWriteCallback(void* contents, size_t size, size_t nmemb, void* params) {
    std::string* lReadBuffer = (std::string*)params;
    lReadBuffer->append((char*)contents, size * nmemb);
    return size * nmemb;
}
//===============================================
