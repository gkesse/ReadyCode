//===============================================
#ifndef _GTest_
#define _GTest_
//===============================================
#include "GObject.h"
//===============================================
class GTest : public GObject
{
public:
    GTest();
    ~GTest();
    void run(int _argc, char** _argv);
    void runDefault(int _argc, char** _argv);
    void runCurl(int _argc, char** _argv);
};
//===============================================
#endif
//===============================================
