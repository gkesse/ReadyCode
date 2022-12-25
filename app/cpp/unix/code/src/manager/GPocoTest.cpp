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
    if(lKey == "get") {
        runGet(_argc, _argv);
    }
    else if(lKey == "server/http") {
        runServerHttp(_argc, _argv);
    }
    else if(lKey == "server/https") {
        runServerHttps(_argc, _argv);
    }
    else if(lKey == "server/https/userpass") {
        runServerHttpsUserPass(_argc, _argv);
    }
    else if(lKey == "server/https/cert") {
        runServerHttpsCert(_argc, _argv);
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
    GString lResponse;
    lPoco.doGet("http://example.com/", lResponse);
    lResponse.print();
}
//===============================================
void GPocoTest::runServerHttp(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    GPoco lPoco;
    lPoco.runServer(_argc, _argv);
}
//===============================================
void GPocoTest::runServerHttps(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    GPoco lPoco;
    lPoco.runServer(_argc, _argv);
}
//===============================================
void GPocoTest::runServerHttpsUserPass(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    GPoco lPoco;
    lPoco.runServer(_argc, _argv);
}
//===============================================
void GPocoTest::runServerHttpsCert(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    GPoco lPoco;
    lPoco.runServer(_argc, _argv);
}
//===============================================
void GPocoTest::runServer(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    GPoco lPoco;
    lPoco.runServer(_argc, _argv);
    m_logs.add(lPoco.m_logs);
}
//===============================================
