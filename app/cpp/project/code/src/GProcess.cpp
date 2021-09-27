//===============================================
#include "GProcess.h"
#include "GProUi.h"
#include "GQtUi.h"
#include "GCppUi.h"
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
    QString lKey = "default";
    if(argc > 1) {lKey = argv[1];}
    if(lKey == "default") {runDefault(argc, argv); return;}
    if(lKey == "pro") {runPro(argc, argv); return;}
    if(lKey == "qt") {runQt(argc, argv); return;}
    if(lKey == "cpp") {runCpp(argc, argv); return;}
    runDefault(argc, argv);
}
//===============================================
void GProcess::runDefault(int argc, char** argv) {
    qDebug() << "[process] aucun process n'a ete selectionne.";
}
//===============================================
void GProcess::runPro(int argc, char** argv) {
    QString lKey = "default";
    if(argc > 2) {lKey = argv[2];}
    QApplication app(argc, argv);
    GProUi* lWindow = GProUi::Create(lKey);
    lWindow->setTitle();
    lWindow->setSize();
    lWindow->show();
    app.exec();
}
//===============================================
void GProcess::runQt(int argc, char** argv) {
    QString lKey = "default";
    if(argc > 2) {lKey = argv[2];}
    GQtUi* lQt = GQtUi::Create(lKey);
    lQt->run(argc, argv);
}
//===============================================
void GProcess::runCpp(int argc, char** argv) {
    QString lKey = "default";
    if(argc > 2) {lKey = argv[2];}
    GCppUi* lCpp = GCppUi::Create(lKey);
    lCpp->run(argc, argv);
}
//===============================================
