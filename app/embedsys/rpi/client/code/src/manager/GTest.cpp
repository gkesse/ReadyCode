//===============================================
#include "GTest.h"
#include "GString.h"
#include "GLog.h"
#include "GXml.h"
#include "GCode.h"
#include "GShell.h"
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

    if(lMethod == "") {
        m_logs.addError("La méthode est obligatoire.");
    }
    else if(lMethod == "string") {
        runString(_argc, _argv);
    }
    else if(lMethod == "shell") {
        runShell(_argc, _argv);
    }
    else {
        m_logs.addError("La méthode est inconnue.");
    }
}
//===============================================
void GTest::runString(int _argc, char** _argv) {
    printf("%s...\n", __FUNCTION__);

    // copy - assign - print
    GString lData = "Bonjour tout le monde.";
    lData.print();
    lData = "Bonjour tout le monde (2).";
    lData.print();

    // indexOf
    int lIndex = lData.indexOf("tout");
    printf("%d\n", lIndex);

    // indexOf
    GString lExtract = lData.extractData("Bonjour", "le");
    sformat("[%s]", lExtract.c_str()).print();
}
//===============================================
void GTest::runShell(int _argc, char** _argv) {
    printf("%s...\n", __FUNCTION__);
    GString lAction = "system";
    GShell lShell;
    GString lData;

    if(_argc > 3) lAction = _argv[3];

    if(lAction == "") {
        m_logs.addError("L'action est obligatoire.");
    }
    else if(lAction == "system") {
        // runSystem
        lShell.runSystem("tree");
    }
    else if(lAction == "cmd") {
        // runCmd
        lData = lShell.runCmd("tree");
        lData.print();
    }
    else {
        m_logs.addError("L'action est inconnue.");
    }
}
//===============================================
