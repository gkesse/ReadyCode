//===============================================
#include "GTestSocket.h"
#include "GLog.h"
#include "GFormat.h"
//===============================================
GTestSocket* GTestSocket::m_test = 0;
//===============================================
GTestSocket::GTestSocket()
: GObject() {

}
//===============================================
GTestSocket::~GTestSocket() {

}
//===============================================
void GTestSocket::run(int _argc, char** _argv) {
    std::string lKey = "default";
    if(_argc > 2) lKey = _argv[2];

    if(lKey == "default") {
        runDefault(_argc, _argv);
    }
    else if(lKey == "tcp") {
        runTcp(_argc, _argv);
    }
    else {
        runDefault(_argc, _argv);
    }
}
//===============================================
void GTestSocket::runDefault(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
}
//===============================================
void GTestSocket::runTcp(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
}
//===============================================
