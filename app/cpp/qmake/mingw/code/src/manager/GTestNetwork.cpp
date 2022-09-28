//===============================================
#include "GTestNetwork.h"
#include "GLog.h"
//===============================================
GTestNetwork* GTestNetwork::m_test = 0;
//===============================================
GTestNetwork::GTestNetwork()
: GModule() {

}
//===============================================
GTestNetwork::~GTestNetwork() {

}
//===============================================
void GTestNetwork::run(int _argc, char** _argv) {
    std::string lKey = "default";
    if(_argc > 2) lKey = _argv[2];
    //===============================================
    // default
    //===============================================
    if(lKey == "default") {
        runTest(_argc, _argv);
    }
    //===============================================
    // network
    //===============================================
    else if(lKey == "test") {
        runTest(_argc, _argv);
    }
    //===============================================
    // end
    //===============================================
    else {
        runTest(_argc, _argv);
    }
}
//===============================================
void GTestNetwork::runTest(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
}
//===============================================
