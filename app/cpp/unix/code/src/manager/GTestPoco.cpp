//===============================================
#include "GTestPoco.h"
#include "GLog.h"
#include "GFormat.h"
//===============================================
GTestPoco::GTestPoco()
: GModule() {

}
//===============================================
GTestPoco::~GTestPoco() {

}
//===============================================
void GTestPoco::run(int _argc, char** _argv) {
    std::string lKey = "default";
    if(_argc > 2) lKey = _argv[2];

    if(lKey == "default") {
        runDefault(_argc, _argv);
    }
    else if(lKey == "ping") {
        runPing(_argc, _argv);
    }
    else {
        runDefault(_argc, _argv);
    }
}
//===============================================
void GTestPoco::runDefault(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
}
//===============================================
void GTestPoco::runPing(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
}
//===============================================
