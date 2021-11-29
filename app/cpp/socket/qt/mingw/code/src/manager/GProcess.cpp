//===============================================
#include "GProcess.h"
#include "GQtUi.h"
#include "GXmlUi.h"
#include "GSocketUi.h"
#include "GSQLiteUi.h"
#include "GFileUi.h"
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
    if(lKey == "xml") {runXml(_argc, _argv); return;}
    if(lKey == "socket") {runSocket(_argc, _argv); return;}
    if(lKey == "sqlite") {runSQLite(_argc, _argv); return;}
    if(lKey == "file") {runFile(_argc, _argv); return;}
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
void GProcess::runXml(int _argc, char** _argv) {
    QString lKey = "default";
    if(_argc > 2) {lKey = _argv[2];}
    GXmlUi* lProcess = GXmlUi::Create(lKey);
    lProcess->run(_argc, _argv);
}
//===============================================
void GProcess::runSocket(int _argc, char** _argv) {
    QString lKey = "default";
    if(_argc > 2) {lKey = _argv[2];}
    GSocketUi* lProcess = GSocketUi::Create(lKey);
    lProcess->run(_argc, _argv);
}
//===============================================
void GProcess::runSQLite(int _argc, char** _argv) {
    QString lKey = "default";
    if(_argc > 2) {lKey = _argv[2];}
    GSQLiteUi* lProcess = GSQLiteUi::Create(lKey);
    lProcess->run(_argc, _argv);
}
//===============================================
void GProcess::runFile(int _argc, char** _argv) {
    QString lKey = "default";
    if(_argc > 2) {lKey = _argv[2];}
    GFileUi* lProcess = GFileUi::Create(lKey);
    lProcess->run(_argc, _argv);
}
//===============================================
