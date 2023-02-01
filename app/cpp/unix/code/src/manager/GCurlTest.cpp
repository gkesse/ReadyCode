//===============================================
#include "GCurlTest.h"
#include "GCurl.h"
//===============================================
GCurlTest::GCurlTest()
: GObject() {

}
//===============================================
GCurlTest::~GCurlTest() {

}
//===============================================
void GCurlTest::run(int _argc, char** _argv) {
    GString lMethod;
    if(_argc > 3) lMethod = _argv[3];
    if(lMethod == "") {
        m_logs.addError("La méthode est obligatoire.");
    }
    else if(lMethod == "test") {
        runTest(_argc, _argv);
    }
    else {
        m_logs.addError("La méthode est inconnue.");
    }
}
//===============================================
void GCurlTest::runTest(int _argc, char** _argv) {

}
//===============================================
void GCurlTest::runGetHttp(int _argc, char** _argv) {
    GCurl lCurl;
    GString lResponse;
    lCurl.doGet("http://example.com/", lResponse);
    lResponse.print();
}
//===============================================
