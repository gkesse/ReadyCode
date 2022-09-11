//===============================================
#include "GTestPoco.h"
#include "GPoco.h"
#include "GLog.h"
#include "GFormat.h"
//===============================================
GTestPoco::GTestPoco()
: GObject() {

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
    GPoco lPoco;
    lPoco.setKey("ping");
    lPoco.setFamily(Poco::Net::IPAddress::IPv4);
    lPoco.setRepetition(4);
    lPoco.setHostname("localhsot");

    try {
        lPoco.init(_argc, _argv);
    }
    catch (Poco::Exception& _e) {
        lPoco.showLogApp(_e);
        return;
    }

    lPoco.run();
}
//===============================================
