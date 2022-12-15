//===============================================
#include "GTest.h"
#include "GCurlTest.h"
#include "GLog.h"
//===============================================
GTest::GTest()
: GManager() {

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
    else {
        runDefault(_argc, _argv);
    }
}
//===============================================
void GTest::runDefault(int _argc, char** _argv) {
    GLOGT(eGFUN, "Le process est inconnu.");
}
//===============================================
void GTest::runCurl(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    GCurlTest lObj;
    lObj.run(_argc, _argv);
}
//===============================================
