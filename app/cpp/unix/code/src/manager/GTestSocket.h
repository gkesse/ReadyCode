//===============================================
#ifndef _GTestSocket_
#define _GTestSocket_
//===============================================
#include "GObject.h"
//===============================================
class GSocket;
//===============================================
class GTestSocket : public GObject {
public:
    GTestSocket();
    ~GTestSocket();
    void run(int _argc, char** _argv);
    void runDefault(int _argc, char** _argv);
    void runTcp(int _argc, char** _argv);
    void runAnalyze(int _argc, char** _argv);

private:
    static GTestSocket* m_test;
};
//===============================================
#endif
//===============================================
