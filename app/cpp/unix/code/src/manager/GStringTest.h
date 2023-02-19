//===============================================
#ifndef _GStringTest_
#define _GStringTest_
//===============================================
#include "GObject.h"
//===============================================
class GStringTest : public GObject {
public:
    GStringTest();
    ~GStringTest();
    void run(int _argc, char** _argv);
    void runTest(int _argc, char** _argv);
};
//==============================================
#endif
//==============================================
