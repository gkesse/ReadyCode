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
    void runPoco(int _argc, char** _argv);
    void runXml(int _argc, char** _argv);
    void runJson(int _argc, char** _argv);
    void runCurl(int _argc, char** _argv);
    void runSocket(int _argc, char** _argv);
    void runOpenSSL(int _argc, char** _argv);
    void runString(int _argc, char** _argv);

public:
    GLog m_logs;
};
//===============================================
#endif
//===============================================
