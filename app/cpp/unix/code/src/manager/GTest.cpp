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
#include "GShell.h"
#include "GEnv.h"
#include "GDate.h"
#include "GHost.h"
#include "GString.h"
#include "GError.h"
#include "GDir.h"
#include "GMaj.h"
#include "GBase64.h"
#include "GMd5.h"
//===============================================
GTest* GTest::m_test = 0;
//===============================================
GTest::GTest() : GModule() {
    m_server = 0;
}
//===============================================
GTest::~GTest() {

}
//===============================================
void GTest::run(int _argc, char** _argv) {
    std::string lKey = "default";
    if(_argc > 2) lKey = _argv[2];
    //===============================================
    // default
    //===============================================
    if(lKey == "default") {
        runTest(_argc, _argv);
    }
    //===============================================
    // int
    //===============================================
    else if(lKey == "int/string") {
        runIntString(_argc, _argv);
    }
    else if(lKey == "int/string/vector") {
        runIntStringVector(_argc, _argv);
    }
    //===============================================
    // string
    //===============================================
    else if(lKey == "string") {
        runString(_argc, _argv);
    }
    else if(lKey == "string/int") {
        runStringInt(_argc, _argv);
    }
    //===============================================
    // path
    //===============================================
    else if(lKey == "path") {
        runPath(_argc, _argv);
    }
    //===============================================
    // format
    //===============================================
    else if(lKey == "format") {
        runFormat(_argc, _argv);
    }
    //===============================================
    // xml
    //===============================================
    else if(lKey == "xml") {
        runXml(_argc, _argv);
    }
    else if(lKey == "xml/check") {
        runXmlCheck(_argc, _argv);
    }
    //===============================================
    // socket
    //===============================================
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
    //===============================================
    // thread
    //===============================================
    else if(lKey == "thread") {
        runThread(_argc, _argv);
    }
    //===============================================
    // exit
    //===============================================
    else if(lKey == "exit") {
        runExit(_argc, _argv);
    }
    //===============================================
    // interrupt
    //===============================================
    else if(lKey == "interrupt") {
        runInterrupt(_argc, _argv);
    }
    //===============================================
    // timer
    //===============================================
    else if(lKey == "timer") {
        runTimer(_argc, _argv);
    }
    //===============================================
    // request
    //===============================================
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
    //===============================================
    // response
    //===============================================
    else if(lKey == "response") {
        runResponse(_argc, _argv);
    }
    //===============================================
    // mysql
    //===============================================
    else if(lKey == "mysql") {
        runMysql(_argc, _argv);
    }
    else if(lKey == "mysql/shell") {
        runMysqlShell(_argc, _argv);
    }
    else if(lKey == "mysql/shell/config") {
        runMysqlShellConfig(_argc, _argv);
    }
    else if(lKey == "mysql/shell/file") {
        runMysqlShellFile(_argc, _argv);
    }
    else if(lKey == "mysql/shell/script") {
        runMysqlShellScript(_argc, _argv);
    }
    else if(lKey == "mysql/db") {
        runMysqlDB(_argc, _argv);
    }
    else if(lKey == "mysql/maj") {
        runMysqlMaj(_argc, _argv);
    }
    else if(lKey == "mysql/maj/prod") {
        runMysqlMajProd(_argc, _argv);
    }
    //===============================================
    // shell
    //===============================================
    else if(lKey == "shell/system") {
        runShellSystem(_argc, _argv);
    }
    //===============================================
    // env
    //===============================================
    else if(lKey == "env") {
        runEnv(_argc, _argv);
    }
    else if(lKey == "env/type") {
        runEnvType(_argc, _argv);
    }
    //===============================================
    // date
    //===============================================
    else if(lKey == "date") {
        runDate(_argc, _argv);
    }
    //===============================================
    // tmp
    //===============================================
    else if(lKey == "tmp/clean") {
        runTmpClean(_argc, _argv);
    }
    //===============================================
    // log
    //===============================================
    else if(lKey == "log") {
        runLog(_argc, _argv);
    }
    else if(lKey == "log/macro") {
        runLogMacro(_argc, _argv);
    }
    else if(lKey == "log/cat") {
        runLogCat(_argc, _argv);
    }
    else if(lKey == "log/tail") {
        runLogTail(_argc, _argv);
    }
    else if(lKey == "log/tail/prod") {
        runLogTailProd(_argc, _argv);
    }
    //===============================================
    // file
    //===============================================
    else if(lKey == "file") {
        runFile(_argc, _argv);
    }
    //===============================================
    // dir
    //===============================================
    else if(lKey == "dir") {
        runDir(_argc, _argv);
    }
    //===============================================
    // base64
    //===============================================
    else if(lKey == "base64") {
        runBase64(_argc, _argv);
    }
    //===============================================
    // md5
    //===============================================
    else if(lKey == "md5") {
        runMd5(_argc, _argv);
    }
    else if(lKey == "md5/key") {
        runMd5Key(_argc, _argv);
    }
    //===============================================
    // end
    //===============================================
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

    GLOGT(eGINF, "int.....: [%d]", lInt);
    GLOGT(eGINF, "string..: (%s)\n", lBuffer);
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

    GLOGT(eGINF, "int.....: [%d]\n", lInt);
    GLOGT(eGINF, "string..: [%s]\n", lBuffer);
    GLOGT(eGINF, "number..: [%d]\n", lNumber);
    GLOGT(eGINF, "size....: [%d]\n", lSize);
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
    std::string lFormat = sformat("%-*d", BUFFER_SIZE, lInt);

    GLOGT(eGINF, ""
            "int.....: [%d]\n"
            "data....: [%s]\n"
            "number..: [%d]\n"
            "size....: [%d]\n"
            "format..: [%s]\n"
            "", lInt
            , lData.c_str()
            , lNumber
            , lSize
            , lFormat.c_str()
    );
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

    GLOGT(eGINF, "lLength.................: %d\n", lLength);
    GLOGT(eGINF, "BUFFER_DATA_SIZE........: %d\n", BUFFER_DATA_SIZE);
    GLOGT(eGINF, "lSize...................: %d\n", lSize);

    for(int i = 0; i < 5; i++) {
        lData = lContent.substr(lIndex, 10);
        lIndex += lData.size();
        GLOGT(eGINF, "lData...................: %s\n", lData.c_str());
        GLOGT(eGINF, "lIndex...................: %d\n", lIndex);
    }
}
//===============================================
void GTest::runStringInt(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    GLOGT(eGINF, "%d\n", GString("  123  ").toInt());
    GLOGT(eGINF, "%d\n", GString("  123  abc  ").toInt());
    GLOGT(eGINF, "%d\n", GString("").toInt());
    GLOGT(eGINF, "%d\n", GString("  ").toInt());

    std::string lData = "  abc 123  ";
    GString lStringInt(lData);
    int lInt = lStringInt.toInt();
    GLOGT(eGINF, "%d : %s\n", lInt, GERROR_GET(lStringInt));

    char lBuffer[1024 + 1];
    sprintf(lBuffer, "%*d", 256, 123);
    GLOGT(eGINF, "%s", lBuffer);
    GLOGT(eGINF, "%d", std::stoi(lBuffer));
}
//===============================================
void GTest::runPath(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    std::string lPath = GRES("xml", "pad.xml");
    GLOGT(eGINF, "%s\n", lPath.c_str());
}
//===============================================
void GTest::runFormat(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    GLOGT(eGINF, "%s\n", sformat("app : %s - v%s", "ReadyPad", "1.0").c_str());
}
//===============================================
void GTest::runXml(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    m_dom.reset(new GXml(GRES("xml", "pad.xml"), true));
    m_dom->createXPath();
    GLOGT(eGINF, "app_name.....: (%s)\n", getItem("pad", "app_name").c_str());
    GLOGT(eGINF, "app_version..: (%s)\n", getItem("pad", "app_version").c_str());
}
//===============================================
void GTest::runXmlCheck(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    m_dom.reset(new GXml);
    m_dom->loadXml("Bonjour tout le monde", false);
    GLOGT(eGINF, "isValid : %s\n", GSTRC(m_dom->isValidXml()).c_str());
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
    std::string lClientIp = lServer.getItem("socket", "client_ip");
    int lPort = lServer.loadPort();
    int lBacklog = std::stoi(lServer.getItem("socket", "backlog"));

    lServer.createSocket(lDomain, lType, lProtocol);
    lServer.createAddress(lFamily, lClientIp, lPort);
    lServer.bindSocket();
    lServer.listenSocket(lBacklog);
    lServer.startMessage();
    lServer.acceptSocket(lClient);

    std::string lData;
    lClient.recvData(lData);
    lClient.sendData("<result>ok</result>");

    GLOGT(eGINF, "%s", lData.c_str());

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
    std::string lServerIp = lClient.getItem("socket", "server_ip");
    int lPort = lClient.loadPort();

    lClient.createSocket(lDomain, lType, lProtocol);
    lClient.createAddress(lFamily, lServerIp, lPort);
    lClient.connectSocket();

    std::string lData;
    lClient.sendData("Bonjour tout le monde");
    lClient.sendData("Voici mon premier test");
    lClient.recvData(lData);

    GLOGT(eGINF, "%s", lData.c_str());

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
    std::string lClientIp = lServer.getItem("socket", "client_ip");
    int lPort = lServer.loadPort();
    int lBacklog = std::stoi(lServer.getItem("socket", "backlog"));

    lServer.createSocket(lDomain, lType, lProtocol);
    lServer.createAddress(lFamily, lClientIp, lPort);
    lServer.bindSocket();
    lServer.listenSocket(lBacklog);

    lServer.startMessage();

    lServer.acceptSocket(lClient);

    std::string lData;
    lClient.readData(lData);
    GLOGT(eGINF, "%s", lData.c_str());

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
    std::string lServerIp = lClient.getItem("socket", "server_ip");
    int lPort = lClient.loadPort();

    lClient.createSocket(lDomain, lType, lProtocol);
    lClient.createAddress(lFamily, lServerIp, lPort);
    lClient.connectSocket();

    std::string lFilename = GRES("file", "test.txt");
    std::string lData = GFile(lFilename).getContent();

    lClient.writeData(lData);
    lClient.readData(lData);
    lClient.closeSocket();

    GLOGT(eGINF, "%s", lData.c_str());
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
    lTimer.pauseTimer();
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
        std::string lData = lClient->getReq()->toString();
        GLOGT(eGOFF, "[RECEPTION]..: (%d)\n(%s)\n", (int)lData.size(), lData.c_str());
        GMaster().onModule(lClient);
        GMaster().sendResponse(lClient);
    }
}
//===============================================
void GTest::runSocketClientStart(int _argc, char** _argv) {
    GLOGT(eGFUN, "");

    std::string lFilename = GRES("file", "test.txt");
    std::string lData = GFile(lFilename).getContent();

    GSocket lClient;
    lData = lClient.callServer(lData);

    GLOGT(eGINF, "%s", lData.c_str());
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
        GLOGT(eGINF, "%s", lMessage.c_str());
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
    lReq.createDoc();
    lReq.createNodePath("/rdv/module", "hostname");
    lReq.createNodePath("/rdv/method", "save_hostname");
    GLOGT(eGINF, "%s", lReq.toString().c_str());
}
//===============================================
void GTest::runRequestSend(int _argc, char** _argv) {
    GLOGT(eGMSG, "");
    GCode lReq;
    GSocket lClient;
    lReq.createReq("test", "request_send");
    std::string lResponse = lClient.callServer(lReq.toString());
    GLOGT(eGINF, "%s", lReq.toString().c_str());
    GLOGT(eGINF, "%s", lResponse.c_str());
}
//===============================================
void GTest::runRequestSaveUser(int _argc, char** _argv) {
    GLOGT(eGMSG, "");
    GCode lReq;
    GSocket lClient;
    lReq.createReq("test", "save_user");
    lReq.createCode("parameters", "firstname", "Gerard");
    lReq.createCode("parameters", "lastname", "KESSE");
    std::string lResponse = lClient.callServer(lReq.toString());
    GERROR_LOAD(eGERR, lResponse);
    GLOGT(eGINF, "[EMISSION]...: (%d)\n(%s)\n", (int)lReq.toString().size(), lReq.toString().c_str());
    GLOGT(eGINF, "[RECEPTION]..: (%d)\n(%s)\n", (int)lResponse.size(), lResponse.c_str());
}
//===============================================
void GTest::runRequestGetUser(int _argc, char** _argv) {
    GLOGT(eGMSG, "");
    GCode lReq;
    GSocket lClient;
    lReq.createReq("test", "get_user");
    std::string lResponse = lClient.callServer(lReq.toString());
    GERROR_LOAD(eGERR, lResponse);
    GCode lRes(lResponse);
    GLOGT(eGINF, "[EMISSION]...: (%d)\n(%s)\n", (int)lReq.toString().size(), lReq.toString().c_str());
    GLOGT(eGINF, "[RECEPTION]..: (%d)\n(%s)\n", (int)lResponse.size(), lResponse.c_str());
    GLOGT(eGINF, ""
            "firstname.....: %s\n"
            "lastname......: %s\n"
            "", lRes.getItem("user", "firstname").c_str()
            , lRes.getItem("user", "lastname").c_str()
    );
}
//===============================================
void GTest::runRequestError(int _argc, char** _argv) {
    GLOGT(eGMSG, "");
    GCode lReq;
    GSocket lClient;
    lReq.createReq("test", "error");
    std::string lResponse = lClient.callServer(lReq.toString());
    GERROR_LOAD(eGERR, lResponse);
    GLOGT(eGINF, "[EMISSION]...: (%d)\n(%s)\n", (int)lReq.toString().size(), lReq.toString().c_str());
    GLOGT(eGINF, "[RECEPTION]..: (%d)\n(%s)\n", (int)lResponse.size(), lResponse.c_str());
}
//===============================================
void GTest::runResponse(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    GCode lRes;
    lRes.createCode("request", "module", "test");
    lRes.createCode("request", "method", "save_user");
    lRes.createCode("request", "method", "do_user");
    lRes.createCode("result", "msg", "ok");
    lRes.createCode("opencv", "version", "4.0");
    lRes.createCode("opencv", "version", "5.0");
    lRes.createMap("error", "msg", "le chemin est incorrect", 0);
    lRes.createMap("error", "code", "1111", 0);
    lRes.createMap("error", "msg", "la donnee est incorrect", 1);
    lRes.createMap("error", "code", "2222", 1);
    lRes.createMap("error", "code", "3333", 1);

    GLOGT(eGINF, "%s", GSTRC(lRes.hasCode("result")).c_str());        // true
    GLOGT(eGINF, "%s", GSTRC(lRes.hasCode("resulto")).c_str());       // false
    GLOGT(eGINF, "%s", GSTRC(lRes.hasCode("error")).c_str());         // true
    GLOGT(eGINF, "%s", GSTRC(lRes.hasCode("error", "msg")).c_str());  // true
    GLOGT(eGINF, "%s", GSTRC(lRes.hasCode("error", "msgo")).c_str()); // false
    GLOGT(eGINF, ""
            "module.......: %s\n"
            "method.......: %s\n"
            "", lRes.getItem("request", "module").c_str()
            , lRes.getItem("request", "method").c_str()
    );

    GLOGT(eGINF, "%s", lRes.toString().c_str());
}
//===============================================
void GTest::runMysql(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    GMySQL lMySQL;
    std::string lSql = "select user from mysql.user";
    GLOGT(eGINF, "%s", lMySQL.readData(lSql).c_str());
    GLOGT(eGINF, "%s", GSTRC(lMySQL.readCol(lSql)).c_str());
}
//===============================================
void GTest::runMysqlShell(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    std::string lCommand = sformat(""
            " GUSER=admin \n"
            " GPASSWORD=xKCQY7GiGTVJ4l334QxN87@TKg \n"
            " ps_sql() { \n"
            "    mysql -u$GUSER -p$GPASSWORD -Bse \"$1\" \n"
            " } \n"
            " ps_sql \" \n"
            "    show databases; \n"
            " \" \n"
            "");
    std::string lOutput = GShell().runSystem(lCommand);
    GLOGT(eGINF, "%s", lOutput.c_str());
}
//===============================================
void GTest::runMysqlShellConfig(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    std::string lCommand = sformat(""
            " GCONFIG=mysql/conf/pkg_config.cnf \n"
            " GCONFIG=$GPROJECT_DATA/$GCONFIG \n"
            " ps_sql() { \n"
            "    mysql --defaults-extra-file=$GCONFIG -Bse \"$1\" \n"
            " } \n"
            " ps_sql \" \n"
            "    show databases; \n"
            " \" \n"
            "");
    std::string lOutput = GShell().runSystem(lCommand);
    GLOGT(eGINF, "%s", lOutput.c_str());
}
//===============================================
void GTest::runMysqlShellFile(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    std::string lCommand = sformat(""
            " . $GPROJECT_DATA/mysql/pkg/pkg_var.sh \n"
            " . $GPKG/pkg_mysql.sh \n"
            " ps_sql \"show databases;\" \n"
            "");
    std::string lOutput = GShell().runSystem(lCommand);
    GLOGT(eGINF, "%s", lOutput.c_str());
}
//===============================================
void GTest::runMysqlShellScript(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    std::string lCommand = sformat(""
            " $GPROJECT_DATA/mysql/pkg/pkg_maj.sh %s \n"
            "", "pad");
    std::string lOutput = GShell().runSystem(lCommand);
    GLOGT(eGINF, "%s", lOutput.c_str());
}
//===============================================
void GTest::runMysqlDB(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    std::string lCommand = sformat(""
            " $GPROJECT_DATA/mysql/pkg/pkg_database.sh \n"
            "");
    std::string lOutput = GShell().runSystem(lCommand);
}
//===============================================
void GTest::runMysqlMaj(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    std::string lPath = GRES("mysql", "maj");
    std::vector<std::string> lFiles = GDir().openDir(lPath, false, false);
    GLOGT(eGMSG, "%s\n", GSTRC(lFiles).c_str());
    for(int i = 0; i < (int)lFiles.size(); i++) {
        std::string lFile = lFiles.at(i);
        GMaj lMaj(lPath, lFile);
        lMaj.createDB();
        lMaj.loadCode();
        lMaj.loadId();
        lMaj.saveData();
        lMaj.runMaj();
    }
}
//===============================================
void GTest::runMysqlMajProd(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    std::string lPath = GRES("mysql", "maj");
    std::vector<std::string> lFiles = GDir().openDir(lPath, false, false);
    GLOGT(eGMSG, "%s\n", GSTRC(lFiles).c_str());
    for(int i = 0; i < (int)lFiles.size(); i++) {
        std::string lFile = lFiles.at(i);
        GMaj lMaj(lPath, lFile);
        lMaj.createDB(false);
        lMaj.loadCode();
        lMaj.loadId(false);
        lMaj.saveData(false);
        lMaj.runMaj(false);
    }
}
//===============================================
void GTest::runShellSystem(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    std::string lCommand = "";
    lCommand += sformat("echo \"Bonjour tout le monde\"\n");
    lCommand += sformat("ls -l $HOME\n");
    std::string lData = GShell().runSystem(lCommand);
    GLOGT(eGINF, "%s", lData.c_str());
}
//===============================================
void GTest::runEnv(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    std::string lTmp = GEnv().getEnv("GPROJECT_TMP");
    std::string lCommand = sformat("if ! [ -d %s ] ; then mkdir -p %s ; fi", lTmp.c_str(), lTmp.c_str());
    GLOGT(eGINF, "%s", lCommand.c_str());
}
//===============================================
void GTest::runEnvType(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    GEnv lEnv;
    std::string lEnvType = lEnv.getEnvType();
    GLOGT(eGINF, "%s", lEnvType.c_str());
}
//===============================================
void GTest::runDate(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    std::string lDate = GDate().getDate(GDate().getDateTimeFileFormat());
    GLOGT(eGINF, "%s", lDate.c_str());
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
    GLOGT(eGINF, "%s", lLog.c_str());
}
//===============================================
void GTest::runLogMacro(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    GLOGT(eGINF, "");
    GLOGT(eGINF, "Bonjour tout le monde");
    GLOGT(eGERR, "Erreur la methode a echoue");
}
//===============================================
void GTest::runLogCat(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    GLOGI->catLogFile();
}
//===============================================
void GTest::runLogTail(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    GLOGI->tailLogFile(GEnv().isTestEnv());
}
//===============================================
void GTest::runLogTailProd(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    GLOGI->tailLogFile(0);
}
//===============================================
void GTest::runFile(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    std::string lData = "";
    lData += "Bonjour tout le monde\n";
    lData += "Bonjour tout le monde\n";
    lData += "Bonjour tout le monde\n";
    GFile(GFile().getLogFullname()).setContent(lData);
}
//===============================================
void GTest::runDir(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    GLOGT(eGINF, "%s", GSTRC(GDir().openDir(GRES("mysql", "maj"), true, false)).c_str());
}
//===============================================
void GTest::runBase64(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    std::string lData1 = "<xml>Bonjour tout le </xml>";
    std::string lData2 = GBase64(lData1).encodeData();
    std::string lData3 = GBase64(lData2).decodeData();
    GLOGT(eGINF, ""
            "1............: %s\n"
            "2............: %s\n"
            "3............: %s\n"
            "", lData1.c_str(), lData2.c_str(), lData3.c_str());
}
//===============================================
void GTest::runMd5(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    std::string lData1 = "root|admin";
    std::string lData2 = GMd5(lData1).encodeData();
    GLOGT(eGINF, ""
            "1............: %s\n"
            "2............: %s\n"
            "", lData1.c_str(), lData2.c_str());
}
//===============================================
void GTest::runMd5Key(int _argc, char** _argv) {
    GLOGT(eGFUN, "");

    std::string lData1 = "produitpargerardkesse";
    std::string lData2 = GMd5(lData1).encodeData();
    std::string lData3 = sformat("%s;%d", lData2.c_str(), 350);
    std::string lData4 = sformat("%-*s", 100, lData3.c_str());

    GLOGT(eGINF, ""
            "1............: (%s)\n"
            "2............: (%s)\n"
            "3............: (%s)\n"
            "4............: (%s)\n"
            "", lData1.c_str()
            , lData2.c_str()
            , lData3.c_str()
            , lData4.c_str()
    );
}
//===============================================
void GTest::onModule(GSocket* _client) {
    std::string lMethod = _client->getReq()->getMethod();
    //===============================================
    // method
    //===============================================
    if(lMethod == "save_user") {
        onRequestSaveUser(_client);
    }
    else if(lMethod == "get_user") {
        onRequestGetUser(_client);
    }
    else if(lMethod == "error") {
        onRequestError(_client);
    }
    //===============================================
    // unknown
    //===============================================
    else {
        onMethodUnknown(_client);
    }
}
//===============================================
void GTest::onRequestSaveUser(GSocket* _client) {
    std::string lFirstname = _client->getReq()->getItem("parameters", "firstname");
    std::string lLastname = _client->getReq()->getItem("parameters", "lastname");
    GLOGT(eGFUN, "");
    GLOGT(eGINF, "firstname...: (%s)\n", lFirstname.c_str());
    GLOGT(eGINF, "lastname....: (%s)\n", lLastname.c_str());
}
//===============================================
void GTest::onRequestGetUser(GSocket* _client) {
    std::shared_ptr<GCode>& lRes = _client->getResponse();
    lRes->createCode("user", "firstname", "Gerard");
    lRes->createCode("user", "lastname", "KESSE");
}
//===============================================
void GTest::onRequestError(GSocket* _client) {
    GERROR(eGERR, "Erreur cet identifiant existe deja");
    GERROR(eGERR, "Erreur le mot de passe est incorrect");
}
//===============================================
