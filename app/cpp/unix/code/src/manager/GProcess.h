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
    void initProcess();
    void run(int _argc, char** _argv);
    void runTest(int _argc, char** _argv);
    void runProd(int _argc, char** _argv);
};
//===============================================
#endif
//===============================================
