//===============================================
#include "GPocoTest.h"
#include "GPoco.h"
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
    if(lKey == "server") {
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
void GPocoTest::runServer(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    GPoco lPoco;
    lPoco.runServer(_argc, _argv);
    m_logs.add(lPoco.m_logs);
}
//===============================================
