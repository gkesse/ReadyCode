//===============================================
#include "GTest.h"
#include "GString.h"
#include "GLog.h"
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
        runString(_argc, _argv);
    }
    else if(lMethod == "log") {
        runLog(_argc, _argv);
    }
}
//===============================================
void GTest::runString(int _argc, char** _argv) {
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

    // addError - addData - addLog - addLogs
    GLog lLog;
    lLog.addError("La connexion au serveur a échoué.");
    lLog.addData("La résolution de l'écran est :  1200 x 970.");
    lLog.addLog("Le chargement du module est terminé.");
    lLog.print();
    m_logs.addLogs(lLog);
}
//===============================================
