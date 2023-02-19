//===============================================
#include "GStringTest.h"
#include "GPage.h"
//===============================================
GStringTest::GStringTest()
: GObject() {

}
//===============================================
GStringTest::~GStringTest() {

}
//===============================================
void GStringTest::run(int _argc, char** _argv) {
    GString lMethod;
    if(_argc > 2) lMethod = _argv[2];
    if(lMethod == "") {
        m_logs.addError("La méthode est obligatoire.");
    }
    else if(lMethod == "test") {
        runTest(_argc, _argv);
    }
    else {
        m_logs.addError("La méthode est inconnue.");
    }
}
//===============================================
void GStringTest::runTest(int _argc, char** _argv) {
    GString lData = "BONJour TouT le MonDE.";
    m_logs.addData(lData.toLower());
    m_logs.addData(lData.toUpper());
}
//===============================================
