//===============================================
#ifndef _GTestNetwork_
#define _GTestNetwork_
//===============================================
#include "GModule.h"
//===============================================
class GSocket;
//===============================================
class GTestNetwork : public GModule {
public:
    GTestNetwork();
    ~GTestNetwork();
    void run(int _argc, char** _argv);
    void runTest(int _argc, char** _argv);
    void runServerSimple(int _argc, char** _argv);
    void runClientSimple(int _argc, char** _argv);
    void runServerUdp(int _argc, char** _argv);
    void runClientUdp(int _argc, char** _argv);

private:
    static GTestNetwork* m_test;
};
//===============================================
#endif
//===============================================
