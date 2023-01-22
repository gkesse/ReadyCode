//===============================================
#include "GSocketTest.h"
#include "GSocket.h"
//===============================================
GSocketTest::GSocketTest()
: GObject() {

}
//===============================================
GSocketTest::~GSocketTest() {

}
//===============================================
void GSocketTest::run(int _argc, char** _argv) {
    GString lMethod;
    if(_argc > 2) lMethod = _argv[2];
    if(lMethod == "") {
        m_logs.addError("Erreur la méthode est obligatoire.");
    }
    else if(lMethod == "test") {
        runTest(_argc, _argv);
    }
    else if(lMethod == "server_tcp") {
        runServerTcp(_argc, _argv);
    }
    else {
        m_logs.addError("Erreur la méthode est inconnue.");
    }
}
//===============================================
void GSocketTest::runTest(int _argc, char** _argv) {
    GSocket lServer;
    lServer.setModule("server_tcp");
    lServer.setHostname("0.0.0.0");
    lServer.setPort(9081);
    lServer.setStartMessage("Démarrage du serveur...\n");
    lServer.setStopMessage("Arrêt du serveur...\n");
    lServer.run();
    m_logs.addLogs(lServer.getLogs());
}
//===============================================
void GSocketTest::runServerTcp(int _argc, char** _argv) {
    GSocket lServer;
    lServer.setModule("server_tcp");
    lServer.setHostname("0.0.0.0");
    lServer.setPort(9081);
    lServer.setStartMessage("Démarrage du serveur...\n");
    lServer.setStopMessage("Arrêt du serveur...\n");
    lServer.run();
    m_logs.addLogs(lServer.getLogs());
}
//===============================================
