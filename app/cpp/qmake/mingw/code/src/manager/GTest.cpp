//===============================================
#include "GTest.h"
#include "GPath.h"
#include "GXml.h"
#include "GConsole.h"
#include "GSocket.h"
//===============================================
GTest::GTest(QObject* _parent) :
GObject(_parent) {

}
//===============================================
GTest::~GTest() {

}
//===============================================
void GTest::run(int _argc, char** _argv) {
	QString lKey = "default";
	if(_argc > 2) lKey = _argv[2];

	if(lKey == "default") {
		runTest(_argc, _argv);
	}
    // path
    else if(lKey == "path") {
        runPath(_argc, _argv);
    }
    // xml
    else if(lKey == "xml") {
        runXml(_argc, _argv);
    }
    // socket
    else if(lKey == "socket/server") {
        runSocketServer(_argc, _argv);
    }
    else if(lKey == "socket/client") {
        runSocketClient(_argc, _argv);
    }
	// end
	else {
		runTest(_argc, _argv);
	}
}
//===============================================
void GTest::runTest(int _argc, char** _argv) {
	printf("%s\n", __FUNCTION__);
}
//===============================================
void GTest::runPath(int _argc, char** _argv) {
    printf("%s\n", __FUNCTION__);
    QString lPath = GRES("xml", "app.xml");
    console(lPath);
}
//===============================================
void GTest::runXml(int _argc, char** _argv) {
    printf("%s\n", __FUNCTION__);
    GXml lXml;
    lXml.loadXmlFile(GRES("xml", "pad.xml"));
    lXml.createXPath();
    lXml.queryXPath(QString("/rdv/datas/data[code='pad']/title"));
    lXml.getNodeXPath();
    QString lData = lXml.getNodeValue();
    console(lData);
}
//===============================================
void GTest::runSocketServer(int _argc, char** _argv) {
    printf("%s\n", __FUNCTION__);
    GSocket lServer;
    GSocket lClient;

    int lMajor = lServer.getItem("socket", "major").toInt();
    int lMinor = lServer.getItem("socket", "minor").toInt();
    int lDomain = lServer.loadDomain();
    int lType = lServer.loadType();
    int lProtocol = lServer.loadProtocol();
    int lFamily = lServer.loadFamily();
    QString lClientIp = lServer.getItem("socket", "client_ip");
    int lPort = lServer.getItem("socket", "port").toInt();
    int lBacklog = lServer.getItem("socket", "backlog").toInt();

    lServer.initSocket(lMajor, lMinor);
    lServer.createSocket(lDomain, lType, lProtocol);
    lServer.createAddress(lFamily, lClientIp, lPort);
    lServer.bindSocket();
    lServer.listenSocket(lBacklog);
    lServer.startMessage();
    lServer.acceptSocket(lClient);

    QString lData;
    lClient.recvData(lData);
    console("=====>");
    console(lData);
    lClient.recvData(lData);
    console("=====>");
    console(lData);
    lClient.sendData("<result>ok</result>");

    lClient.closeSocket();
    lServer.closeSocket();
    lServer.cleanSocket();
}
//===============================================
void GTest::runSocketClient(int _argc, char** _argv) {
    printf("%s\n", __FUNCTION__);
    GSocket lClient;

    int lMajor = lClient.getItem("socket", "major").toInt();
    int lMinor = lClient.getItem("socket", "minor").toInt();
    int lDomain = lClient.loadDomain();
    int lType = lClient.loadType();
    int lProtocol = lClient.loadProtocol();
    int lFamily = lClient.loadFamily();
    QString lServerIp = lClient.getItem("socket", "server_ip");
    int lPort = lClient.getItem("socket", "port").toInt();

    lClient.initSocket(lMajor, lMinor);
    lClient.createSocket(lDomain, lType, lProtocol);
    lClient.createAddress(lFamily, lServerIp, lPort);
    lClient.connectSocket();

    QString lData;
    lClient.sendData("Bonjour tout le monde");
    lClient.sendData("Voici mon premier test");
    lClient.recvData(lData);

    console("=====>");
    console(lData);

    lClient.closeSocket();
    lClient.cleanSocket();
}
//===============================================
