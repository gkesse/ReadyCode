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
        m_logs.addError("Erreur la méthode est obligatoire.");
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
    else {
        m_logs.addError("Erreur la méthode est inconnue.");
    }
}
//===============================================
void GXmlTest::runTest(int _argc, char** _argv) {
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
    lPage.print();

    m_logs.addData(lPage.serialize());
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
    lPage.print();

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
