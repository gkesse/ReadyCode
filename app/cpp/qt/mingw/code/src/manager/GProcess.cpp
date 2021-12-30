//===============================================
#include "GProcess.h"
#include "GQtUi.h"
#include "GSocketUi.h"
#include "GSQLiteUi.h"
#include "GFileUi.h"
#include "GQtStudio.h"
#include "GXml.h"
//===============================================
GProcess* GProcess::m_instance = 0;
//===============================================
GProcess::GProcess() : GObject() {
    createDom();
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
    std::string lKey = getName();
    if(lKey == "qt") {runQt(_argc, _argv);}
    else if(lKey == "socket") {runSocket(_argc, _argv);}
    else if(lKey == "sqlite") {runSQLite(_argc, _argv);}
    else if(lKey == "file") {runFile(_argc, _argv);}
    else if(lKey == "studio") {runStudio(_argc, _argv);}
}
//===============================================
void GProcess::createDom() {
    m_dom.reset(new GXml);
    m_dom->loadXmlFile(GRES("cpp/xml", "process.xml"));
    m_dom->createXPath();
}
//===============================================
std::string GProcess::getName() const {
    m_dom->queryXPath("/rdv/process/name");
    m_dom->getNodeXPath();
    std::string lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
void GProcess::runQt(int _argc, char** _argv) {
    QString lKey = "default";
    if(_argc > 2) {lKey = _argv[2];}
    GQtUi* lProcess = GQtUi::Create(lKey);
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
void GProcess::runStudio(int _argc, char** _argv) {
    QApplication app(_argc, _argv);
    GQtStudio* lWindow = new GQtStudio;
    lWindow->show();
    app.exec();
}
//===============================================
