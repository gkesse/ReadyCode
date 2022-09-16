//===============================================
#ifndef _GTestPoco_
#define _GTestPoco_
//===============================================
#include "GObject.h"
//===============================================
class GTestPoco : public GObject {
public:
    GTestPoco();
    ~GTestPoco();
    void run(int _argc, char** _argv);
    void runDefault(int _argc, char** _argv);
    void runPing(int _argc, char** _argv);
    void runHttpGet(int _argc, char** _argv);
    void runServerTcp(int _argc, char** _argv);
    void runServerTime(int _argc, char** _argv);
    void runServerEcho(int _argc, char** _argv);
    void runDns(int _argc, char** _argv);
    void runStream(int _argc, char** _argv);
    void runStreamHttp(int _argc, char** _argv);

private:
    static GTestPoco* m_test;
};
//===============================================
#endif
//===============================================
