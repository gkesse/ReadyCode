//===============================================
#ifndef _GXmlTest_
#define _GXmlTest_
//===============================================
#include "GObject.h"
//===============================================
class GXmlTest : public GObject {
public:
    GXmlTest();
    ~GXmlTest();
    void run(int _argc, char** _argv);
    void runTest(int _argc, char** _argv);
    void runTestNext(GCode& _dom);
    void runDom(int _argc, char** _argv);
    void runSerialize(int _argc, char** _argv);
    void runXNode(int _argc, char** _argv);
    void runNode(int _argc, char** _argv);
};
//==============================================
#endif
//==============================================
