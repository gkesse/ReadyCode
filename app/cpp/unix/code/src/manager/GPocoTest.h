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
    void runServerHttp(int _argc, char** _argv);
    void runServerHttps(int _argc, char** _argv);
    void runServerHttpsUserPass(int _argc, char** _argv);
    void runServerHttpsCert(int _argc, char** _argv);
};
//==============================================
#endif
//==============================================
