//===============================================
#include "GProcess.h"
#include "GCppUi.h"
#include "GSocketUi.h"
#include "GOpenGLUi.h"
#include "GXmlUi.h"
#include "GMasterUi.h"
#include "GServerUi.h"
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
void GProcess::run(int _argc, char** _argv) {
    std::string lKey = "default";
    if(_argc > 1) {lKey = _argv[1];}
    if(lKey == "default") {runDefault(_argc, _argv); return;}
    if(lKey == "cpp") {runCpp(_argc, _argv); return;}
    if(lKey == "socket") {runSocket(_argc, _argv); return;}
    if(lKey == "opengl") {runOpenGL(_argc, _argv); return;}
    if(lKey == "xml") {runXml(_argc, _argv); return;}
    if(lKey == "master") {runMaster(_argc, _argv); return;}
    if(lKey == "server") {runServer(_argc, _argv); return;}
    runDefault(_argc, _argv);
}
//===============================================
void GProcess::runDefault(int _argc, char** _argv) {
    printf("[process] process par defaut\n");
}
//===============================================
void GProcess::runCpp(int _argc, char** _argv) {
    std::string lKey = "default";
    if(_argc > 2) {lKey = _argv[2];}
    GCppUi* lProcess = GCppUi::Create(lKey);
    lProcess->run(_argc, _argv);
}
//===============================================
void GProcess::runSocket(int _argc, char** _argv) {
    std::string lKey = "default";
    if(_argc > 2) {lKey = _argv[2];}
    GSocketUi* lProcess = GSocketUi::Create(lKey);
    lProcess->run(_argc, _argv);
}
//===============================================
void GProcess::runOpenGL(int _argc, char** _argv) {
    std::string lKey = "default";
    if(_argc > 2) {lKey = _argv[2];}
    GOpenGLUi* lProcess = GOpenGLUi::Create(lKey);
    lProcess->run(_argc, _argv);
}
//===============================================
void GProcess::runXml(int _argc, char** _argv) {
    std::string lKey = "default";
    if(_argc > 2) {lKey = _argv[2];}
    GXmlUi* lProcess = GXmlUi::Create(lKey);
    lProcess->run(_argc, _argv);
}
//===============================================
void GProcess::runMaster(int _argc, char** _argv) {
    std::string lKey = "default";
    if(_argc > 2) {lKey = _argv[2];}
    GMasterUi* lProcess = GMasterUi::Create(lKey);
    lProcess->run(_argc, _argv);
}
//===============================================
void GProcess::runServer(int _argc, char** _argv) {
    std::string lKey = "default";
    if(_argc > 2) {lKey = _argv[2];}
    GServerUi* lProcess = GServerUi::Create(lKey);
    lProcess->run(_argc, _argv);
}
//===============================================
