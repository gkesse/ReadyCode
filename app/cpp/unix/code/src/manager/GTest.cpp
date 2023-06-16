//===============================================
#include "GTest.h"
#include "GPocoTest.h"
#include "GXmlTest.h"
#include "GJsonTest.h"
#include "GCurlTest.h"
#include "GSocketTest.h"
#include "GOpenSSLTest.h"
#include "GStringTest.h"
//===============================================
GTest::GTest()
: GManager() {

}
//===============================================
GTest::~GTest() {

}
//===============================================
void GTest::run(int _argc, char** _argv) {
    GString lModule;
    if(_argc > 1) lModule = _argv[1];
    if(lModule == "") {
        m_logs.addError("Le module est obligatoire.");
    }
    else if(lModule == "poco") {
        runPoco(_argc, _argv);
    }
    else if(lModule == "xml") {
        runXml(_argc, _argv);
    }
    else if(lModule == "json") {
        runJson(_argc, _argv);
    }
    else if(lModule == "curl") {
        runCurl(_argc, _argv);
    }
    else if(lModule == "socket") {
        runSocket(_argc, _argv);
    }
    else if(lModule == "openssl") {
        runOpenSSL(_argc, _argv);
    }
    else if(lModule == "string") {
        runTest(_argc, _argv);
    }
    else {
        m_logs.addError("Le module est inconnu.");
    }
}
//===============================================
void GTest::runPoco(int _argc, char** _argv) {
    GPocoTest lTest;
    lTest.run(_argc, _argv);
    m_logs.addLogs(lTest.getLogs());
}
//===============================================
void GTest::runXml(int _argc, char** _argv) {
    GXmlTest lTest;
    lTest.run(_argc, _argv);
    m_logs.addLogs(lTest.getLogs());
}
//===============================================
void GTest::runJson(int _argc, char** _argv) {
    GJsonTest lTest;
    lTest.run(_argc, _argv);
    m_logs.addLogs(lTest.getLogs());
}
//===============================================
void GTest::runCurl(int _argc, char** _argv) {
    GCurlTest lTest;
    lTest.run(_argc, _argv);
    m_logs.addLogs(lTest.getLogs());
}
//===============================================
void GTest::runSocket(int _argc, char** _argv) {
    GSocketTest lTest;
    lTest.run(_argc, _argv);
    m_logs.addLogs(lTest.getLogs());
}
//===============================================
void GTest::runOpenSSL(int _argc, char** _argv) {
    GOpenSSLTest lTest;
    lTest.run(_argc, _argv);
    m_logs.addLogs(lTest.getLogs());
}
//===============================================
void GTest::runTest(int _argc, char** _argv) {
    GStringTest lTest;
    lTest.run(_argc, _argv);
    m_logs.addLogs(lTest.getLogs());
}
//===============================================
