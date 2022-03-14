//===============================================
#include "GProcess.h"
#include "GTest.h"
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

    if(lKey == "default") {
        runTest(_argc, _argv);
    }
    // test
    else if(lKey == "test") {
        runTest(_argc, _argv);
    }
    // end
    else {
        runTest(_argc, _argv);
    }
}
//===============================================
void GProcess::runTest(int _argc, char** _argv) {
    GTest lTest;
    lTest.run(_argc, _argv);
}
//===============================================
