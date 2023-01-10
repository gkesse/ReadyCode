//===============================================
#ifndef _GSocketTest_
#define _GSocketTest_
//===============================================
#include "GObject.h"
//===============================================
class GSocketTest : public GObject {
public:
    GSocketTest();
    ~GSocketTest();
    void run(int _argc, char** _argv);
    void runDefault(int _argc, char** _argv);
    void runClientTcpEcho(int _argc, char** _argv);
    void runClientTcpEchoXml(int _argc, char** _argv);
};
//==============================================
#endif
//==============================================
