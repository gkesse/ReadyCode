//===============================================
#include "GTest.h"
#include "GPath.h"
#include "GXml.h"
#include "GRequest.h"
#include "GCode.h"
#include "GConsole.h"
#include "GSocket.h"
#include "GFile.h"
#include "GThread.h"
#include "GTimer.h"
#include "GMaster.h"
//===============================================
GTest* GTest::m_test = 0;
//===============================================
GTest::GTest(QObject* _parent) :
GObject(_parent) {
    m_server = 0;
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
    else if(lKey == "socket/server/write") {
        runSocketServerWrite(_argc, _argv);
    }
    else if(lKey == "socket/client/write") {
        runSocketClientWrite(_argc, _argv);
    }
    else if(lKey == "socket/server/start") {
        runSocketServerStart(_argc, _argv);
    }
    else if(lKey == "socket/client/start") {
        runSocketClientStart(_argc, _argv);
    }
    // thread
    else if(lKey == "thread") {
        runThread(_argc, _argv);
    }
    // timer
    else if(lKey == "timer") {
        runTimer(_argc, _argv);
    }
    // request
    else if(lKey == "request") {
        runRequest(_argc, _argv);
    }
    else if(lKey == "request/send") {
        runRequestSend(_argc, _argv);
    }
    // response
    else if(lKey == "response") {
        runResponse(_argc, _argv);
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
    lClient.sendData("<result>ok</result>");

    console("=====>");
    console(lData);

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
    lClient.recvData(lData);

    console("=====>");
    console(lData);

    lClient.closeSocket();
    lClient.cleanSocket();
}
//===============================================
void GTest::runSocketServerWrite(int _argc, char** _argv) {
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
    lClient.readData(lData);
    lClient.writeData("<result>ok</result>");

    console("=====>");
    console(lData);

    lClient.closeSocket();
    lServer.closeSocket();
    lServer.cleanSocket();
}
//===============================================
void GTest::runSocketClientWrite(int _argc, char** _argv) {
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
    lClient.writeData(GFile(GRES("xml", "pad.xml")).getData());
    lClient.readData(lData);

    console("=====>");
    console(lData);

    lClient.closeSocket();
    lClient.cleanSocket();
}
//===============================================
void GTest::runSocketServerStart(int _argc, char** _argv) {
    printf("%s\n", __FUNCTION__);
    m_test = new GTest;
    m_test->m_server = new GSocket;
    GThread lThread;
    GTimer lTimer;
    lThread.createThread((void*)onSocketServerStartThread, this);
    lTimer.setTimer((void*)onSocketServerStartTimer, 100);
    lTimer.pauseTimer();
}
//===============================================
DWORD WINAPI GTest::onSocketServerStartThread(LPVOID _params) {
    printf("%s\n", __FUNCTION__);
    GSocket* lServer = m_test->m_server;
    lServer->startServer((void*)GSocket::onServerThread);
    return 0;
}
//===============================================
VOID CALLBACK GTest::onSocketServerStartTimer(HWND, UINT, UINT_PTR, DWORD) {
    GSocket* lServer = m_test->m_server;
    QStack<QString>& lDataIns = lServer->getDataIns();
    QStack<GSocket*>& lClientIns = lServer->getClientIns();

    if(!lDataIns.empty()) {
        QString lDataIn = lDataIns.front();
        GSocket* lClient = lClientIns.front();
        lDataIns.pop();
        lClientIns.pop();
        GMaster lMaster(lDataIn);
        lMaster.onModule(lDataIn, lClient);
        lMaster.sendResponse(lClient);
    }
}
//===============================================
void GTest::runSocketClientStart(int _argc, char** _argv) {
    printf("%s\n", __FUNCTION__);
    GSocket lClient;

    QString lData = GFile(GRES("xml", "pad.xml")).getData();
    lData = lClient.callServer(lData);

    console("=====>");
    console(lData);

    lClient.closeSocket();
    lClient.cleanSocket();
}
//===============================================
void GTest::runThread(int _argc, char** _argv) {
    printf("%s\n", __FUNCTION__);
    GThread lThread;
    lThread.createThread((void*)onThread, 0);
    system("pause");
}
//===============================================
DWORD WINAPI GTest::onThread(LPVOID _params) {
    printf("%s\n", __FUNCTION__);
    int lCount = 10;
    for(int i = 0; i < lCount; i++) {
        console(QString("[%1] : Bonjour tout le monde").arg(i));
    }
    return 0;
}
//===============================================
void GTest::runTimer(int _argc, char** _argv) {
    printf("%s\n", __FUNCTION__);
    GTimer lTimer;
    lTimer.setTimer((void*)onTimer, 1000);
    lTimer.pauseTimer();
}
//===============================================
VOID CALLBACK GTest::onTimer(HWND, UINT, UINT_PTR, DWORD) {
    printf("%s\n", __FUNCTION__);
}
//===============================================
void GTest::runRequest(int _argc, char** _argv) {
    printf("%s\n", __FUNCTION__);
    GXml lReq;
    lReq.createDoc("1.0");
    lReq.createRoot("rdv");
    lReq.createXPath();
    lReq.createNodePath("/rdv/module", "user");
    lReq.createNodePath("/rdv/method", "save_user");
    lReq.createNodePath("/rdv/data/firstname", "Gerard");
    lReq.createNodePath("/rdv/data/lastname", "KESSE");
    console(lReq.toString());
}
//===============================================
void GTest::runRequestSend(int _argc, char** _argv) {
    printf("%s\n", __FUNCTION__);
    GRequest lReq;
    GSocket lClient;
    lReq.createRequest("usero", "save_user");
    QString lResponse = lClient.callServer(lReq.toString());
    console(lResponse);
}
//===============================================
void GTest::runResponse(int _argc, char** _argv) {
    printf("%s\n", __FUNCTION__);
    GCode lRes;
    lRes.createDoc("1.0", "rdv");
    lRes.createCode("result", "msg", "ok");
    lRes.createCode("opencv", "version", "4.0");
    lRes.createMap("error", "map", "msg", "le chemin est incorrect");
    lRes.createMap("error", "map", "msg", "la donnee est incorrect");
    console("=====>");
    console(lRes.hasCode("result"));        // true
    console("=====>");
    console(lRes.hasCode("resulto"));       // false
    console("=====>");
    console(lRes.hasCode("error"));         // true
    console("=====>");
    console(lRes.hasCode("error", "msg"));  // true
    console("=====>");
    console(lRes.hasCode("error", "msgo")); // false
    console("=====>");
    console(lRes.toString());
}
//===============================================
