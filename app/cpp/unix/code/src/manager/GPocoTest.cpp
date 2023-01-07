//===============================================
#include "GPocoTest.h"
#include "GPoco.h"
//===============================================
GPocoTest::GPocoTest()
: GObject() {

}
//===============================================
GPocoTest::~GPocoTest() {

}
//===============================================
void GPocoTest::run(int _argc, char** _argv) {
    GString lMethod;
    if(_argc > 3) lMethod = _argv[3];
    if(lMethod == "") {
        m_logs.addError("Erreur la méthode est obligatoire.");
    }
    else if(lMethod == "test") {
        runTest(_argc, _argv);
    }
    else {
        m_logs.addError("Erreur la méthode est inconnue.");
    }
}
//===============================================
void GPocoTest::runTest(int _argc, char** _argv) {

}
//===============================================
void GPocoTest::runServer(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    GPoco lPoco;
    lPoco.runServer(_argc, _argv);
    m_logs.add(lPoco.m_logs);
}
//===============================================
