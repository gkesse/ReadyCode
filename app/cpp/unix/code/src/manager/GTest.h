//===============================================
#ifndef _GTest_
#define _GTest_
//===============================================
#include "GManager.h"
//===============================================
class GTest : public GManager {
public:
    GTest();
    ~GTest();
    void run(int _argc, char** _argv);
    void runDefault(int _argc, char** _argv);
    void runPoco(int _argc, char** _argv);
    void runCurl(int _argc, char** _argv);
    void runSocket(int _argc, char** _argv);

public:
    GLog m_logs;
};
//===============================================
#endif
//===============================================
