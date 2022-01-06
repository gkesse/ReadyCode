//===============================================
#include "GProcess.h"
#include "GQtStudio.h"
#include "GQtSpreadWindow.h"
#include "GSocket.h"
#include "GSQLite.h"
#include "GThread.h"
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
    else if(lKey == "sqlite") {
        runSQLite(_argc, _argv);
    }
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

    if(_argc > 1) {
        lType = _argv[1];
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
        GThread lThread;
        GSocket lServer;
        lThread.createThread(onServerTcp, &lServer);

        while(1) {
            std::queue<std::string>& lDataIn = lServer.getDataIn();
            std::queue<GSocket*>& lClientIn = lServer.getClientIn();

            if(!lDataIn.empty()) {
                std::string lData = lDataIn.front();
                GSocket* lClient = lClientIn.front();

                lDataIn.pop();
                lClientIn.pop();

                printf("ooooo : %s\n", lData.c_str());

                lClient->resultOk("hellooooooooooo");
            }
        }
    }
}
//===============================================
void GProcess::runSQLite(int _argc, char** _argv) {
    std::string lData = GSQLITE->readData(""
            "select 'Bonjour tout le monde'"
            "");
    printf("%s\n", lData.c_str());
}
//===============================================
DWORD WINAPI GProcess::onServerTcp(LPVOID _params) {
    GSocket* lServer = (GSocket*)_params;
    lServer->startServerTcp();
    return 0;
}
//===============================================
