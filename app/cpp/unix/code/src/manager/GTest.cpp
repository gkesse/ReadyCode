//===============================================
#include "GTest.h"
#include "GPath.h"
#include "GXml.h"
#include "GCode.h"
#include "GLog.h"
#include "GFormat.h"
#include "GSocket.h"
#include "GFile.h"
#include "GThread.h"
#include "GExit.h"
#include "GInterrupt.h"
#include "GTimer.h"
#include "GMaster.h"
#include "GMySQL.h"
#include "GHostname.h"
#include "GShell.h"
#include "GEnv.h"
#include "GDate.h"
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
    // shell
    else if(lKey == "shell/system") {
        runShellSystem(_argc, _argv);
    }
    // env
    else if(lKey == "env") {
        runEnv(_argc, _argv);
    }
    else if(lKey == "env/type") {
        runEnvType(_argc, _argv);
    }
    // date
    else if(lKey == "date") {
        runDate(_argc, _argv);
    }
    // tmp
    else if(lKey == "tmp/clean") {
        runTmpClean(_argc, _argv);
    }
    // log
    else if(lKey == "log") {
        runLog(_argc, _argv);
    }
    else if(lKey == "log/macro") {
        runLogMacro(_argc, _argv);
    }
    else if(lKey == "log/show") {
        runLogShow(_argc, _argv);
    }
    // end
    else {
        runTest(_argc, _argv);
    }
}
//===============================================
void GTest::runTest(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    int lInt = 123;
    const int BUFFER_SIZE = 10;
    char lBuffer[BUFFER_SIZE + 1];

    sprintf(lBuffer, "%*d", BUFFER_SIZE, lInt);

    GLOGW("int.....: [%d]\n", lInt);
    GLOGW("string..: [%s]\n", lBuffer);
}
//===============================================
void GTest::runIntString(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    int lInt = 123;
    const int BUFFER_SIZE = 10;
    char lBuffer[BUFFER_SIZE + 1];

    sprintf(lBuffer, "%*d", BUFFER_SIZE, lInt);
    std::string lString = lBuffer;
    int lNumber = std::stoi(lString);
    int lSize = lString.size();

    GLOGW("int.....: [%d]\n", lInt);
    GLOGW("string..: [%s]\n", lBuffer);
    GLOGW("number..: [%d]\n", lNumber);
    GLOGW("size....: [%d]\n", lSize);
}
//===============================================
void GTest::runIntStringVector(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    int lInt = 123;
    const int BUFFER_SIZE = 10;

    std::vector<char> lBuffer(BUFFER_SIZE + 1);
    snprintf(lBuffer.data(), lBuffer.size(), "%*d", BUFFER_SIZE, lInt);
    std::string lData = lBuffer.data();
    int lNumber = std::stoi(lData);
    int lSize = lData.size();

    GLOGW("int.....: [%d]\n", lInt);
    GLOGW("data....: [%s]\n", lData.c_str());
    GLOGW("number..: [%d]\n", lNumber);
    GLOGW("size....: [%d]\n", lSize);
    GLOGW("iformat.: [%s]\n", iformat(lInt, BUFFER_SIZE).c_str());
}
//===============================================
void GTest::runString(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    std::string lFilename = GRES("file", "test.txt");
    std::string lContent = GFile(lFilename).getContent();
    int lLength = lContent.size();
    int BUFFER_DATA_SIZE = 1024;
    int lSize = (int)ceil((double)lLength/BUFFER_DATA_SIZE);
    int lIndex = 0;
    std::string lData;

    GLOGW("lLength.................: %d\n", lLength);
    GLOGW("BUFFER_DATA_SIZE........: %d\n", BUFFER_DATA_SIZE);
    GLOGW("lSize...................: %d\n", lSize);

    for(int i = 0; i < 5; i++) {
        lData = lContent.substr(lIndex, 10);
        lIndex += lData.size();
        GLOGW("lData...................: %s\n", lData.c_str());
        GLOGW("lIndex...................: %d\n", lIndex);
    }
}
//===============================================
void GTest::runPath(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    std::string lPath = GRES("xml", "pad.xml");
    GLOGW("%s\n", lPath.c_str());
}
//===============================================
void GTest::runFormat(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    GLOGW("%s\n", sformat("app : %s - v%s", "ReadyPad", "1.0").c_str());
}
//===============================================
void GTest::runXml(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    m_dom.reset(new GXml);
    m_dom->loadXmlFile(GRES("xml", "pad.xml"));
    m_dom->createXPath();
    GLOGW("app_name......: %s\n", getPadItem("app_name").c_str());
    GLOGW("app_version...: %s\n", getPadItem("app_version").c_str());
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
    GLOGT(eGFUN, "");
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
    lClient.sendData("<result>ok</result>");

    GLOGW("=====>\n");
    GLOGW("%s\n", lData.c_str());

    lClient.closeSocket();
    lServer.closeSocket();
}
//===============================================
void GTest::runSocketClient(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
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

    GLOGW("=====>\n");
    GLOGW("%s\n", lData.c_str());

    lClient.closeSocket();
}
//===============================================
void GTest::runSocketServerFile(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
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
    GLOGW("=====>\n");
    GLOGW("%s\n", lData.c_str());

    lClient.writeData("<result>ok</result>");

    lClient.closeSocket();
    lServer.closeSocket();
}
//===============================================
void GTest::runSocketClientFile(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
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
    std::string lData = GFile(lFilename).getContent();

    lClient.writeData(lData);
    lClient.readData(lData);
    lClient.closeSocket();

    GLOGW("=====>\n");
    GLOGW("%s\n", lData.c_str());
}
//===============================================
void GTest::runSocketServerStart(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
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
    GLOGT(eGFUN, "");
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
        GLOGT(eGMSG, "%s", lClient->getRequest().c_str());
        GMaster lMaster(lClient->getRequest());
        lMaster.onModule(lClient);
        GHostname lHostname;
        lHostname.saveHostname(lClient);
        lMaster.sendResponse(lClient);
    }
}
//===============================================
void GTest::runSocketClientStart(int _argc, char** _argv) {
    GLOGT(eGFUN, "");

    std::string lFilename = GRES("file", "test.txt");
    std::string lData = GFile(lFilename).getContent();

    GSocket lClient;
    lData = lClient.callServer(lData);

    GLOGW("=====>\n");
    GLOGW("%s\n", lData.c_str());
}
//===============================================
void GTest::runThread(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    GThread lThread;
    lThread.createThread((void*)onThread, (void*)"Bonjour tout le monde");
    pause();
}
//===============================================
void* GTest::onThread(void* _params) {
    GLOGT(eGFUN, "");
    std::string lMessage = (char*)_params;
    for(int i = 0; i < 10; i++) {
        GLOGW("%s\n", lMessage.c_str());
    }
    return 0;
}
//===============================================
void GTest::runExit(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    GExit lExit;
    lExit.setCallback((void*)GExit::onExit);
    exit(0);
}
//===============================================
void GTest::runInterrupt(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    GInterrupt lInterrupt;
    lInterrupt.setCallback((void*)GInterrupt::onInterrupt);
    pause();
}
//===============================================
void GTest::runTimer(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    GTimer lTimer;
    lTimer.setCallback((void*)GTimer::onTimer, 1000);
    while(1) {
        pause();
    }
}
//===============================================
void GTest::runRequest(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    GXml lReq;
    lReq.createDoc("1.0");
    lReq.createRoot("rdv");
    lReq.createXPath();
    lReq.createNodePath("/rdv/module", "hostname");
    lReq.createNodePath("/rdv/method", "save_hostname");
    GLOGW("%s\n", lReq.toString().c_str());
}
//===============================================
void GTest::runRequestSend(int _argc, char** _argv) {
    GLOGT(eGMSG, "");
    GCode lReq;
    GSocket lClient;
    lReq.createRequest("test", "request_send");
    std::string lResponse = lClient.callServer(lReq.toString());
    GLOGW("%s", lReq.toString().c_str());
    GLOGW("%s", lResponse.c_str());
}
//===============================================
void GTest::runRequestSaveUser(int _argc, char** _argv) {
    GLOGT(eGMSG, "");
    GCode lReq;
    GSocket lClient;
    lReq.createRequest("test", "save_user");
    lReq.createCode("parameters", "firstname", "Gerard");
    lReq.createCode("parameters", "lastname", "KESSE");
    std::string lResponse = lClient.callServer(lReq.toString());
    GLOGI->loadErrors(lResponse);
    GLOGW("%s", lReq.toString().c_str());
    GLOGT(eGMSG, "");
    GLOGW("%s", lResponse.c_str());
}
//===============================================
void GTest::runRequestGetUser(int _argc, char** _argv) {
    GLOGT(eGMSG, "");
    GCode lReq;
    GSocket lClient;
    lReq.createRequest("test", "get_user");
    std::string lResponse = lClient.callServer(lReq.toString());
    GLOGI->loadErrors(lResponse);
    GCode lRes(lResponse);
    GLOGT(eGMSG, "");
    GLOGW("%s", lReq.toString().c_str());
    GLOGT(eGMSG, "");
    GLOGW("%s", lResponse.c_str());
    GLOGT(eGMSG, "");
    GLOGW("firstname.....: %s", lRes.getItem("user", "firstname").c_str());
    GLOGW("lastname......: %s", lRes.getItem("user", "lastname").c_str());
}
//===============================================
void GTest::runRequestError(int _argc, char** _argv) {
    GLOGT(eGMSG, "");
    GCode lReq;
    GSocket lClient;
    lReq.createRequest("test", "error");
    std::string lResponse = lClient.callServer(lReq.toString());
    GLOGI->loadErrors(lResponse);
    GLOGT(eGMSG, "");
    GLOGW("%s", lReq.toString().c_str());
    GLOGT(eGMSG, "");
    GLOGW("%s", lResponse.c_str());
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
    GLOGT(eGFUN, "");
    GLOGW("%s", GSTRC(lRes.hasCode("result")).c_str());        // true
    GLOGT(eGFUN, "");
    GLOGW("%s", GSTRC(lRes.hasCode("resulto")).c_str());       // false
    GLOGT(eGFUN, "");
    GLOGW("%s", GSTRC(lRes.hasCode("error")).c_str());         // true
    GLOGT(eGFUN, "");
    GLOGW("%s", GSTRC(lRes.hasCode("error", "msg")).c_str());  // true
    GLOGT(eGFUN, "");
    GLOGW("%s", GSTRC(lRes.hasCode("error", "msgo")).c_str()); // false
    GLOGT(eGFUN, "");
    GLOGW("module.....: %s", lRes.getItem("request", "module").c_str());
    GLOGW("method.....: %s", lRes.getItem("request", "method").c_str());
    GLOGT(eGFUN, "");
    GLOGW("%s", lRes.toString().c_str());
}
//===============================================
void GTest::runMysql(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    GMySQL lMySQL;
    std::string lSql = "select user from mysql.user";
    GLOGW("%s", lMySQL.readData(lSql).c_str());
    GLOGT(eGFUN, "");
    GLOGW("%s", GSTRC(lMySQL.readCol(lSql)).c_str());
}
//===============================================
void GTest::runShellSystem(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    std::string lCommand = sformat("echo \"Bonjour tout le monde\"");
    std::string lData = GShell().runSystem(lCommand);
    GLOGT(eGMSG, "%s", lData.c_str());
}
//===============================================
void GTest::runEnv(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    std::string lTmp = GEnv().getEnv("GPROJECT_TMP");
    std::string lCommand = sformat("if ! [ -d %s ] ; then mkdir -p %s ; fi", lTmp.c_str(), lTmp.c_str());
    GLOGW("%s", lCommand.c_str());
}
//===============================================
void GTest::runEnvType(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    GEnv lEnv;
    std::string lEnvType = lEnv.getEnvType();
    GLOGW("%s", lEnvType.c_str());
}
//===============================================
void GTest::runDate(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    std::string lDate = GDate().getDate(GDate().getDateTimeFileFormat());
    GLOGW("%s", lDate.c_str());
}
//===============================================
void GTest::runTmpClean(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    GShell lShell;
    lShell.cleanDir(lShell.getTmpDir());
}
//===============================================
void GTest::runLog(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    std::string lDate = GDate().getDate(GDate().getDateTimeLogFormat());
    std::string lLog = "";
    lLog += sformat("__FILE__.............: %s\n", __FILE__);
    lLog += sformat("__LINE__.............: %d\n", __LINE__);
    lLog += sformat("__FUNCTION__.........: %s\n", __FUNCTION__);
    lLog += sformat("__PRETTY_FUNCTION__..: %s\n", __PRETTY_FUNCTION__);
    lLog += sformat("__func__.............: %s\n", __func__);
    lLog += sformat("=====> [%s] : %s : %s : [%d] : %s :\n%s", "INFO", lDate.c_str(), __FILE__, __LINE__, __PRETTY_FUNCTION__, "Bonjour tout le monde");
    GLOGW("%s", lLog.c_str());
}
//===============================================
void GTest::runLogMacro(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    GLOGT(eGINF, "");
    GLOGT(eGINF, "Bonjour tout le monde");
    GLOGT(eGERR, "Erreur la methode a echoue");
}
//===============================================
void GTest::runLogShow(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    GLOGI->catLogFile();
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
    GLOGT(eGFUN, "");
    GLOGW("firstname......: %s", lFirstname.c_str());
    GLOGW("lastname.......: %s", lLastname.c_str());
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
    GERROR("Erreur cet identifiant existe deja");
    GERROR("Erreur le mot de passe est incorrect");
}
//===============================================
