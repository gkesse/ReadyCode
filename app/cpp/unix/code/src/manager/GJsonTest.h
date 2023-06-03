//===============================================
#ifndef _GJsonTest_
#define _GJsonTest_
//===============================================
#include "GObject.h"
//===============================================
class GJsonTest : public GObject {
public:
    GJsonTest();
    ~GJsonTest();
    void run(int _argc, char** _argv);
    void runTest(int _argc, char** _argv);
    void runObject(int _argc, char** _argv);
    void runData(int _argc, char** _argv);
};
//==============================================
#endif
//==============================================
