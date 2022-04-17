//===============================================
#include "GTest.h"
#include "GPath.h"
#include "GXml.h"
#include "GCode.h"
#include "GSocket.h"
#include "GFile.h"
#include "GThread.h"
#include "GTimer.h"
#include "GMaster.h"
#include "GLog.h"
//===============================================
GTest* GTest::m_test = 0;
//===============================================
GTest::GTest(QObject* _parent) : GModule(_parent) {
    m_server = 0;
}
//===============================================
GTest::GTest(const QString& _req, QObject* _parent) : GModule(_req, _parent) {
    m_server = 0;
}
//===============================================
GTest::~GTest() {

}
//===============================================
void GTest::run(int _argc, char** _argv) {
	QString lKey = "default";
	if(_argc > 2) lKey = _argv[2];

	if(lKey == "test") {
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
    else if(lKey == "request/save_user") {
        runRequestSaveUser(_argc, _argv);
    }
    else if(lKey == "request/get_user") {
        runRequestGetUser(_argc, _argv);
    }
    else if(lKey == "request/error") {
        runRequestError(_argc, _argv);
    }
    // response
    else if(lKey == "response") {
        runResponse(_argc, _argv);
    }
    // string
    else if(lKey == "string/pad") {
        runStringPad(_argc, _argv);
    }
    else if(lKey == "string/sub") {
        runStringSub(_argc, _argv);
    }
    // end
    else {
        runDefault(_argc, _argv);
    }
}
//===============================================
void GTest::runDefault(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
}
//===============================================
void GTest::runTest(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
}
//===============================================
void GTest::runPath(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    QString lPath = GRES("xml", "app.xml");
    GLOGW(eGINF, lPath);
}
//===============================================
void GTest::runXml(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    GXml lXml;
    lXml.loadXmlFile(GRES("xml", "pad.xml"));
    lXml.createXPath();
    lXml.queryXPath(QString("/rdv/datas/data[code='pad']/title"));
    lXml.getNodeXPath();
    QString lData = lXml.getNodeValue();
    GLOGW(eGINF, lData);
}
//===============================================
void GTest::runSocketServer(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
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

    GLOGW(eGINF, lData);

    lClient.closeSocket();
    lServer.closeSocket();
    lServer.cleanSocket();
}
//===============================================
void GTest::runSocketClient(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
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

    GLOGW(eGINF, lData);

    lClient.closeSocket();
    lClient.cleanSocket();
}
//===============================================
void GTest::runSocketServerWrite(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
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

    GLOGW(eGINF, lData);

    lClient.closeSocket();
    lServer.closeSocket();
    lServer.cleanSocket();
}
//===============================================
void GTest::runSocketClientWrite(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
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
    lClient.writeData(GFile(GRES("xml", "pad.xml")).getContent());
    lClient.readData(lData);

    GLOGW(eGINF, lData);

    lClient.closeSocket();
    lClient.cleanSocket();
}
//===============================================
void GTest::runSocketServerStart(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
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
    GLOGT(eGFUN, "");
    GSocket* lServer = m_test->m_server;
    lServer->startServer((void*)GSocket::onServerThread);
    return 0;
}
//===============================================
VOID CALLBACK GTest::onSocketServerStartTimer(HWND, UINT, UINT_PTR, DWORD) {
    GSocket* lServer = m_test->m_server;
    QStack<GSocket*>& lClientIns = lServer->getClientIns();

    if(!lClientIns.empty()) {
        GSocket* lClient = lClientIns.front();
        lClientIns.pop();
        GMaster lMaster(lClient->getRequest());
        lMaster.onModule(lClient);
        lMaster.sendResponse(lClient);
    }
}
//===============================================
void GTest::runSocketClientStart(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    GSocket lClient;

    QString lData = GFile(GRES("xml", "pad.xml")).getContent();
    lData = lClient.callServer(lData);

    GLOGW(eGINF, lData);

    lClient.closeSocket();
    lClient.cleanSocket();
}
//===============================================
void GTest::runThread(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    GThread lThread;
    lThread.createThread((void*)onThread, 0);
    system("pause");
}
//===============================================
DWORD WINAPI GTest::onThread(LPVOID _params) {
    GLOGT(eGFUN, "");
    int lCount = 10;
    for(int i = 0; i < lCount; i++) {
        GLOGW(eGINF, QString("[%1] : Bonjour tout le monde").arg(i));
    }
    return 0;
}
//===============================================
void GTest::runTimer(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    GTimer lTimer;
    lTimer.setTimer((void*)onTimer, 1000);
    lTimer.pauseTimer();
}
//===============================================
VOID CALLBACK GTest::onTimer(HWND, UINT, UINT_PTR, DWORD) {
    GLOGT(eGFUN, "");
}
//===============================================
void GTest::runRequest(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    GXml lReq;
    lReq.createDoc("1.0");
    lReq.createRoot("rdv");
    lReq.createXPath();
    lReq.createNodePath("/rdv/module", "user");
    lReq.createNodePath("/rdv/method", "save_user");
    lReq.createNodePath("/rdv/data/firstname", "Gerard");
    lReq.createNodePath("/rdv/data/lastname", "KESSE");
    GLOGW(eGINF, lReq.toString());
}
//===============================================
void GTest::runRequestSend(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    GCode lReq;
    GSocket lClient;
    lReq.createRequest("test", "request_send");
    QString lResponse = lClient.callServer(lReq.toString());
    GLOGW(eGINF, lReq.toString());
    GLOGW(eGINF, lResponse);
}
//===============================================
void GTest::runRequestSaveUser(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    GCode lReq;
    GSocket lClient;
    lReq.createRequest("test", "save_user");
    lReq.createCode("parameters", "firstname", "Gerard");
    lReq.createCode("parameters", "lastname", "KESSE");
    QString lResponse = lClient.callServer(lReq.toString());
    GERROR_LOAD(eGERR, lResponse);
    GLOGW(eGINF, lReq.toString());
    GLOGW(eGINF, lResponse);
}
//===============================================
void GTest::runRequestGetUser(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    GCode lReq;
    GSocket lClient;
    lReq.createRequest("test", "get_user");
    QString lResponse = lClient.callServer(lReq.toString());
    GERROR_LOAD(eGERR, lResponse);
    GCode lRes(lResponse);
    GLOGT(eGINF, "");
    GLOGW(eGINF, lReq.toString());
    GLOGT(eGINF, "");
    GLOGW(eGINF, lResponse);
    GLOGT(eGINF, "");
    GLOGW(eGINF, QString("firstname.....: %1").arg(lRes.getItem("user", "firstname")));
    GLOGW(eGINF, QString("lastname......: %1").arg(lRes.getItem("user", "lastname")));
}
//===============================================
void GTest::runRequestError(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    GCode lReq;
    GSocket lClient;
    lReq.createRequest("test", "error");
    QString lResponse = lClient.callServer(lReq.toString());
    GERROR_LOAD(eGERR, lResponse);
    GLOGT(eGINF, "");
    GLOGW(eGINF, lReq.toString());
    GLOGT(eGINF, "");
    GLOGW(eGINF, lResponse);
}
//===============================================
void GTest::runResponse(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    GCode lRes;
    lRes.createDoc("1.0", "rdv");
    lRes.createCode("request", "module", "test");
    lRes.createCode("request", "method", "save_user");
    lRes.createCode("result", "msg", "ok");
    lRes.createCode("opencv", "version", "4.0");
    lRes.createMap("error", "msg", "le chemin est incorrect");
    lRes.createMap("error", "msg", "la donnee est incorrect");
    GLOGT(eGINF, "");
    GLOGW(eGINF, GSTRC(lRes.hasCode("result")));        // true
    GLOGT(eGINF, "");
    GLOGW(eGINF, GSTRC(lRes.hasCode("resulto")));       // false
    GLOGT(eGINF, "");
    GLOGW(eGINF, GSTRC(lRes.hasCode("error")));         // true
    GLOGT(eGINF, "");
    GLOGW(eGINF, GSTRC(lRes.hasCode("error", "msg")));  // true
    GLOGT(eGINF, "");
    GLOGW(eGINF, GSTRC(lRes.hasCode("error", "msgo"))); // false
    GLOGT(eGINF, "");
    GLOGW(eGINF, QString("module.....: %1").arg(lRes.getItem("request", "module")));
    GLOGW(eGINF, QString("method.....: %1").arg(lRes.getItem("request", "method")));
    GLOGT(eGINF, "");
    GLOGW(eGINF, lRes.toString());
}
//===============================================
void GTest::runStringPad(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    QString lData = "123";
    QString lPad = lData.leftJustified(10);
    QString lLeft = lData.leftJustified(10, '.');
    QString lRight = lData.rightJustified(10, '.');
    GLOGW(eGINF, QString("[%1]").arg(lData));
    GLOGW(eGINF, QString("[%1]").arg(lPad));
    GLOGW(eGINF, QString("[%1]").arg(lLeft));
    GLOGW(eGINF, QString("[%1]").arg(lRight));
}
//===============================================
void GTest::runStringSub(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    QString lData = "Bonjour tout le monde";
    QString lSub = lData.mid(1, 5);
    GLOGW(eGINF, lData);
    GLOGW(eGINF, lSub);
}
//===============================================
void GTest::onModule(GSocket* _client) {
    QString lMethod = m_req->getMethod();

    // method
    if(lMethod == "save_user") {
        onRequestSaveUser(_client);
    }
    else if(lMethod == "get_user") {
        onRequestGetUser(_client);
    }
    else if(lMethod == "error") {
        onRequestError(_client);
    }
    // unknown
    else {
        onMethodUnknown(_client);
    }
}
//===============================================
void GTest::onRequestSaveUser(GSocket* _client) {
    QString lFirstname = m_req->getItem("parameters", "firstname");
    QString lLastname = m_req->getItem("parameters", "lastname");
    GLOGT(eGINF, "");
    GLOGW(eGINF, QString("firstname......: %1").arg(lFirstname));
    GLOGW(eGINF, QString("lastname.......: %1").arg(lLastname));
}
//===============================================
void GTest::onRequestGetUser(GSocket* _client) {
    GSocket* lClient = _client;
    QSharedPointer<GCode>& lRes = lClient->getResponse();
    lRes->createCode("user", "firstname", "Gerard");
    lRes->createCode("user", "lastname", "KESSE");
}
//===============================================
void GTest::onRequestError(GSocket* _client) {
    GERROR(eGERR, QString("Erreur cet identifiant existe deja"));
    GERROR(eGERR, QString("Erreur le mot de passe est incorrect"));
}
//===============================================
