//===============================================
#ifndef _GCurlTest_
#define _GCurlTest_
//===============================================
#include "GObject.h"
//===============================================
class GCurlTest : public GObject {
public:
    GCurlTest();
    ~GCurlTest();
    void run(int _argc, char** _argv);
    void runTest(int _argc, char** _argv);
    void runCall(int _argc, char** _argv);
};
//==============================================
#endif
//==============================================
