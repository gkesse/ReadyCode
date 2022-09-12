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
    else if(lKey == "server/tcp") {
        runServerTcp(_argc, _argv);
    }
    else if(lKey == "server/time") {
        runServerTime(_argc, _argv);
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
    lPoco.setModule("ping");
    lPoco.setFamily(Poco::Net::IPAddress::IPv4);
    lPoco.setRepetitions(4);
    lPoco.setHostname("readydev.ovh");
    lPoco.init(_argc, _argv);
    lPoco.run();
}
//===============================================
void GTestPoco::runServerTcp(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    GPoco lPoco;
    lPoco.setModule("tcp");
    lPoco.setPort(9001);
    lPoco.startServer();
}
//===============================================
void GTestPoco::runServerTime(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    GPoco lPoco;
    lPoco.setModule("time");
    lPoco.setFormat(Poco::DateTimeFormat::ISO8601_FORMAT);
    lPoco.setPort(9001);
    lPoco.run(_argc, _argv);
}
//===============================================
void GTestPoco::runServerEcho(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    GPoco lPoco;
    lPoco.setModule("echo");
    lPoco.setPort(9001);
    lPoco.init();
    lPoco.run(_argc, _argv);
}
//===============================================
