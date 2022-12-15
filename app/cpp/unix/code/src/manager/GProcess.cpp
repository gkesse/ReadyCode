//===============================================
#include "GProcess.h"
#include "GLog.h"
#include "GServer.h"
//===============================================
GProcess::GProcess()
: GObject() {

}
//===============================================
GProcess::~GProcess() {

}
//===============================================
void GProcess::run(int _argc, char** _argv) {
    GString lKey = "";
    if(_argc > 1) lKey = _argv[1];
    if(lKey == "") {
        runDefault(_argc, _argv);
    }
    else if(lKey == "server") {
        runServer(_argc, _argv);
    }
    else {
        runDefault(_argc, _argv);
    }
}
//===============================================
void GProcess::runDefault(int _argc, char** _argv) {
    GLOGT(eGMSG, "Le process est inconnu.");
}
//===============================================
void GProcess::runServer(int _argc, char** _argv) {
    GRUN_SERVER(_argc, _argv);
}
//===============================================
