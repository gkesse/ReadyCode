//===============================================
#include "GSocketTest.h"
#include "GSocket.h"
#include "GLog.h"
//===============================================
GSocketTest::GSocketTest(const GString& _code)
: GObject(_code) {

}
//===============================================
GSocketTest::~GSocketTest() {

}
//===============================================
void GSocketTest::run(int _argc, char** _argv) {
    GString lKey;
    if(_argc > 3) lKey = _argv[3];
    if(lKey == "server/tcp/echo") {
        runServerTcpEcho(_argc, _argv);
    }
    else if(lKey == "server/udp") {
        runServerUdp(_argc, _argv);
    }
    else {
        runDefault(_argc, _argv);
    }
}
//===============================================
void GSocketTest::runDefault(int _argc, char** _argv) {
    GLOGT(eGFUN, "Le process est inconnu.");
}
//===============================================
void GSocketTest::runServerTcpEcho(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    GSocket lSocket;
    lSocket.setModule(GSocket::SOCKET_SERVER_TCP);
    lSocket.setProtocol(GSocket::PROTOCOL_ECHO);
    lSocket.runServer();
}
//===============================================
void GSocketTest::runServerUdp(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
}
//===============================================
