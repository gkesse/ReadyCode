//===============================================
#ifndef _GTest_
#define _GTest_
//===============================================
#include "GObject.h"
//===============================================
class GTest : public GObject {
public:
    GTest();
    ~GTest();
    void run(int _argc, char** _argv);
    void runString(int _argc, char** _argv);
    void runLog(int _argc, char** _argv);
    void runXml(int _argc, char** _argv);
    void runCode(int _argc, char** _argv);
    void runSocket(int _argc, char** _argv);
};
//===============================================
#endif
//===============================================
