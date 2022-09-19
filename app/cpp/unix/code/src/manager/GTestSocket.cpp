//===============================================
#include "GTestSocket.h"
#include "GSocket2.h"
#include "GLog.h"
#include "GFormat.h"
//===============================================
GTestSocket* GTestSocket::m_test = 0;
//===============================================
GTestSocket::GTestSocket()
: GObject() {

}
//===============================================
GTestSocket::~GTestSocket() {

}
//===============================================
void GTestSocket::run(int _argc, char** _argv) {
    std::string lKey = "default";
    if(_argc > 2) lKey = _argv[2];

    if(lKey == "default") {
        runDefault(_argc, _argv);
    }
    else if(lKey == "tcp") {
        runTcp(_argc, _argv);
    }
    else if(lKey == "analyze") {
        runAnalyze(_argc, _argv);
    }
    else {
        runDefault(_argc, _argv);
    }
}
//===============================================
void GTestSocket::runDefault(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
}
//===============================================
void GTestSocket::runTcp(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    GSocket2 lSocket;
    lSocket.setModule("tcp");
    lSocket.setHostname("192.168.1.45");
    lSocket.setPort(9001);
    lSocket.setDomain(AF_INET);
    lSocket.setType(SOCK_STREAM);
    lSocket.setProtocol(IPPROTO_TCP);
    lSocket.setFamily(AF_INET);
    lSocket.setBacklog(5);
    lSocket.setMessage("Démarrage du serveur...");
    lSocket.run();
}
//===============================================
void GTestSocket::runAnalyze(int _argc, char** _argv) {
    GString2 lDataIn = "RDVAPP;api_key:12345|username:porto|password:key|size:25;Bonjour tout le monde";
    if(lDataIn.startBy("RDVAPP")) {
        GString2 lMethod = lDataIn.extract(0, ";");
        GString2 lHeader = lDataIn.extract(1, ";");

        GLOGT(eGMSG, "%s", lMethod.c_str());
        GLOGT(eGMSG, "%s", lHeader.c_str());

        for(int i = 0; i < lHeader.count("|"); i++) {
            GString2 lWord = lHeader.extract(i, "|");
            GLOGT(eGMSG, "%s", lWord.c_str());
        }
    }
}
//===============================================
