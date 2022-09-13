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
    else if(lKey == "server/echo") {
        runServerEcho(_argc, _argv);
    }
    else if(lKey == "dns") {
        runDns(_argc, _argv);
    }
    else if(lKey == "stream") {
        runStream(_argc, _argv);
    }
    else if(lKey == "stream/http") {
        runStreamHttp(_argc, _argv);
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
    lPoco.run(_argc, _argv);
}
//===============================================
void GTestPoco::runDns(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    GPoco lPoco;
    lPoco.setModule("dns");
    lPoco.setHostname("readydev.ovh");
    lPoco.run(_argc, _argv);
}
//===============================================
void GTestPoco::runStream(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    GPoco lPoco;
    lPoco.setModule("stream");
    lPoco.setHostname("pratique.leparisien.fr");
    lPoco.setPort(80);
    lPoco.setRequest(""
            ""
            " GET / HTTP/1.1\r\n "
            " Host: pratique.leparisien.fr\r\n "
            " \r\n "
            "");
    lPoco.run(_argc, _argv);
}
//===============================================
void GTestPoco::runStreamHttp(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    GPoco lPoco;
    lPoco.setModule("stream/http");
    lPoco.setPort(9001);
    lPoco.setResponse(""
            ""
            " HTTP/1.0 200 OK\r\n "
            " Content-Type: text/html\r\n "
            " \r\n "
            " <html><head><title>My 1st Web Server</title></head> "
            " <body><h1>Bonjour tout le monde !</h1></body></html> "
            "");
    lPoco.run(_argc, _argv);
}
//===============================================
