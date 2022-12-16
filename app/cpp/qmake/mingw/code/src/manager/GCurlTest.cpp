//===============================================
#include "GCurlTest.h"
#include "GCurl.h"
#include "GLog.h"
//===============================================
GCurlTest::GCurlTest(const GString& _code)
: GObject(_code) {

}
//===============================================
GCurlTest::~GCurlTest() {

}
//===============================================
void GCurlTest::run(int _argc, char** _argv) {
    GString lKey;
    if(_argc > 3) lKey = _argv[3];
    if(lKey == "get") {
        runGet(_argc, _argv);
    }
    else if(lKey == "post") {
        runPost(_argc, _argv);
    }
    else {
        runDefault(_argc, _argv);
    }
}
//===============================================
void GCurlTest::runDefault(int _argc, char** _argv) {
    GLOGT(eGFUN, "Le process est inconnu.");
}
//===============================================
void GCurlTest::runGet(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    GCurl lCurl;
    GString lResponse;
    lCurl.doGet("http://readydev.ovh:9080/", lResponse);
    lResponse.print();
}
//===============================================
void GCurlTest::runPost(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    GCurl lCurl;
    GString lResponse;
    lCurl.addParam("name", "Gerard KESSE");
    lCurl.addParam("project", "cURL");
    lCurl.doPost("http://readydev.ovh:9080/", lResponse);
    lResponse.print();
}
//===============================================
