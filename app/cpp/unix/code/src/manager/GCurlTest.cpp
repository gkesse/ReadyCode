//===============================================
#include "GCurlTest.h"
#include "GCurl.h"
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
        runGetHttp(_argc, _argv);
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
void GCurlTest::runGetHttp(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    GCurl lCurl;
    GString lResponse;
    lCurl.doGet("http://example.com/", lResponse);
    lResponse.print();
}
//===============================================
