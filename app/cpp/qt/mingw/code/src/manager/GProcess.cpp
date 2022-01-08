//===============================================
#include "GProcess.h"
#include "GQtStudio.h"
#include "GQtSpreadWindow.h"
#include "GSocket.h"
#include "GMaster.h"
#include "GSQLite.h"
#include "GTimer.h"
#include "GOpenCV.h"
#include "GQtOpenCVUi.h"
#include "GThread.h"
#include "GXml.h"
//===============================================
GProcess* GProcess::m_instance = 0;
//===============================================
GProcess::GProcess() : GObject() {
    createDoms();
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
    std::string lKey = getName(_argc, _argv);
    bool lProcShow = getProcShow();
    bool lArgShow = getArgShow();

    if(lProcShow) {
        printf("nom processus : %s\n", lKey.c_str());
    }
    if(lArgShow) {
        showArgs(_argc, _argv);
    }

    if(lKey == "studio") {
        runStudio(_argc, _argv);
    }
    else if(lKey == "spreadsheet") {
        runSpreadsheet(_argc, _argv);
    }
    else if(lKey == "socket") {
        runSocket(_argc, _argv);
    }
    else if(lKey == "master") {
        runMaster(_argc, _argv);
    }
    else if(lKey == "sqlite") {
        runSQLite(_argc, _argv);
    }
    else if(lKey == "timer") {
        runTimer(_argc, _argv);
    }
    else if(lKey == "opencv") {
        runOpenCV(_argc, _argv);
    }
}
//===============================================
void GProcess::createDoms() {
    m_dom.reset(new GXml);
    m_dom->loadXmlFile(GRES("cpp/xml", "process.xml"));
    m_dom->createXPath();
}
//===============================================
std::string GProcess::getName(int _argc, char** _argv) const {
    std::string lData = "";
    if(getNameUse()) {
        lData = getName();
    }
    else {
        if(_argc > 1) {
            lData = _argv[1];
        }
    }
    return lData;
}
//===============================================
std::string GProcess::getName() const {
    m_dom->queryXPath("/rdv/process/name");
    m_dom->getNodeXPath();
    std::string lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
bool GProcess::getNameUse() const {
    m_dom->queryXPath("/rdv/process/nameuse");
    m_dom->getNodeXPath();
    std::string lData = m_dom->getNodeValue();
    return (lData == "1");
}
//===============================================
bool GProcess::getProcShow() const {
    m_dom->queryXPath("/rdv/process/procshow");
    m_dom->getNodeXPath();
    bool lData = (m_dom->getNodeValue() == "1");
    return lData;
}
//===============================================
bool GProcess::getArgShow() const {
    m_dom->queryXPath("/rdv/process/argshow");
    m_dom->getNodeXPath();
    bool lData = (m_dom->getNodeValue() == "1");
    return lData;
}
//===============================================
void GProcess::runStudio(int _argc, char** _argv) {
    QApplication lApp(_argc, _argv);
    GQtStudio* lWindow = new GQtStudio;
    lWindow->show();
    lApp.exec();
}
//===============================================
void GProcess::runSpreadsheet(int _argc, char** _argv) {
    QApplication lApp(_argc, _argv);
    GQtSpreadWindow* lWindow = new GQtSpreadWindow;
    lWindow->show();
    lApp.exec();
}
//===============================================
void GProcess::runSocket(int _argc, char** _argv) {
    std::string lType = "";

    if(getNameUse()) {
        if(_argc > 1) {
            lType = _argv[1];
        }
    }
    else {
        if(_argc > 2) {
            lType = _argv[2];
        }
    }

    // client
    if(lType == "client") {
        GSocket lSocket;
        std::string lDataIn = "Bonjour tout le monde";
        std::string lDataOut;
        lSocket.callServerTcp(lDataIn, lDataOut);
        printf("%s\n", lDataOut.c_str());
    }
    // server
    else {
        GTHREAD->createThread(onServerTcp, GSOCKET);
        GTIMER->setTimer(onServerTcpTimer, 50);
        GTIMER->pause();
    }
}
//===============================================
void GProcess::runMaster(int _argc, char** _argv) {
    GMASTER->run(_argc, _argv);
}
//===============================================
void GProcess::runSQLite(int _argc, char** _argv) {
    std::string lData = GSQLITE->readData(""
            "select 'Bonjour tout le monde'"
            "");
    printf("%s\n", lData.c_str());
}
//===============================================
void GProcess::runTimer(int _argc, char** _argv) {
    GTIMER->setTimer(onTimer, 1000);
    GTIMER->pause();
}
//===============================================
void GProcess::runOpenCV(int _argc, char** _argv) {
    std::string lType = "";

    if(getNameUse()) {
        if(_argc > 1) {
            lType = _argv[1];
        }
    }
    else {
        if(_argc > 2) {
            lType = _argv[2];
        }
    }

    if(lType == "ui") {
        QApplication lApp(_argc, _argv);
        GQtOpenCVUi* lWindow = new GQtOpenCVUi;
        lWindow->show();
        lApp.exec();
    }
    else {
        GOPENCV->run(_argc, _argv);
    }
}
//===============================================
DWORD WINAPI GProcess::onServerTcp(LPVOID _params) {
    GSocket* lServer = (GSocket*)_params;
    lServer->startServerTcp();
    return 0;
}
//===============================================
void CALLBACK GProcess::onServerTcpTimer(HWND hwnd, UINT uMsg, UINT_PTR timerId, DWORD dwTime) {
    std::queue<std::string>& lDataIn = GSOCKET->getDataIn();
    std::queue<GSocket*>& lClientIn = GSOCKET->getClientIn();

    if(!lDataIn.empty()) {
        std::string lData = lDataIn.front();
        GSocket* lClient = lClientIn.front();

        lDataIn.pop();
        lClientIn.pop();

        printf("%s\n", lData.c_str());

        lClient->resultOk();
    }
}
//===============================================
void CALLBACK GProcess::onTimer(HWND hwnd, UINT uMsg, UINT_PTR timerId, DWORD dwTime) {
    printf("onTimer... %lu (ms)\n", dwTime);
}
//===============================================
