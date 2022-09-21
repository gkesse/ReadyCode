//===============================================
#include "GTestSocket.h"
#include "GLog.h"
#include "GFormat.h"
#include "GSocket2.h"
#include "GXml2.h"
#include "GCode2.h"
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
    else if(lKey == "xml") {
        runXml(_argc, _argv);
    }
    else if(lKey == "code") {
        runCode(_argc, _argv);
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
        GString2 lMethod = lDataIn.extract(0, ";").trim();
        GString2 lHeader = lDataIn.extract(1, ";").trim();
        int lCount = lHeader.count("|");
        for(int i = 0; i < lCount; i++) {
            GString2 lWord = lHeader.extract(i, "|").trim();
            if(lWord.startBy("api_key")) {
                GString2 lData = lWord.extract(1, ":").trim();
                GLOGT(eGMSG, "%s", lData.c_str());
            }
            else if(lWord.startBy("username")) {
                GString2 lData = lWord.extract(1, ":").trim();
                GLOGT(eGMSG, "%s", lData.c_str());
            }
            else if(lWord.startBy("size")) {
                GString2 lData = lWord.extract(1, ":").trim();
                GLOGT(eGMSG, "%s", lData.c_str());
            }
        }
    }

    int lSize = lDataIn.sepSize(1, ";");
    GString2 lData = lDataIn.substr(lSize);
    GLOGT(eGMSG, "%s", lData.c_str());
}
//===============================================
void GTestSocket::runXml(int _argc, char** _argv) {
    GXml2 lXml;
    lXml.createDoc();
    lXml.createNodePath("rdv/datas");
    lXml.createNodePath("rdv/datas");
    lXml.createNodePath("rdv/datas");
    lXml.toString().print();
}
//===============================================
void GTestSocket::runCode(int _argc, char** _argv) {
    GCode2 lCode;
    lCode.createDoc();
    lCode.addData("menu", "nom", "gerard");
    lCode.addData("menu", "nom", "tia");
    lCode.addData("menu", "nom", "kesse");
    lCode.addData("titre", "nom", "gerard");
    lCode.addData("titre", "nom", "tia");
    lCode.addData("titre", "nom", "key");
    lCode.toString().print();
}
//===============================================
