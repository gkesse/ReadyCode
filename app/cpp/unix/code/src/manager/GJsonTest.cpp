//===============================================
#include "GJsonTest.h"
//===============================================
GJsonTest::GJsonTest()
: GObject() {

}
//===============================================
GJsonTest::~GJsonTest() {

}
//===============================================
void GJsonTest::run(int _argc, char** _argv) {
    GString lMethod;
    if(_argc > 2) lMethod = _argv[2];
    if(lMethod == "") {
        m_logs.addError("Erreur la méthode est obligatoire.");
    }
    else if(lMethod == "test") {
        runTest(_argc, _argv);
    }
    else if(lMethod == "data") {
        runData(_argc, _argv);
    }
    else if(lMethod == "object") {
        runObject(_argc, _argv);
    }
    else {
        m_logs.addError("Erreur la méthode est inconnue.");
    }
}
//===============================================
void GJsonTest::runTest(int _argc, char** _argv) {
    GJson lJson(true);

    lJson.createObject();
    lJson.addData("code", "page");
    lJson.addData("name", "admin");
    lJson.addData("title", "Administration");
    lJson.addData("url", "home/admin");
    lJson.addData("path", "/path/home/admin.php");

    lJson.pushObject();
    lJson.createArray();

    for(int i = 0; i < 3; i++) {
        lJson.pushObject();
        lJson.createObject();
        lJson.addData("code", "page");
        lJson.addData("name", "admin");
        lJson.addData("title", "Administration");
        lJson.addData("url", "home/admin");
        lJson.addData("path", "/path/home/admin.php");
        lJson.initChild();
        lJson.popObject();
        lJson.initParent();
        lJson.addObject();
    }

    lJson.initChild();
    lJson.popObject();
    lJson.initParent();
    lJson.addObject("map");

    m_logs.addData(lJson.toString());
}
//===============================================
void GJsonTest::runObject(int _argc, char** _argv) {
    GJson lJson(true);

    lJson.createObject();
    lJson.addData("code", "page");
    lJson.addData("name", "admin");
    lJson.addData("title", "Administration");
    lJson.addData("url", "home/admin");
    lJson.addData("path", "/path/home/admin.php");

    lJson.pushObject();
    lJson.createArray();

    for(int i = 0; i < 3; i++) {
        lJson.pushObject();
        lJson.createObject();
        lJson.addData("code", "page");
        lJson.addData("name", "admin");
        lJson.addData("title", "Administration");
        lJson.addData("url", "home/admin");
        lJson.addData("path", "/path/home/admin.php");
        lJson.initChild();
        lJson.popObject();
        lJson.initParent();
        lJson.addObject();
    }

    lJson.initChild();
    lJson.popObject();
    lJson.initParent();
    lJson.addObject("map");

    m_logs.addData(lJson.toString());
}
//===============================================
void GJsonTest::runData(int _argc, char** _argv) {
    GJson lJson(true);

    lJson.createObject();
    lJson.addData("code", "page");
    lJson.addData("name", "admin");
    lJson.addData("title", "Administration");
    lJson.addData("url", "home/admin");
    lJson.addData("path", "/path/home/admin.php");

    lJson.pushObject();
    lJson.createArray();
    lJson.addData("un");
    lJson.addData("deux");
    lJson.addData("trois");
    lJson.addData("quatre");
    lJson.initChild();
    lJson.popObject();
    lJson.initParent();
    lJson.addObject("map");

    m_logs.addData(lJson.toString());
}
//===============================================
