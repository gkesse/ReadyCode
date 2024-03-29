//===============================================
#include "GCurlTest.h"
#include "GCurl.h"
#include "GCode.h"
//===============================================
GCurlTest::GCurlTest()
: GObject() {

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
        runTest(_argc, _argv);
    }
}
//===============================================
void GCurlTest::runTest(int _argc, char** _argv) {
    GLOGT(eGFUN, "Le process est inconnu.");
}
//===============================================
void GCurlTest::runCall(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    GCurl lCurl;
    GString lResponse;
    GCode lDom;
    lDom.createDoc();
    lDom.createRequest("module", "load_module");
    lCurl.addForm("name", "Gerard KESSE");
    lCurl.addForm("project", "cURL");
    lCurl.setContentType("application/xml");
    lCurl.addContent(lDom.toString());
    lCurl.doCall(lResponse);
    lResponse.print();
}
//===============================================
