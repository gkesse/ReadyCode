//===============================================
#include "GTest.h"
#include "GCurlTest.h"
#include "GSocketTest.h"
//===============================================
GTest::GTest()
: GObject() {

}
//===============================================
GTest::~GTest() {

}
//===============================================
void GTest::run(int _argc, char** _argv) {
	GString lKey;
	if(_argc > 2) lKey = _argv[2];
    if(lKey == "curl") {
        runCurl(_argc, _argv);
    }
    else if(lKey == "socket") {
        runSocket(_argc, _argv);
    }
    else {
        runTest(_argc, _argv);
    }
}
//===============================================
void GTest::runTest(int _argc, char** _argv) {
    GLOGT(eGFUN, "Le process est inconnu.");
}
//===============================================
void GTest::runCurl(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    GCurlTest lObj;
    lObj.run(_argc, _argv);
}
//===============================================
void GTest::runSocket(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    GSocketTest lObj;
    lObj.run(_argc, _argv);
}
//===============================================
