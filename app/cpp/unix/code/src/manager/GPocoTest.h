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
    void runHttpGet(int _argc, char** _argv);
    void runServer(int _argc, char** _argv);
};
//==============================================
#endif
//==============================================
