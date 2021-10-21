//===============================================
#include "GProcess.h"
#include "GSocketUi.h"
//===============================================
GProcess* GProcess::m_instance = 0;
//===============================================
GProcess::GProcess() {

}
//===============================================
GProcess::~GProcess() {

}
//===============================================
GProcess* GProcess::Instance() {
    if(m_instance == 0) {
        m_instance = new GProcess;
    }
    return m_instance;
}
//===============================================
void GProcess::run(int argc, char** argv) {
    std::string lKey = "default";
    if(argc > 1) {lKey = argv[1];}
    if(lKey == "default") {runDefault(argc, argv); return;}
    if(lKey == "socket") {runSocket(argc, argv); return;}
    runDefault(argc, argv);
}
//===============================================
void GProcess::runDefault(int argc, char** argv) {
    printf("[process] process par defaut\n");
}
//===============================================
void GProcess::runSocket(int argc, char** argv) {
    std::string lKey = "default";
    if(argc > 2) {lKey = argv[2];}
    GSocketUi* lProcess = GSocketUi::Create(lKey);
    lProcess->run(argc, argv);
}
//===============================================
