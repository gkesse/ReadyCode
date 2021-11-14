//===============================================
#include "GProcess.h"
#include "GCppUi.h"
#include "GSocketUi.h"
#include "GOpenGLUi.h"
#include "GQtUi.h"
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
    if(lKey == "qt") {runQt(_argc, _argv); return;}
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
void GProcess::runQt(int _argc, char** _argv) {
    std::string lKey = "default";
    if(_argc > 2) {lKey = _argv[2];}
    GQtUi* lProcess = GQtUi::Create(lKey);
    lProcess->run(_argc, _argv);
}
//===============================================