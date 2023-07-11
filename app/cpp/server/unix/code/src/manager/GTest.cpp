//===============================================
#include "GTest.h"
#include "GString.h"
#include "GLog.h"
#include "GXml.h"
#include "GCode.h"
#include "GSocket.h"
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

    if(lMethod == "string") {
        runTest(_argc, _argv);
    }
    else if(lMethod == "log") {
        runLog(_argc, _argv);
    }
    else if(lMethod == "xml") {
        runXml(_argc, _argv);
    }
    else if(lMethod == "code") {
        runCode(_argc, _argv);
    }
    else if(lMethod == "socket_client") {
        runSocket(_argc, _argv);
    }
}
//===============================================
void GTest::runTest(int _argc, char** _argv) {
    printf("%s...\n", __FUNCTION__);

    // copie - affectation
    GString lData = "Bonjour tout le monde.";
    lData.print();
    lData = "Bonjour tout le monde (2).";
    lData.print();
}
//===============================================
void GTest::runLog(int _argc, char** _argv) {
    printf("%s...\n", __FUNCTION__);
    GLog lLog;
    GLog lLogC;

    // addError - addData - addLog - addLogs - serialize
    lLog.addError("La connexion au serveur a échoué.");
    lLog.addData("La résolution de l'écran est :  1200 x 970.");
    lLog.addLog("Le chargement du module est terminé.");
    lLog.loadFromMap(2);
    lLog.serialize().print();
    m_logs.addLogs(lLog);

    // deserialize
    lLogC.deserialize(lLog.serialize());
    lLogC.serialize().print();
}
//===============================================
void GTest::runXml(int _argc, char** _argv) {
    printf("%s...\n", __FUNCTION__);
    GXml lDom;
    GXml lDomC;

    // createDoc - setNode - addObj - addData - toString
    lDom.createDoc();
    lDomC.setNode(lDom.addObj("datas"));
    lDomC.setNode(lDomC.addObj("data"));
    lDomC.addData("code", "logs");
    lDomC.addData("type", "error");
    lDomC.addData("side", "server_cpp");
    lDomC.addData("msg", "La connexion au serveur a échoué.");
    lDom.toString().print();

    // getNode - toNode
    lDomC.setNode(lDom.getNode(lDom, sformat("/rdv/datas/data")));
    lDomC.toNode(lDom).print();

    // createNode
    lDom.createDoc();
    lDom.createNode(lDom, sformat("/rdv/datas/data"));
    lDomC.setNode(lDom.createNode(lDom, sformat("/rdv/datas/data")));
    lDomC.createNode(lDom, sformat("rdv/datas/data"));
    lDomC.createNode(lDom, sformat("rdv/datas/data"));
    lDom.toString().print();
}
//===============================================
void GTest::runCode(int _argc, char** _argv) {
    printf("%s...\n", __FUNCTION__);
    GCode lDom;

    // createDatas - createCode - addData
    lDom.createDoc();
    lDom.createDatas();
    lDom.createDatas();
    lDom.createCode("logs");
    lDom.createCode("logs");
    lDom.addData("logs", "type", "error");
    lDom.toString().print();
    lDom.addData("logs", "type", "log");
    lDom.toString().print();

    // createDatas - createCode - addData
    lDom.createDoc();
    lDom.addData("manager", "module", "logs");
    lDom.toString().print();
}
//===============================================
void GTest::runSocket(int _argc, char** _argv) {
    printf("%s...\n", __FUNCTION__);
    GSocket lClient;
    GLog lLog;

    // callFacade
    lLog.addError("La connexion au serveur a échoué.");
    lLog.addData("La résolution de l'écran est :  1200 x 970.");
    lLog.addLog("Le chargement du module est terminé.");
    lLog.loadFromMap(2);
    GString lData = lClient.callFacade("logs", "save_logs", lLog.serialize());
    lData.print();
}
//===============================================
