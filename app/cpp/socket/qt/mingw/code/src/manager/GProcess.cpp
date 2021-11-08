//===============================================
#include "GProcess.h"
#include "GQtUi.h"
#include "GQXmlUi.h"
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
    QString lKey = "default";
    if(_argc > 1) {lKey = _argv[1];}
    if(lKey == "default") {runDefault(_argc, _argv); return;}
    if(lKey == "qt") {runQt(_argc, _argv); return;}
    if(lKey == "qxml") {runQXml(_argc, _argv); return;}
    runDefault(_argc, _argv);
}
//===============================================
void GProcess::runDefault(int _argc, char** _argv) {
    printf("[process] process par defaut\n");
}
//===============================================
void GProcess::runQt(int _argc, char** _argv) {
    QString lKey = "default";
    if(_argc > 2) {lKey = _argv[2];}
    GQtUi* lProcess = GQtUi::Create(lKey);
    lProcess->run(_argc, _argv);
}
//===============================================
void GProcess::runQXml(int _argc, char** _argv) {
    QString lKey = "default";
    if(_argc > 2) {lKey = _argv[2];}
    GQXmlUi* lProcess = GQXmlUi::Create(lKey);
    lProcess->run(_argc, _argv);
}
//===============================================
