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
    void runGetHttp(int _argc, char** _argv);
    void runGetHttps(int _argc, char** _argv);
    void runGetHttpsCert(int _argc, char** _argv);
    void runPostXml(int _argc, char** _argv);
    void runPostHttpsXml(int _argc, char** _argv);
    void runPostForm(int _argc, char** _argv);
    void runCall(int _argc, char** _argv);
};
//==============================================
#endif
//==============================================
