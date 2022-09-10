//===============================================
#include "GTest.h"
#include "GCurl.h"
//===============================================
GTest::GTest()
: GObject()
{

}
//===============================================
GTest::~GTest()
{

}
//===============================================
void GTest::run(int _argc, char** _argv)
{
    std::string lKey = "default";
    if(_argc > 2) lKey = _argv[2];

    if(lKey == "default")
    {
        runDefault(_argc, _argv);
    }
    else if(lKey == "curl")
    {
        runCurl(_argc, _argv);
    }
    else
    {
        runDefault(_argc, _argv);
    }
}
//===============================================
void GTest::runDefault(int _argc, char** _argv)
{
    printf("Aucun process n'a été sélectionné.\n");
}
//===============================================
void GTest::runCurl(int _argc, char** _argv)
{
    printf("[ INFO ] : %s\n", __PRETTY_FUNCTION__);
    GCurl lCurl;
    lCurl.setUrl("http://web.simmons.edu/");
    lCurl.setOption(CURLINFO_CONTENT_TYPE);
    std::string lInfo;
    if(lCurl.getInfo(lInfo))
    {
        printf("[ DATA ] : %s\n", lInfo.c_str());
    }
}
//===============================================
