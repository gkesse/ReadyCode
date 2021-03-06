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

private:
    static GTestNetwork* m_test;
};
//===============================================
#endif
//===============================================
