//===============================================
#include "GTest.h"
#include "GPocoTest.h"
#include "GCurlTest.h"
#include "GSocketTest.h"
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
    if(_argc > 2) lModule = _argv[2];
    if(lModule == "") {
        m_logs.addError("Erreur le module est obligatoire.");
    }
    else if(lModule == "poco") {
        runPoco(_argc, _argv);
    }
    else if(lModule == "curl") {
        runCurl(_argc, _argv);
    }
    else if(lModule == "socket") {
        runSocket(_argc, _argv);
    }
    else {
        m_logs.addError("Erreur le module est inconnu.");
    }
}
//===============================================
void GTest::runPoco(int _argc, char** _argv) {
    GPocoTest lPoco;
    lPoco.run(_argc, _argv);
    m_logs.add(lPoco.m_logs);
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
