//===============================================
#include "GProcess.h"
#include "GTest.h"
#include "GSocket.h"
#include "GOpenSSL.h"
//===============================================
GProcess::GProcess()
: GObject() {

}
//===============================================
GProcess::~GProcess() {

}
//===============================================
void GProcess::init() {
    // libxml2
    xmlInitParser();
    // openssl
    SSL_library_init();
    OpenSSL_add_all_algorithms();
    SSL_load_error_strings();
    // curl
    curl_global_init(CURL_GLOBAL_ALL);
}
//===============================================
void GProcess::clean() {
    // libxml2
    xmlCleanupParser();
    xmlMemoryDump();
    // curl
    curl_global_cleanup();
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
    else if(lModule == "server_ssl") {
        runServerSSL(_argc, _argv);
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
void GProcess::runServerSSL(int _argc, char** _argv) {
    GOpenSSL lObj;
    lObj.runServer();
    m_logs.addLogs(lObj.getLogs());
}
//===============================================
