//===============================================
#ifndef _GPocoTest_
#define _GPocoTest_
//===============================================
#include "GObject.h"
//===============================================
class GPocoTest : public GObject {
public:
    GPocoTest();
    ~GPocoTest();
    void run(int _argc, char** _argv);
    void runTest(int _argc, char** _argv);
    void runHttp(int _argc, char** _argv);
    void runHttps(int _argc, char** _argv);
};
//==============================================
#endif
//==============================================
