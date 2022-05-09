//===============================================
#ifndef _GTest_
#define _GTest_
//===============================================
#include "GModule.h"
//===============================================
class GSocket;
//===============================================
class GTest : public GModule {
public:
    GTest();
    ~GTest();
    void run(int _argc, char** _argv);
    void runTest(int _argc, char** _argv);
    void runIntString(int _argc, char** _argv);
    void runIntStringVector(int _argc, char** _argv);
    void runString(int _argc, char** _argv);
    void runStringInt(int _argc, char** _argv);
    void runPath(int _argc, char** _argv);
    void runFormat(int _argc, char** _argv);
    void runXml(int _argc, char** _argv);
    void runXmlCheck(int _argc, char** _argv);
    void runSocketServer(int _argc, char** _argv);
    void runSocketClient(int _argc, char** _argv);
    void runSocketServerFile(int _argc, char** _argv);
    void runSocketClientFile(int _argc, char** _argv);
    void runSocketServerStart(int _argc, char** _argv);
    static void* onSocketServerStartThread(void* _params);
    static void onSocketServerStartTimer(int _signo);
    void runSocketClientStart(int _argc, char** _argv);
    void runThread(int _argc, char** _argv);
    static void* onThread(void* _params);
    void runExit(int _argc, char** _argv);
    void runInterrupt(int _argc, char** _argv);
    void runTimer(int _argc, char** _argv);
    void runRequest(int _argc, char** _argv);
    void runRequestSend(int _argc, char** _argv);
    void runRequestSaveUser(int _argc, char** _argv);
    void runRequestGetUser(int _argc, char** _argv);
    void runRequestError(int _argc, char** _argv);
    void runResponse(int _argc, char** _argv);
    void runMysql(int _argc, char** _argv);
    void runMysqlShell(int _argc, char** _argv);
    void runMysqlShellConfig(int _argc, char** _argv);
    void runMysqlShellFile(int _argc, char** _argv);
    void runMysqlShellScript(int _argc, char** _argv);
    void runMysqlDB(int _argc, char** _argv);
    void runMysqlMaj(int _argc, char** _argv);
    void runShellSystem(int _argc, char** _argv);
    void runEnv(int _argc, char** _argv);
    void runEnvType(int _argc, char** _argv);
    void runDate(int _argc, char** _argv);
    void runTmpClean(int _argc, char** _argv);
    void runLog(int _argc, char** _argv);
    void runLogMacro(int _argc, char** _argv);
    void runLogCat(int _argc, char** _argv);
    void runLogTail(int _argc, char** _argv);
    void runLogTailProd(int _argc, char** _argv);
    void runFile(int _argc, char** _argv);
    void runDir(int _argc, char** _argv);
    void runBase64(int _argc, char** _argv);
    void runMd5(int _argc, char** _argv);
    void runMd5Key(int _argc, char** _argv);
    //
    void onModule(GSocket* _client);
    void onRequestSaveUser(GSocket* _client);
    void onRequestGetUser(GSocket* _client);
    void onRequestError(GSocket* _client);

private:
    static GTest* m_test;
    GSocket* m_server;
};
//===============================================
#endif
//===============================================
