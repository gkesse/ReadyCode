//===============================================
#include "GProcess.h"
#include "GTest.h"
#include "GSocket.h"
//===============================================
GProcess::GProcess()
: GObject() {

}
//===============================================
GProcess::~GProcess() {

}
//===============================================
void GProcess::init() {
    SetConsoleOutputCP(CP_UTF8);
    xmlInitParser();
}
//===============================================
void GProcess::clean() {
    xmlCleanupParser();
    xmlMemoryDump();
}
//===============================================
void GProcess::run(int _argc, char** _argv) {
    GString lModule = "";
    if(_argc > 1) lModule = _argv[1];

    if(lModule == "") {
        m_logs.addError("Le module est obligatoire.");
    }
    else if(lModule == "test") {
        runTest(_argc, _argv);
    }
    else if(lModule == "client") {
        runClient(_argc, _argv);
    }
    else {
        m_logs.addError("Le module est inconnu.");
    }
}
//===============================================
void GProcess::runTest(int _argc, char** _argv) {
    GTest lObj;
    lObj.run(_argc, _argv);
    m_logs.addLogs(lObj.getLogs());
}
//===============================================
void GProcess::runClient(int _argc, char** _argv) {

}
//===============================================
