//===============================================
#include "GProcess.h"
#include "GQtUi.h"
#include "GGslUi.h"
#include "GElectronicsUi.h"
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
    if(lKey == "qt") {runQt(argc, argv); return;}
    if(lKey == "gsl") {runGsl(argc, argv); return;}
    if(lKey == "electronics") {runElectronics(argc, argv); return;}
    runDefault(argc, argv);
}
//===============================================
void GProcess::runDefault(int argc, char** argv) {
    qDebug() << "[process] aucun process n'a ete selectionne.";
}
//===============================================
void GProcess::runQt(int argc, char** argv) {
    QString lKey = "default";
    if(argc > 2) {lKey = argv[2];}
    QApplication app(argc, argv);
    GQtUi* lWindow = GQtUi::Create(lKey);
    lWindow->setWindowTitle("ReadyApp");
    lWindow->resize();
    lWindow->show();
    app.exec();
}
//===============================================
void GProcess::runGsl(int argc, char** argv) {
    QString lKey = "default";
    if(argc > 2) {lKey = argv[2];}
    QApplication app(argc, argv);
    GGslUi* lWindow = GGslUi::Create(lKey);
    lWindow->setWindowTitle("ReadyApp");
    lWindow->resize();
    lWindow->show();
    app.exec();
}
//===============================================
void GProcess::runElectronics(int argc, char** argv) {
    QString lKey = "default";
    if(argc > 2) {lKey = argv[2];}
    QApplication app(argc, argv);
    GElectronicsUi* lWindow = GElectronicsUi::Create(lKey);
    lWindow->setWindowTitle("ReadyApp");
    lWindow->resize();
    lWindow->show();
    app.exec();
}
//===============================================
