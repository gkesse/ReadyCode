//===============================================
#include "GProcess.h"
#include "GSocket.h"
#include "GLog.h"
#include "GTest.h"
//===============================================
GProcess::GProcess()
: GObject() {

}
//===============================================
GProcess::~GProcess() {

}
//===============================================
void GProcess::run(int _argc, char** _argv) {
    GString lKey;
    if(_argc > 1) lKey = _argv[1];
    if(lKey == "test") {
        runTest(_argc, _argv);
    }
    else if(lKey == "server") {
        runServer(_argc, _argv);
    }
    else {
        runDefault(_argc, _argv);
    }
}
//===============================================
void GProcess::runDefault(int _argc, char** _argv) {
    GLOGT(eGMSG, "Le process est inconnu.");
}
//===============================================
void GProcess::runTest(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    GTest lObj;
    lObj.run(_argc, _argv);
}
//===============================================
void GProcess::runServer(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    GSocket lSocket;
    lSocket.setModule(GSocket::SOCKET_SERVER_TCP);
    lSocket.setProtocol(GSocket::PROTOCOL_RDVAPP);
    lSocket.runServer();
}
//===============================================
