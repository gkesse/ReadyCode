//===============================================
#ifndef _GPocoTest_
#define _GPocoTest_
//===============================================
#include "GObject.h"
//===============================================
class GPocoTest : public GObject {
public:
    GPocoTest(const GString& _code = "poco_test");
    ~GPocoTest();
    void run(int _argc, char** _argv);
    void runDefault(int _argc, char** _argv);
    void runGet(int _argc, char** _argv);
    void runServer(int _argc, char** _argv);
};
//==============================================
#endif
//==============================================