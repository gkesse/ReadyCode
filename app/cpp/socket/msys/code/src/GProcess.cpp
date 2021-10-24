//===============================================
#include "GProcess.h"
#include "GSocketUi.h"
#include "GOpenCVUi.h"
#include "GXmlUi.h"
#include "GAsioUi.h"
#include "GCurlUi.h"
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
    if(lKey == "opencv") {runOpenCV(argc, argv); return;}
    if(lKey == "xml") {runXml(argc, argv); return;}
    if(lKey == "asio") {runAsio(argc, argv); return;}
    if(lKey == "curl") {runCurl(argc, argv); return;}
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
void GProcess::runOpenCV(int argc, char** argv) {
    std::string lKey = "default";
    if(argc > 2) {lKey = argv[2];}
    GOpenCVUi* lProcess = GOpenCVUi::Create(lKey);
    lProcess->run(argc, argv);
}
//===============================================
void GProcess::runXml(int argc, char** argv) {
    std::string lKey = "default";
    if(argc > 2) {lKey = argv[2];}
    GXmlUi* lProcess = GXmlUi::Create(lKey);
    lProcess->run(argc, argv);
}
//===============================================
void GProcess::runAsio(int argc, char** argv) {
    std::string lKey = "default";
    if(argc > 2) {lKey = argv[2];}
    GAsioUi* lProcess = GAsioUi::Create(lKey);
    lProcess->run(argc, argv);
}
//===============================================
void GProcess::runCurl(int argc, char** argv) {
    std::string lKey = "default";
    if(argc > 2) {lKey = argv[2];}
    GCurlUi* lProcess = GCurlUi::Create(lKey);
    lProcess->run(argc, argv);
}
//===============================================
