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
    if(_argc > 2) lMethod = _argv[2];
    if(lMethod == "") {
        m_logs.addError("Erreur la méthode est obligatoire.");
    }
    else if(lMethod == "test") {
        runTest(_argc, _argv);
    }
    else if(lMethod == "http_get") {
        runHttpGet(_argc, _argv);
    }
    else {
        m_logs.addError("Erreur la méthode est inconnue.");
    }
}
//===============================================
void GPocoTest::runTest(int _argc, char** _argv) {
    GPoco lPoco;
    lPoco.initPoco();
    lPoco.setProtocol("http");
    lPoco.setVerb("readyapi-1.0");
    lPoco.setUserAgent("rdvapp/1.0");
    lPoco.setPort(9071);
    lPoco.setHasUserPass(false);
    lPoco.setHasContentType(false);
    lPoco.run(_argc, _argv);
    m_logs.addLogs(lPoco.getLogs());
}
//===============================================
void GPocoTest::runHttpGet(int _argc, char** _argv) {
    GPoco lPoco;
    lPoco.initPoco();
    lPoco.setProtocol("http");
    lPoco.setVerb("readyapi-1.0");
    lPoco.setUserAgent("rdvapp/1.0");
    lPoco.setPort(9071);
    lPoco.setHasUserPass(false);
    lPoco.setHasContentType(false);
    lPoco.run(_argc, _argv);
    m_logs.addLogs(lPoco.getLogs());
}
//===============================================
void GPocoTest::runServer(int _argc, char** _argv) {
    GPoco lPoco;
    lPoco.run(_argc, _argv);
    m_logs.addLogs(lPoco.getLogs());
}
//===============================================
