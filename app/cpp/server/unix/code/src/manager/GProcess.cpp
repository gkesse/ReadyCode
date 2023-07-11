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

    if(lModule == "test") {
        runTest(_argc, _argv);
    }
    else if(lModule == "server") {
        runServer(_argc, _argv);
    }
}
//===============================================
void GProcess::runTest(int _argc, char** _argv) {
    GTest lObj;
    lObj.run(_argc, _argv);
    m_logs.addLogs(lObj.getLogs());
}
//===============================================
void GProcess::runServer(int _argc, char** _argv) {
    GSocket lObj;
    lObj.runServer();
    m_logs.addLogs(lObj.getLogs());
}
//===============================================
