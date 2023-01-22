//===============================================
#ifndef _GOpenSSLTest_
#define _GOpenSSLTest_
//===============================================
#include "GObject.h"
//===============================================
class GOpenSSLTest : public GObject {
public:
    GOpenSSLTest();
    ~GOpenSSLTest();
    void run(int _argc, char** _argv);
    void runTest(int _argc, char** _argv);
};
//==============================================
#endif
//==============================================
