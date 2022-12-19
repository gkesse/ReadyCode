//===============================================
#ifndef _GSocketTest_
#define _GSocketTest_
//===============================================
#include "GObject.h"
//===============================================
class GSocketTest : public GObject {
public:
    GSocketTest(const GString& _code = "socket_test");
    ~GSocketTest();
    void run(int _argc, char** _argv);
    void runDefault(int _argc, char** _argv);
    void runServerTcpEcho(int _argc, char** _argv);
    void runServerUdp(int _argc, char** _argv);
};
//==============================================
#endif
//==============================================