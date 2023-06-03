//===============================================
#include "GStringTest.h"
#include "GPcre.h"
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
    else if(lMethod == "lower") {
        runLower(_argc, _argv);
    }
    else {
        m_logs.addError("La méthode est inconnue.");
    }
}
//===============================================
void GStringTest::runTest(int _argc, char** _argv) {
    GString lData = ""
            "POST /readyapi-1.0 HTTP/1.1\r\n"
            "Host: readydev.ovh:9081\r\n"
            "Authorization: Basic YWRtaW46YWRtaW5wYXNz\r\n"
            "User-Agent: rdvapp/1.0\r\n"
            "Content-Type: application/xml\r\n"
            "Content-Length: 18500\r\n"
            "\r\n"
            "<rdv><datas><data><code>manager</code>"
            "<module>page</module>"
            "<method>save_page_file</method>"
            "";
    if(lData == GString()) {
        m_logs.addLog("lData == GString()");
    }
    if(lData != GString()) {
        m_logs.addLog("lData != GString()");
    }
    if(GString() == GString()) {
        m_logs.addLog("GString() == GString()");
    }
    if(GString() != GString()) {
        m_logs.addLog("GString() != GString()");
    }
    int posI = lData.indexOf("Content-Length:");
    int posJ = lData.indexOf("\r\n", posI + 1);
    int posK = lData.indexOf("\r\n\r\n", posI + 1);
    lData = lData.substr(posI, posJ - posI);
    m_logs.addLog(GFORMAT("posI  : [%d]", posI));
    m_logs.addLog(GFORMAT("posJ  : [%d]", posJ));
    m_logs.addLog(GFORMAT("posK  : [%d]", posK));
    m_logs.addLog(GFORMAT("lData : [%s]", lData.c_str()));
}
//===============================================
void GStringTest::runHttp(int _argc, char** _argv) {
    GPcre lPcre;

    lPcre.setPattern("([^\\s]+)\r\n");
    lPcre.setDataIn(""
            "POST /readyapi-1.0 HTTP/1.1\r\n"
            "Host: readydev.ovh:9081\r\n"
            "Authorization: Basic YWRtaW46YWRtaW5wYXNz\r\n"
            "User-Agent: rdvapp/1.0\r\n"
            "Content-Type: application/xml\r\n"
            "Content-Length: 18500\r\n"
            "\r\n"
            "<rdv><datas><data><code>manager</code>"
            "<module>page</module>"
            "<method>save_page_file</method>"
            "");
    lPcre.run();
    m_logs.addData(lPcre.serialize());
    m_logs.addLogs(lPcre.getLogs());
}
//===============================================
void GStringTest::runPcre(int _argc, char** _argv) {
    GPcre lPcre;

    lPcre.setPattern("From:([^@]+)@([^\r]+)");
    lPcre.setDataIn(""
            "From:regular.expressions@example.com\r\n"
            "From:exddd@43434.com\r\n"
            "From:7853456@exgem.com\r\n"
            "");
    lPcre.run();
    m_logs.addData(lPcre.serialize());
    m_logs.addLogs(lPcre.getLogs());
}
//===============================================
void GStringTest::runLower(int _argc, char** _argv) {
    GString lData = "BONJour TouT le MonDE.";
    m_logs.addData(lData.toLower());
    m_logs.addData(lData.toUpper());
}
//===============================================
