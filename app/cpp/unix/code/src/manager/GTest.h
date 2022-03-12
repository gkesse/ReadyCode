//===============================================
#ifndef _GTest_
#define _GTest_
//===============================================
#include "GObject.h"
//===============================================
class GTest : public GObject {
public:
    GTest();
    ~GTest();
    void run(int _argc, char** _argv);
    void runTest(int _argc, char** _argv);
    void runIntString(int _argc, char** _argv);
    void runIntStringVector(int _argc, char** _argv);
    void runString(int _argc, char** _argv);
    void runPath(int _argc, char** _argv);
    void runFormat(int _argc, char** _argv);
    void runXml(int _argc, char** _argv);
    std::string getPadItem(const std::string& _data) const;
    void runSocketServer(int _argc, char** _argv);
    void runSocketClient(int _argc, char** _argv);
    void runSocketServerFile(int _argc, char** _argv);
    void runSocketClientFile(int _argc, char** _argv);
    void runSocketServerStart(int _argc, char** _argv);
    void runSocketClientStart(int _argc, char** _argv);
    void runThread(int _argc, char** _argv);
    static void* onThread(void* _params);
    void runExit(int _argc, char** _argv);
    void runInterrupt(int _argc, char** _argv);
    void runTimer(int _argc, char** _argv);
    void runRequest(int _argc, char** _argv);
    void runRequestSend(int _argc, char** _argv);
};
//===============================================
#endif
//===============================================
