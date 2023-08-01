//===============================================
#include "GTest.h"
#include "GString.h"
#include "GLog.h"
#include "GXml.h"
#include "GCode.h"
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
