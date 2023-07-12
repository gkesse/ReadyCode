//===============================================
#include "GTest.h"
#include "GCurl.h"
//===============================================
GTest::GTest()
: GObject() {

}
//===============================================
GTest::~GTest() {

}
//===============================================
void GTest::run(int _argc, char** _argv) {
    GString lMethod = "";
    if(_argc > 2) lMethod = _argv[2];

    if(lMethod == "") {
        m_logs.addError("La méthode est obligatoire.");
    }
    else if(lMethod == "curl") {
        runCurl(_argc, _argv);
    }
    else {
        m_logs.addError("La méthode est inconnue.");
    }
}
//===============================================
void GTest::runCurl(int _argc, char** _argv) {
    GCurl lCurl;
    GString lData = lCurl.postHttpFacade("calculator", "run_calculator");
    m_logs.addLogs(lCurl.getLogs());
    if(!m_logs.hasErrors()) {
        m_logs.addData(lData);
    }
}
//===============================================
