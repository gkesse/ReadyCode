//===============================================
#include "GProcess.h"
#include "GSocketUi.h"
#include "GXmlRpcUi.h"
#include "GOpenGLUi.h"
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
    if(lKey == "xmlrpc") {runXmlRpc(argc, argv); return;}
    if(lKey == "opengl") {runOpenGL(argc, argv); return;}
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
void GProcess::runXmlRpc(int argc, char** argv) {
    std::string lKey = "default";
    if(argc > 2) {lKey = argv[2];}
    GXmlRpcUi* lProcess = GXmlRpcUi::Create(lKey);
    lProcess->run(argc, argv);
}
//===============================================
void GProcess::runOpenGL(int argc, char** argv) {
    std::string lKey = "default";
    if(argc > 2) {lKey = argv[2];}
    GOpenGLUi* lProcess = GOpenGLUi::Create(lKey);
    lProcess->run(argc, argv);
}
//===============================================
