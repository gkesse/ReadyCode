//===============================================
#include "GProcess.h"
#include "GTest.h"
#include "GTestNetwork.h"
//===============================================
GProcess::GProcess() : GObject() {

}
//===============================================
GProcess::~GProcess() {

}
//===============================================
void GProcess::run(int _argc, char** _argv) {
    std::string lKey = "default";
    if(_argc > 1) lKey = _argv[1];

    //===============================================
    // default
    //===============================================
    if(lKey == "default") {
        runDefault(_argc, _argv);
    }
    //===============================================
    // test
    //===============================================
    else if(lKey == "test") {
        runTest(_argc, _argv);
    }
    else if(lKey == "test/network") {
        runTestNetwork(_argc, _argv);
    }
    //===============================================
    // end
    //===============================================
    else {
        runDefault(_argc, _argv);
    }
}
//===============================================
void GProcess::runDefault(int _argc, char** _argv) {
    GTest().run(_argc, _argv);
}
//===============================================
void GProcess::runTest(int _argc, char** _argv) {
    GTest().run(_argc, _argv);
}
//===============================================
void GProcess::runTestNetwork(int _argc, char** _argv) {
    GTestNetwork().run(_argc, _argv);
}
//===============================================
