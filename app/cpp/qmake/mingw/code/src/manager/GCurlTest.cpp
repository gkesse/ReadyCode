//===============================================
#include "GCurlTest.h"
#include "GCurl.h"
#include "GCode.h"
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
    if(lKey == "call") {
        runCall(_argc, _argv);
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
void GCurlTest::runCall(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    GCurl lCurl;
    GString lResponse;
    lCurl.addForm("name", "Gerard KESSE");
    lCurl.addForm("project", "cURL");
    lCurl.setContentType("application/json");
    lCurl.doCall(lResponse);
    lResponse.print();
}
//===============================================
