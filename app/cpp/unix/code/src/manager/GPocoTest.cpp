//===============================================
#include "GPocoTest.h"
#include "GPoco.h"
#include "GLog.h"
//===============================================
GPocoTest::GPocoTest(const GString& _code)
: GObject(_code) {

}
//===============================================
GPocoTest::~GPocoTest() {

}
//===============================================
void GPocoTest::run(int _argc, char** _argv) {
    GString lKey;
    if(_argc > 3) lKey = _argv[3];
    if(lKey == "get") {
        runGet(_argc, _argv);
    }
    else if(lKey == "server") {
        runServer(_argc, _argv);
    }
    else {
        runDefault(_argc, _argv);
    }
}
//===============================================
void GPocoTest::runDefault(int _argc, char** _argv) {
    GLOGT(eGFUN, "Le process est inconnu.");
}
//===============================================
void GPocoTest::runGet(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    GPoco lPoco;
    lPoco.doGet("http://example.com/");
}
//===============================================
void GPocoTest::runServer(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    GPoco lPoco;
    lPoco.runServer(_argc, _argv);
}
//===============================================
