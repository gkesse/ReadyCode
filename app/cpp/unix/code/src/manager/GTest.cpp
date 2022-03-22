//===============================================
#include "GTest.h"
#include "GPath.h"
#include "GXml.h"
#include "GCode.h"
#include "GFormat.h"
#include "GSocket.h"
#include "GFile.h"
#include "GThread.h"
#include "GExit.h"
#include "GInterrupt.h"
#include "GTimer.h"
#include "GMaster.h"
#include "GMySQL.h"
#include "GConsole.h"
#include "GLog.h"
#include "GHostname.h"
//===============================================
GTest* GTest::m_test = 0;
//===============================================
GTest::GTest() : GModule() {
    m_server = 0;
}
//===============================================
GTest::GTest(const std::string& _req) : GModule(_req) {
    m_server = 0;
}
//===============================================
GTest::~GTest() {

}
//===============================================
void GTest::run(int _argc, char** _argv) {
    std::string lKey = "default";
    if(_argc > 2) lKey = _argv[2];

    if(lKey == "default") {
        runTest(_argc, _argv);
    }
    // int
    else if(lKey == "int/string") {
        runIntString(_argc, _argv);
    }
    else if(lKey == "int/string/vector") {
        runIntStringVector(_argc, _argv);
    }
    // string
    else if(lKey == "string") {
        runString(_argc, _argv);
    }
    // path
    else if(lKey == "path") {
        runPath(_argc, _argv);
    }
    // format
    else if(lKey == "format") {
        runFormat(_argc, _argv);
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
    else if(lKey == "socket/server/file") {
        runSocketServerFile(_argc, _argv);
    }
    else if(lKey == "socket/client/file") {
        runSocketClientFile(_argc, _argv);
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
    // exit
    else if(lKey == "exit") {
        runExit(_argc, _argv);
    }
    // interrupt
    else if(lKey == "interrupt") {
        runInterrupt(_argc, _argv);
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
    // mysql
    else if(lKey == "mysql") {
        runMysql(_argc, _argv);
    }
    // end
    else {
        runTest(_argc, _argv);
    }
}
//===============================================
void GTest::runTest(int _argc, char** _argv) {
    printf("%s\n", __FUNCTION__);
    int lInt = 123;
    const int BUFFER_SIZE = 10;
    char lBuffer[BUFFER_SIZE + 1];

    sprintf(lBuffer, "%*d", BUFFER_SIZE, lInt);

    printf("int.....: [%d]\n", lInt);
    printf("string..: [%s]\n", lBuffer);
}
//===============================================
void GTest::runIntString(int _argc, char** _argv) {
    printf("%s\n", __FUNCTION__);
    int lInt = 123;
    const int BUFFER_SIZE = 10;
    char lBuffer[BUFFER_SIZE + 1];

    sprintf(lBuffer, "%*d", BUFFER_SIZE, lInt);
    std::string lString = lBuffer;
    int lNumber = std::stoi(lString);
    int lSize = lString.size();

    printf("int.....: [%d]\n", lInt);
    printf("string..: [%s]\n", lBuffer);
    printf("number..: [%d]\n", lNumber);
    printf("size....: [%d]\n", lSize);
}
//===============================================
void GTest::runIntStringVector(int _argc, char** _argv) {
    printf("%s\n", __FUNCTION__);
    int lInt = 123;
    const int BUFFER_SIZE = 10;

    std::vector<char> lBuffer(BUFFER_SIZE + 1);
    snprintf(lBuffer.data(), lBuffer.size(), "%*d", BUFFER_SIZE, lInt);
    std::string lData = lBuffer.data();
    int lNumber = std::stoi(lData);
    int lSize = lData.size();

    printf("int.....: [%d]\n", lInt);
    printf("data....: [%s]\n", lData.c_str());
    printf("number..: [%d]\n", lNumber);
    printf("size....: [%d]\n", lSize);
    printf("iformat.: [%s]\n", iformat(lInt, BUFFER_SIZE).c_str());
}
//===============================================
void GTest::runString(int _argc, char** _argv) {
    printf("%s\n", __FUNCTION__);
    std::string lFilename = GRES("file", "test.txt");
    std::string lContent = GFile(lFilename).getData();
    int lLength = lContent.size();
    int BUFFER_DATA_SIZE = 1024;
    int lSize = (int)ceil((double)lLength/BUFFER_DATA_SIZE);
    int lIndex = 0;
    std::string lData;

    printf("lLength.................: %d\n", lLength);
    printf("BUFFER_DATA_SIZE........: %d\n", BUFFER_DATA_SIZE);
    printf("lSize...................: %d\n", lSize);

    for(int i = 0; i < 5; i++) {
        lData = lContent.substr(lIndex, 10);
        lIndex += lData.size();
        printf("lData...................: %s\n", lData.c_str());
        printf("lIndex...................: %d\n", lIndex);
    }
}
//===============================================
void GTest::runPath(int _argc, char** _argv) {
    printf("%s\n", __FUNCTION__);
    std::string lPath = GRES("xml", "pad.xml");
    printf("%s\n", lPath.c_str());
}
//===============================================
void GTest::runFormat(int _argc, char** _argv) {
    printf("%s\n", __FUNCTION__);
    printf("%s\n", sformat("app : %s - v%s", "ReadyPad", "1.0").c_str());
}
//===============================================
void GTest::runXml(int _argc, char** _argv) {
    printf("%s\n", __FUNCTION__);
    m_dom.reset(new GXml);
    m_dom->loadXmlFile(GRES("xml", "pad.xml"));
    m_dom->createXPath();
    printf("app_name......: %s\n", getPadItem("app_name").c_str());
    printf("app_version...: %s\n", getPadItem("app_version").c_str());
}
//===============================================
std::string GTest::getPadItem(const std::string& _data) const {
    m_dom->queryXPath(sformat("/rdv/datas/data[code='pad']/%s", _data.c_str()));
    m_dom->getNodeXPath();
    std::string lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
void GTest::runSocketServer(int _argc, char** _argv) {
    printf("%s\n", __FUNCTION__);
    GSocket lServer;
    GSocket lClient;

    int lDomain = lServer.loadDomain();
    int lType = lServer.loadType();
    int lProtocol = lServer.loadProtocol();
    int lFamily = lServer.loadFamily();
    std::string lClientIp = lServer.getSocketItem("client_ip");
    int lPort = std::stoi(lServer.getSocketItem("port"));
    int lBacklog = std::stoi(lServer.getSocketItem("backlog"));

    lServer.createSocket(lDomain, lType, lProtocol);
    lServer.createAddress(lFamily, lClientIp, lPort);
    lServer.bindSocket();
    lServer.listenSocket(lBacklog);
    lServer.startMessage();
    lServer.acceptSocket(lClient);

    std::string lData;
    lClient.recvData(lData);
    lClient.sendData("<result>ok</result>\0");

    printf("=====>\n");
    printf("%s\n", lData.c_str());

    lClient.closeSocket();
    lServer.closeSocket();
}
//===============================================
void GTest::runSocketClient(int _argc, char** _argv) {
    printf("%s\n", __FUNCTION__);
    GSocket lClient;

    int lDomain = lClient.loadDomain();
    int lType = lClient.loadType();
    int lProtocol = lClient.loadProtocol();
    int lFamily = lClient.loadFamily();
    std::string lServerIp = lClient.getSocketItem("server_ip");
    int lPort = std::stoi(lClient.getSocketItem("port"));

    lClient.createSocket(lDomain, lType, lProtocol);
    lClient.createAddress(lFamily, lServerIp, lPort);
    lClient.connectSocket();

    std::string lData;
    lClient.sendData("Bonjour tout le monde");
    lClient.sendData("Voici mon premier test");
    lClient.recvData(lData);

    printf("=====>\n");
    printf("%s\n", lData.c_str());

    lClient.closeSocket();
}
//===============================================
void GTest::runSocketServerFile(int _argc, char** _argv) {
    printf("%s\n", __FUNCTION__);
    GSocket lServer;
    GSocket lClient;

    int lDomain = lServer.loadDomain();
    int lType = lServer.loadType();
    int lProtocol = lServer.loadProtocol();
    int lFamily = lServer.loadFamily();
    std::string lClientIp = lServer.getSocketItem("client_ip");
    int lPort = std::stoi(lServer.getSocketItem("port"));
    int lBacklog = std::stoi(lServer.getSocketItem("backlog"));

    lServer.createSocket(lDomain, lType, lProtocol);
    lServer.createAddress(lFamily, lClientIp, lPort);
    lServer.bindSocket();
    lServer.listenSocket(lBacklog);

    lServer.startMessage();

    lServer.acceptSocket(lClient);

    std::string lData;
    lClient.readData(lData);
    printf("=====>\n");
    printf("%s\n", lData.c_str());

    lClient.writeData("<result>ok</result>");

    lClient.closeSocket();
    lServer.closeSocket();
}
//===============================================
void GTest::runSocketClientFile(int _argc, char** _argv) {
    printf("%s\n", __FUNCTION__);
    GSocket lClient;

    int lDomain = lClient.loadDomain();
    int lType = lClient.loadType();
    int lProtocol = lClient.loadProtocol();
    int lFamily = lClient.loadFamily();
    std::string lServerIp = lClient.getSocketItem("server_ip");
    int lPort = std::stoi(lClient.getSocketItem("port"));

    lClient.createSocket(lDomain, lType, lProtocol);
    lClient.createAddress(lFamily, lServerIp, lPort);
    lClient.connectSocket();

    std::string lFilename = GRES("file", "test.txt");
    std::string lData = GFile(lFilename).getData();

    lClient.writeData(lData);
    lClient.readData(lData);
    lClient.closeSocket();

    printf("=====>\n");
    printf("%s\n", lData.c_str());
}
//===============================================
void GTest::runSocketServerStart(int _argc, char** _argv) {
    printf("%s\n", __FUNCTION__);
    m_test = new GTest;
    m_test->m_server = new GSocket;
    GThread lThread;
    GTimer lTimer;
    lThread.createThread((void*)onSocketServerStartThread, this);
    lTimer.setCallback((void*)onSocketServerStartTimer, 100);
    while(lTimer.isRunning()) {
        pause();
    }
}
//===============================================
void* GTest::onSocketServerStartThread(void* _params) {
    printf("%s\n", __FUNCTION__);
    GSocket* lServer = m_test->m_server;
    lServer->startServer((void*)GSocket::onServerThread);
    return 0;
}
//===============================================
void GTest::onSocketServerStartTimer(int _signo) {
    GSocket* lServer = m_test->m_server;
    std::queue<GSocket*>& lClientIns = lServer->getClientIns();

    if(!lClientIns.empty()) {
        GSocket* lClient = lClientIns.front();
        lClientIns.pop();
        GMaster lMaster(lClient->getRequest());
        lMaster.onModule(lClient);
        GHostname lHostname;
        lHostname.saveHostname(lClient);
        lMaster.sendResponse(lClient);
    }
}
//===============================================
void GTest::runSocketClientStart(int _argc, char** _argv) {
    printf("%s\n", __FUNCTION__);

    std::string lFilename = GRES("file", "test.txt");
    std::string lData = GFile(lFilename).getData();

    GSocket lClient;
    lData = lClient.callServer(lData);

    printf("=====>\n");
    printf("%s\n", lData.c_str());
}
//===============================================
void GTest::runThread(int _argc, char** _argv) {
    printf("%s\n", __FUNCTION__);
    GThread lThread;
    lThread.createThread((void*)onThread, (void*)"Bonjour tout le monde");
    pause();
}
//===============================================
void* GTest::onThread(void* _params) {
    std::string lMessage = (char*)_params;
    printf("%s\n", __FUNCTION__);
    for(int i = 0; i < 10; i++) {
        printf("%s\n", lMessage.c_str());
    }
    return 0;
}
//===============================================
void GTest::runExit(int _argc, char** _argv) {
    printf("%s\n", __FUNCTION__);
    GExit lExit;
    lExit.setCallback((void*)GExit::onExit);
    exit(0);
}
//===============================================
void GTest::runInterrupt(int _argc, char** _argv) {
    printf("%s\n", __FUNCTION__);
    GInterrupt lInterrupt;
    lInterrupt.setCallback((void*)GInterrupt::onInterrupt);
    pause();
}
//===============================================
void GTest::runTimer(int _argc, char** _argv) {
    printf("%s\n", __FUNCTION__);
    GTimer lTimer;
    lTimer.setCallback((void*)GTimer::onTimer, 1000);
    while(1) {
        pause();
    }
}
//===============================================
void GTest::runRequest(int _argc, char** _argv) {
    printf("%s\n", __FUNCTION__);
    GXml lReq;
    lReq.createDoc("1.0");
    lReq.createRoot("rdv");
    lReq.createXPath();
    lReq.createNodePath("/rdv/module", "hostname");
    lReq.createNodePath("/rdv/method", "save_hostname");
    printf("%s\n", lReq.toString().c_str());
}
//===============================================
void GTest::runRequestSend(int _argc, char** _argv) {
    printf("%s\n", __FUNCTION__);
    GCode lReq;
    GSocket lClient;
    lReq.createRequest("test", "request_send");
    std::string lResponse = lClient.callServer(lReq.toString());
    console("=====>");
    console(lReq.toString());
    console("=====>");
    console(lResponse);
}
//===============================================
void GTest::runRequestSaveUser(int _argc, char** _argv) {
    printf("%s\n", __FUNCTION__);
    GCode lReq;
    GSocket lClient;
    lReq.createRequest("test", "save_user");
    lReq.createCode("parameters", "firstname", "Gerard");
    lReq.createCode("parameters", "lastname", "KESSE");
    std::string lResponse = lClient.callServer(lReq.toString());
    GLOGI->loadErrors(lResponse);
    console("=====>");
    console(lReq.toString());
    console("=====>");
    console(lResponse);
}
//===============================================
void GTest::runRequestGetUser(int _argc, char** _argv) {
    printf("%s\n", __FUNCTION__);
    GCode lReq;
    GSocket lClient;
    lReq.createRequest("test", "get_user");
    std::string lResponse = lClient.callServer(lReq.toString());
    GLOGI->loadErrors(lResponse);
    GCode lRes(lResponse);
    console("=====>");
    console(lReq.toString());
    console("=====>");
    console(lResponse);
    console("=====>");
    consoles("firstname.....: %s", lRes.getItem("user", "firstname").c_str());
    consoles("lastname......: %s", lRes.getItem("user", "lastname").c_str());
}
//===============================================
void GTest::runRequestError(int _argc, char** _argv) {
    printf("%s\n", __FUNCTION__);
    GCode lReq;
    GSocket lClient;
    lReq.createRequest("test", "error");
    std::string lResponse = lClient.callServer(lReq.toString());
    GLOGI->loadErrors(lResponse);
    console("=====>");
    console(lReq.toString());
    console("=====>");
    console(lResponse);
    console("=====>");
}
//===============================================
void GTest::runResponse(int _argc, char** _argv) {
    printf("%s\n", __FUNCTION__);
    GCode lRes;
    lRes.createDoc("1.0", "rdv");
    lRes.createCode("request", "module", "test");
    lRes.createCode("request", "method", "save_user");
    lRes.createCode("result", "msg", "ok");
    lRes.createCode("opencv", "version", "4.0");
    lRes.createMap("error", "msg", "le chemin est incorrect");
    lRes.createMap("error", "msg", "la donnee est incorrect");
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
    consoles("module.....: %s", lRes.getItem("request", "module").c_str());
    consoles("method.....: %s", lRes.getItem("request", "method").c_str());
    console("=====>");
    console(lRes.toString());
}
//===============================================
void GTest::runMysql(int _argc, char** _argv) {
    printf("%s\n", __FUNCTION__);
    GMySQL lMySQL;
    std::string lSql = "select user from mysql.user";
    console(lMySQL.readData(lSql));
    console("");
    console(lMySQL.readCol(lSql));
}
//===============================================
void GTest::onModule(GSocket* _client) {
    std::string lMethod = m_req->getMethod();

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
    std::string lFirstname = m_req->getItem("parameters", "firstname");
    std::string lLastname = m_req->getItem("parameters", "lastname");
    console("=====>");
    consoles("firstname......: %s", lFirstname.c_str());
    consoles("lastname.......: %s", lLastname.c_str());
}
//===============================================
void GTest::onRequestGetUser(GSocket* _client) {
    GSocket* lClient = _client;
    std::shared_ptr<GCode>& lRes = lClient->getResponse();
    lRes->createCode("user", "firstname", "Gerard");
    lRes->createCode("user", "lastname", "KESSE");
}
//===============================================
void GTest::onRequestError(GSocket* _client) {
    GLOG("Erreur cet identifiant existe deja");
    GLOG("Erreur le mot de passe est incorrect");
}
//===============================================
