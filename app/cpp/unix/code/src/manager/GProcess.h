//===============================================
#ifndef _GProcess_
#define _GProcess_
//===============================================
#include "GObject.h"
//===============================================
class GProcess : public GObject {
public:
    GProcess();
    ~GProcess();
    void run(int _argc, char** _argv);
    void runDefault(int _argc, char** _argv);
    void runTest(int _argc, char** _argv);
    void runServer(int _argc, char** _argv);

public:
    GLog m_logs;
};
//===============================================
#endif
//===============================================
