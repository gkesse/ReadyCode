//===============================================
#include "GProcess.h"
#include "GTest.h"
//===============================================
GProcess::GProcess()
: GObject()
{

}
//===============================================
GProcess::~GProcess()
{

}
//===============================================
void GProcess::run(int _argc, char** _argv)
{
    std::string lKey = "default";
    if(_argc > 1) lKey = _argv[1];

    if(lKey == "default")
    {
        runDefault(_argc, _argv);
    }
    else if(lKey == "test")
    {
        runTest(_argc, _argv);
    }
    else
    {
        runDefault(_argc, _argv);
    }
}
//===============================================
void GProcess::runDefault(int _argc, char** _argv)
{
    printf("Aucun process n'a été sélectionné.\n");
}
//===============================================
void GProcess::runTest(int _argc, char** _argv)
{
    GTest lTest;
    lTest.run(_argc, _argv);
}
//===============================================
