//===============================================
#ifndef _GCurlTest_
#define _GCurlTest_
//===============================================
#include "GObject.h"
//===============================================
class GCurlTest : public GObject {
public:
    GCurlTest(const GString& _code = "curl_test");
    ~GCurlTest();
    void run(int _argc, char** _argv);
    void runDefault(int _argc, char** _argv);
    void runGet(int _argc, char** _argv);
};
//==============================================
#endif
//==============================================
