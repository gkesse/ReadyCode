//===============================================
#include "GProcess.h"
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
    if(lKey == "opengl") {runOpenGL(argc, argv); return;}
    runDefault(argc, argv);
}
//===============================================
void GProcess::runDefault(int argc, char** argv) {
    std::cout << "[process] aucun process n'a ete selectionne.\n";
}
//===============================================
void GProcess::runOpenGL(int argc, char** argv) {
    std::string lKey = "default";
    if(argc > 2) {lKey = argv[2];}
    GOpenGLUi::Create(lKey)->run(argc, argv);
}
//===============================================
