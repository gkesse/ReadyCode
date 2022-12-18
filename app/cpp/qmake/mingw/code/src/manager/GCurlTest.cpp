//===============================================
#include "GCurlTest.h"
#include "GCurl.h"
#include "GLog.h"
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
    if(lKey == "get") {
        runGet(_argc, _argv);
    }
    else if(lKey == "post/xml") {
        runPostXml(_argc, _argv);
    }
    else if(lKey == "post/form") {
        runPostForm(_argc, _argv);
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
    lCurl.doGet("https://readydev.ovh:9071/", lResponse);
    lResponse.print();
}
//===============================================
void GCurlTest::runPostXml(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    GCurl lCurl;
    GString lResponse;

    GCode lDom;
    lDom.createDoc();
    lDom.createRequest("command", "load_command");

    lCurl.addHeader("Content-Type", "application/xml");
    lCurl.addHeader("X-Api-Key", "oooooooooooooooooooooooooooooo");
    lCurl.addContent(lDom.toString());
    lCurl.doPost("https://api.sncf.com/v1/coverage/sncf/commercial_modes", lResponse);
    lResponse.print();
}
//===============================================
void GCurlTest::runPostForm(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    GCurl lCurl;
    GString lResponse;
    lCurl.addForm("name", "Gerard KESSE");
    lCurl.addForm("project", "cURL");
    lCurl.doPost("http://readydev.ovh:9081/", lResponse);
}
//===============================================
