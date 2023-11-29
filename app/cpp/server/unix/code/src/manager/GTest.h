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
    void runTest(int _argc, char** _argv);
    void runLog(int _argc, char** _argv);
    void runXml(int _argc, char** _argv);
    void runCode(int _argc, char** _argv);
    void runSocket(int _argc, char** _argv);
    void runMySQL(int _argc, char** _argv);
    void runDatetime(int _argc, char** _argv);
    void runCurl(int _argc, char** _argv);
    void runEmail(int _argc, char** _argv);
};
//===============================================
#endif
//===============================================
