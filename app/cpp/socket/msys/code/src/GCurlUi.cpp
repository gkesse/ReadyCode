//===============================================
#include "GCurlUi.h"
#include "GCurl.h"
#include "GManager.h"
//===============================================
GCurlUi::GCurlUi() {

}
//===============================================
GCurlUi::~GCurlUi() {

}
//===============================================
GCurlUi* GCurlUi::Create(const std::string& key) {
    if(key == "default") {return new GCurlUi;}
    return new GCurlUi;
}
//===============================================
void GCurlUi::run(int argc, char** argv) {
    sGApp* lApp = GManager::Instance()->data()->app;

    GCurl lCurl;
    lCurl.init();
    lCurl.url(lApp->curl_url);
    lCurl.writeFunc(onWriteFunc);
    lCurl.writeData();
    lCurl.perform();
    lCurl.clean();
    lCurl.print();
}
//===============================================
size_t GCurlUi::onWriteFunc(void* _content, size_t _size, size_t _nmemb, void* _params) {
    GCurl lData;
    return lData.append(_content, _size, _nmemb, _params);
}
//===============================================
