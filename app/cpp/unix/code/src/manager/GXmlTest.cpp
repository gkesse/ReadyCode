//===============================================
#include "GXmlTest.h"
#include "GPage.h"
//===============================================
GXmlTest::GXmlTest()
: GObject() {

}
//===============================================
GXmlTest::~GXmlTest() {

}
//===============================================
void GXmlTest::run(int _argc, char** _argv) {
    GString lMethod;
    if(_argc > 2) lMethod = _argv[2];
    if(lMethod == "") {
        m_logs.addError("La méthode est obligatoire.");
    }
    else if(lMethod == "test") {
        runTest(_argc, _argv);
    }
    else if(lMethod == "node") {
        runNode(_argc, _argv);
    }
    else if(lMethod == "xnode") {
        runXNode(_argc, _argv);
    }
    else if(lMethod == "serialize") {
        runSerialize(_argc, _argv);
    }
    else if(lMethod == "dom") {
        runDom(_argc, _argv);
    }
    else {
        m_logs.addError("La méthode est inconnue.");
    }
}
//===============================================
void GXmlTest::runTest(int _argc, char** _argv) {
    GCode lDom;
    GString lPage;
    GString lType;
    lDom.createCode("page");
    lDom.createXNode("map");
    for(int i = 0; i < 3; i++) {
        lPage = GFORMAT("Page_%d", i);
        lType = GFORMAT("Type_%d", i);
        lDom.pushNode();
        lDom.createNode("data");
        lDom.next();
        lDom.createVNode("name", lPage);
        lDom.createVNode("type", lType);
        runTestNext(lDom);
        lDom.popNode();
    }
    m_logs.addData(lDom.toString());
}
//===============================================
void GXmlTest::runTestNext(GCode& _dom) {
    GString lPage;
    GString lType;
    _dom.createXNode("map");
    for(int i = 0; i < 3; i++) {
        lPage = GFORMAT("Page_%d", i);
        lType = GFORMAT("Type_%d", i);
        _dom.pushNode();
        _dom.createNode("data");
        _dom.next();
        _dom.createVNode("name", lPage);
        _dom.createVNode("type", lType);
        _dom.popNode();
    }
}
//===============================================
void GXmlTest::runDom(int _argc, char** _argv) {
    GCode lDom;

    lDom.addData("page", "name", "admin");
    lDom.addData("page", "title", "Administration");
    lDom.addData("page", "url", "home/admin");
    lDom.addData("page", "path", "/path/home/admin.php");

    lDom.addData("logs", "type", "error");
    lDom.addData("logs", "side", "server");
    lDom.addData("logs", "msg", "Erreur lors de la lecture des données.");

    lDom.getCode("page");
    lDom.createNode("map");
    lDom.next();

    for(int i = 0; i < 3; i++) {
        GCode lData;
        lData.addData("page", "id", i + 1);
        lData.addData("page", "name", "admin");
        lData.addData("page", "title", "Administration");
        lData.addData("page", "url", "home/admin");
        lData.addData("page", "path", "/path/home/admin.php");
        lDom.loadNode(lData.toData());
    }

    lDom.getCode("logs");
    lDom.createNode("map");
    lDom.next();

    for(int i = 0; i < 1; i++) {
        GCode lData;
        lData.addData("logs", "id", i + 1);
        lData.addData("logs", "type", "error");
        lData.addData("logs", "side", "server");
        lData.addData("logs", "msg", "Erreur lors de la lecture des données.");
        lDom.loadNode(lData.toData());
    }

    m_logs.addData(lDom.toJson());
}
//===============================================
void GXmlTest::runSerialize(int _argc, char** _argv) {
    GXml lXml;

    lXml.createXNode("/rdv/datas/data");

    lXml.createVNode("code", "page");
    lXml.createVNode("name", "admin");
    lXml.createVNode("title", "Administration");
    lXml.createVNode("url", "home/admin");
    lXml.createVNode("path", "/path/home/admin.php");

    lXml.createXNode("map");

    for(int i = 0; i < 3; i++) {
        lXml.pushNode();
        lXml.createXNode("data");
        lXml.createVNode("id", i + 1);
        lXml.createVNode("code", "page");
        lXml.createVNode("name", "admin");
        lXml.createVNode("title", "Administration");
        lXml.createVNode("url", "home/admin");
        lXml.createVNode("path", "/path/home/admin.php");
        lXml.popNode();
    }

    GPage lPage;
    lPage.deserialize(lXml.toString());

    m_logs.addData(lPage.serialize());
}
//===============================================
void GXmlTest::runXNode(int _argc, char** _argv) {
    GXml lXml;

    lXml.createXNode("/rdv/datas/data");

    lXml.createVNode("code", "page");
    lXml.createVNode("name", "admin");
    lXml.createVNode("title", "Administration");
    lXml.createVNode("url", "home/admin");
    lXml.createVNode("path", "/path/home/admin.php");

    lXml.createXNode("map");

    for(int i = 0; i < 3; i++) {
        lXml.pushNode();
        lXml.createXNode("data");
        lXml.createVNode("id", i + 1);
        lXml.createVNode("code", "page");
        lXml.createVNode("name", "admin");
        lXml.createVNode("title", "Administration");
        lXml.createVNode("url", "home/admin");
        lXml.createVNode("path", "/path/home/admin.php");
        lXml.popNode();
    }

    m_logs.addData(lXml.toString());
}
//===============================================
void GXmlTest::runNode(int _argc, char** _argv) {
    GXml lXml;

    lXml.createNode("rdv");
    lXml.next();
    lXml.createNode("datas");
    lXml.next();
    lXml.createNode("data");
    lXml.next();

    lXml.pushNode();
    lXml.createNode("code");
    lXml.next();
    lXml.setValue("page");
    lXml.popNode();

    lXml.pushNode();
    lXml.createNode("name");
    lXml.next();
    lXml.setValue("admin");
    lXml.popNode();

    lXml.pushNode();
    lXml.createNode("title");
    lXml.next();
    lXml.setValue("Administration");
    lXml.popNode();

    lXml.pushNode();
    lXml.createNode("url");
    lXml.next();
    lXml.setValue("home/admin");
    lXml.popNode();

    lXml.pushNode();
    lXml.createNode("path");
    lXml.next();
    lXml.setValue("/path/home/admin.php");
    lXml.popNode();

    m_logs.addData(lXml.toString());
}
//===============================================
