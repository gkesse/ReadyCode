//===============================================
#include <GCode.h>
#include "GXml.h"
#include "GTestSocket.h"
#include "GLog.h"
#include "GSocket2.h"
#include "GModule2.h"
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
    GString lKey = "default";
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
    else if(lKey == "map") {
        runMap(_argc, _argv);
    }
    else if(lKey == "module") {
        runModule(_argc, _argv);
    }
    else if(lKey == "response") {
        runResponse(_argc, _argv);
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
    lSocket.runServer();
}
//===============================================
void GTestSocket::runAnalyze(int _argc, char** _argv) {
    GString lDataIn = "RDVAPP;api_key:12345|username:porto|password:key|size:25;Bonjour tout le monde";

    if(lDataIn.startBy("RDVAPP")) {
        GString lMethod = lDataIn.extract(0, ";").trim();
        GString lHeader = lDataIn.extract(1, ";").trim();
        int lCount = lHeader.countSep("|");
        for(int i = 0; i < lCount; i++) {
            GString lWord = lHeader.extract(i, "|").trim();
            if(lWord.startBy("api_key")) {
                GString lData = lWord.extract(1, ":").trim();
                GLOGT(eGMSG, "%s", lData.c_str());
            }
            else if(lWord.startBy("username")) {
                GString lData = lWord.extract(1, ":").trim();
                GLOGT(eGMSG, "%s", lData.c_str());
            }
            else if(lWord.startBy("size")) {
                GString lData = lWord.extract(1, ":").trim();
                GLOGT(eGMSG, "%s", lData.c_str());
            }
        }
    }

    int lSize = lDataIn.sepSize(1, ";");
    GString lData = lDataIn.substr(lSize);
    GLOGT(eGMSG, "%s", lData.c_str());
}
//===============================================
void GTestSocket::runXml(int _argc, char** _argv) {
    GXml lXml;
    lXml.createDoc();
    lXml.createNodePath("rdv/datas");
    lXml.createNodePath("rdv/datas");
    lXml.createNodePath("rdv/datas");
    lXml.toString().print();
}
//===============================================
void GTestSocket::runCode(int _argc, char** _argv) {
    GCode lCode;
    lCode.createDoc();
    lCode.addData("menu", "nom", "gerard");
    lCode.addData("menu", "nom", "tia");
    lCode.addData("menu", "nom", "kesse");
    lCode.addData("titre", "nom", "gerard");
    lCode.addData("titre", "nom", "tia");
    lCode.addData("titre", "nom", 1000);
    lCode.toString().print();
}
//===============================================
void GTestSocket::runMap(int _argc, char** _argv) {
    std::vector<GObject*> lMap;
    for(int i = 0; i < 5; i++) {
        GModule2* lModule = new GModule2;
        lModule->setModule(GFORMAT("module[%d]", i + 1));
        lModule->setMethod(GFORMAT("method[%d]", i + 1));
        lMap.push_back(lModule);
    }

    GString lCode = "request";

    GCode lDom;
    lDom.createDoc();
    lDom.addData("request", lMap);
    lDom.print();

    lDom.getData(lCode, lMap, new GModule2);
    lDom.getData(lCode, lMap, new GModule2);

    for(int i = 0; i < lMap.size(); i++) {
        GModule2* lModule = (GModule2*)lMap.at(i);
        lModule->serialize().print();
    }
}
//===============================================
void GTestSocket::runModule(int _argc, char** _argv) {
    GModule2 lModule;
    lModule.setModule("opencv");
    lModule.setMethod("create_image");
    lModule.print();
}
//===============================================
void GTestSocket::runResponse(int _argc, char** _argv) {
    GCode lDom;
    lDom.createDoc();

    lDom.print();
    GString lPath = "/rdv/datas/data[code]";
    int lCount = lDom.countNode(lPath);
    printf("%d\n", lCount);

    lDom.addData("user", "name", "Gerard KESSE");
    lDom.addData("user", "id", "123456");

    lDom.print();
    lCount = lDom.countNode(lPath);
    printf("%d\n", lCount);

    lDom.addData("person", "name", "Gerard KESSE");
    lDom.addData("person", "id", "123456");

    lDom.print();
    lCount = lDom.countNode(lPath);
    printf("%d\n", lCount);
}
//===============================================
