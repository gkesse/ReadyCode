//===============================================
#include "GTest.h"
#include "GPocoTest.h"
#include "GCurlTest.h"
#include "GSocketTest.h"
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
    if(lKey == "poco") {
        runPoco(_argc, _argv);
    }
    else if(lKey == "curl") {
        runCurl(_argc, _argv);
    }
    else if(lKey == "socket") {
        runSocket(_argc, _argv);
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
void GTest::runPoco(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    GPocoTest lObj;
    lObj.run(_argc, _argv);
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
