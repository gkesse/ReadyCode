//===============================================
#include "GProcess.h"
#include "GQtStudio.h"
#include "GQtPlan.h"
#include "GQtSpreadWindow.h"
#include "GQtOpenCVUi.h"
#include "GOpenCV.h"
#include "GChat.h"
#include "GSocket.h"
#include "GMaster.h"
#include "GTimer.h"
#include "GThread.h"
#include "GSQLite.h"
#include "GConsole.h"
#include "GString.h"
#include "GXml.h"
#include "GLog.h"
//===============================================
GProcess* GProcess::m_instance = 0;
GProcess* GProcess::m_process = 0;
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

    if(lKey == "test") {
        runTest(_argc, _argv);
    }
    else if(lKey == "studio") {
        runStudio(_argc, _argv);
    }
    else if(lKey == "plan") {
        runPlan(_argc, _argv);
    }
    else if(lKey == "spreadsheet") {
        runSpreadsheet(_argc, _argv);
    }
    // socket
    else if(lKey == "socket/server") {
        runSocketServer(_argc, _argv);
    }
    else if(lKey == "socket/client") {
        runSocketClient(_argc, _argv);
    }
    else if(lKey == "socket/server/test") {
        runSocketServerTest(_argc, _argv);
    }
    else if(lKey == "socket/client/test") {
        runSocketClientTest(_argc, _argv);
    }
    //
    else if(lKey == "master") {
        runMaster(_argc, _argv);
    }
    else if(lKey == "sqlite") {
        runSQLite(_argc, _argv);
    }
    else if(lKey == "timer") {
        runTimer(_argc, _argv);
    }
    //
    else if(lKey == "opencv") {
        runOpenCV(_argc, _argv);
    }
    else if(lKey == "opencv/ui") {
        runOpenCVUi(_argc, _argv);
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
void GProcess::runTest(int _argc, char** _argv) {
    GXml lDom;
    lDom.createDoc("1.0");
    lDom.createRoot("rdv");
    lDom.createXPath();
    lDom.createNodePath("/rdv/request/data/map/data");
    lDom.createNodePath("/rdv/request/data/map/data");
    std::cout << lDom.toString() << "\n";
}
//===============================================
void GProcess::runTestPoll(int _argc, char** _argv) {
    GXml lDom;
    lDom.createDoc("1.0");
    lDom.createRoot("rdv");
    lDom.createXPath();
    lDom.createNodePath("/rdv/request/data/map/data");
    lDom.createNodePath("/rdv/request/data/map/data");
    std::cout << lDom.toString() << "\n";
}
//===============================================
void GProcess::runStudio(int _argc, char** _argv) {
    QApplication lApp(_argc, _argv);
    GQtStudio* lWindow = new GQtStudio;
    lWindow->show();
    lApp.exec();
}
//===============================================
void GProcess::runPlan(int _argc, char** _argv) {
    QApplication lApp(_argc, _argv);
    GQtPlan* lWindow = new GQtPlan;
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
void GProcess::runSocketServer(int _argc, char** _argv) {
    GThread lThread;
    GTimer lTimer;

    m_process = new GProcess;
    m_process->m_server = new GSocket;
    m_process->m_server->setResponseLoop(true);

    lThread.createThread(onSocketServer, m_process);
    lTimer.setTimer(onSocketServerTimer, 50);
    lTimer.setTimer(onSocketServerLoopWR, 50);
    lTimer.pauseTimer();
}
//===============================================
void GProcess::runSocketClient(int _argc, char** _argv) {
    if(_argc < 3) {
        GERROR_ADD->addError(sformat("Erreur la methode (runSocketClient) a echoue "
                "sur le nombre d'arguments (%d).", _argc));
        return;
    }

    std::string lId = _argv[2];
    std::string lPseudo = _argv[3];

    m_process = new GProcess;

    m_process->m_console = new GConsole;
    m_process->m_console->setPseudo(lPseudo);
    m_process->m_console->setPseudoId(lId);
    m_process->m_console->runConsole();

    GChat lChat;
    lChat.setId(lId);
    lChat.setPseudo(lPseudo);
    lChat.createConnection();

    std::string lDataOut;

    m_process->m_client = new GSocket;
    m_process->m_client->startClientTcp();
    m_process->m_client->addDataIn(lChat);

    m_process->m_timer = new GTimer;
    m_process->m_timer->setTimer(onSocketClientConsole, 50);
    m_process->m_timer->setTimer(onSocketClientLoopWR, 50);
    m_process->m_timer->setTimer(onSocketClientDispatcher, 50);
    m_process->m_timer->pauseTimer();
}
//===============================================
void GProcess::runSocketServerTest(int _argc, char** _argv) {
    GSocket lServer;

    lServer.initSocket(lServer.getMajor(), lServer.getMinor());
    lServer.createSocketTcp();
    lServer.createAddress(lServer.getAddressClient(), lServer.getPort());
    lServer.bindSocket();
    lServer.listenSocket(lServer.getBacklog());

    printf("Demarrage su derveur...\n");

    GSocket lClient;
    lServer.acceptSocket(lClient);

    printf("adresse ip client : %s\n", lClient.loadAddressIp().c_str());

    std::string lData;

    for(int i = 0; i < 4; i++) {
        lClient.recvData(lData);
        printf("----->\n%s\n", lData.c_str());
    }

    lClient.sendData("Server : Bienvenue !!!");

    lClient.closeSocket();
    lServer.closeSocket();
    lServer.cleanSocket();
}
//===============================================
void GProcess::runSocketClientTest(int _argc, char** _argv) {
    GSocket lClient;

    lClient.initSocket(lClient.getMajor(), lClient.getMinor());
    lClient.createSocketTcp();
    lClient.createAddress(lClient.getAddressServer(), lClient.getPort());
    lClient.connectSocket();

    std::string lData;

    for(int i = 0; i < 4; i++) {
        lClient.sendData("Client : Bonjour tout le monde");
    }

    lClient.recvData(lData);
    printf("----->\n%s\n", lData.c_str());


    lClient.cleanSocket();
    lClient.cleanSocket();
}
//===============================================
void GProcess::runMaster(int _argc, char** _argv) {
    GMaster lMaster;
    lMaster.run(_argc, _argv);
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
    GTimer lTimer;
    lTimer.setTimer(onTimer, 1000);
    lTimer.pauseTimer();
}
//===============================================
void GProcess::runOpenCV(int _argc, char** _argv) {
    GOpenCV lOpenCV;
    lOpenCV.run(_argc, _argv);
}
//===============================================
void GProcess::runOpenCVUi(int _argc, char** _argv) {
    QApplication lApp(_argc, _argv);
    GQtOpenCVUi* lWindow = new GQtOpenCVUi;
    lWindow->show();
    lApp.exec();
}
//===============================================
DWORD WINAPI GProcess::onSocketServer(LPVOID _params) {
    GProcess* lProcess = (GProcess*)_params;
    GSocket* lServer = lProcess->m_server;
    lServer->setOnServerTcp(onSocketServerThread);
    lServer->startServerTcp();
    delete lServer;
    return 0;
}
//===============================================
DWORD WINAPI GProcess::onSocketServerThread(LPVOID _params) {
    GSocket* lClient = (GSocket*)_params;
    GSocket* lServer = lClient->getServer();
    std::queue<std::string>& lDataIn = lServer->getDataIn();
    std::queue<GSocket*>& lClientIn = lServer->getClientIn();
    std::string lData;

    lClient->setResponseLoop(lServer->hasResponseLoop());

    if(lServer->hasResponseLoop()) {
        while(1) {
            lClient->readData(lData);
            if(lData == "") {
                lClient->removeClient();
                lClient->closeSocket();
                delete lClient;
                break;
            }
            lDataIn.push(lData);
            lClientIn.push(lClient);
        }
    }
    else {
        lClient->readData(lData);
        lDataIn.push(lData);
        lClientIn.push(lClient);
    }
    return 0;
}
//===============================================
void CALLBACK GProcess::onSocketServerLoopWR(HWND hwnd, UINT uMsg, UINT_PTR timerId, DWORD dwTime) {
    GSocket* lServer = m_process->m_server;
    std::queue<std::string>& lDataAns = lServer->getDataAns();
    std::queue<GSocket*>& lClientAns = lServer->getClientAns();

    if(!lDataAns.empty()) {
        std::string lData = lDataAns.front();
        GSocket* lClient = lClientAns.front();

        lDataAns.pop();
        lClientAns.pop();

        if(lClient->hasBroadcast()) {
            std::map<std::string, GSocket*>& lClientMap = lServer->getClientMap();
            std::map<std::string, GSocket*>::iterator it;

            for (it = lClientMap.begin(); it != lClientMap.end(); it++) {
                GSocket* iClient = it->second;
                if(lClient->hasBroadcastExclusive()) {
                    if(iClient == lClient) continue;
                }
                iClient->writeData(lData);
            }
            lClient->setBroadcast(false);
        }
        else {
            lClient->writeData(lData);
        }
    }
}
//===============================================
void CALLBACK GProcess::onSocketServerTimer(HWND hwnd, UINT uMsg, UINT_PTR timerId, DWORD dwTime) {
    GSocket* lServer = m_process->m_server;
    std::queue<std::string>& lDataIn = lServer->getDataIn();
    std::queue<GSocket*>& lClientIn = lServer->getClientIn();

    if(!lDataIn.empty()) {
        std::string lRequest = lDataIn.front();
        GSocket* lClient = lClientIn.front();

        lDataIn.pop();
        lClientIn.pop();

        lServer->showMessage(lRequest);

        GObject lDom;
        lDom.loadDom(lRequest);
        std::string lModule = lDom.getModule();
        std::string lMethod = lDom.getMethod();

        lClient->setReq(lRequest);

        if(lModule == "chat") {
            onModuleChat(lClient);
        }
        else {
            onUnknownModule(lRequest, lClient);
        }

        GObject lResultOk;
        lResultOk.initResult();
        lResultOk.addResultMsg(GOBJECT->sformat("%s/%s (OK).", lModule.c_str(), lMethod.c_str()));
        lClient->addResultOk(lResultOk);

        lClient->sendResponse();

        if(!lClient->hasResponseLoop()) {
            lClient->closeSocket();
            delete lClient;
        }
    }
}
//===============================================
void CALLBACK GProcess::onSocketClientConsole(HWND hwnd, UINT uMsg, UINT_PTR timerId, DWORD dwTime) {
    GConsole* lConsole = m_process->m_console;
    GSocket* lClient = m_process->m_client;
    GTimer* lTimer = m_process->m_timer;
    std::queue<std::string>& lDataIn = lConsole->getDataIn();
    bool& lReadyOn = lConsole->getReadyOn();

    if(!lDataIn.empty()) {
        std::string lData = lDataIn.front();
        lDataIn.pop();

        lData = GString(lData).trimData();

        if(lData == "exit" || lData == "quit") {
            lConsole->stopConsole();
            lTimer->stopTimer();
            delete lConsole;
            delete lTimer;
            delete m_process;
            return;
        }

        GChat lChat;
        lChat.setId(lConsole->getPseudoId());
        lChat.setPseudo(lConsole->getPseudo());
        lChat.createMessage();
        lChat.addMessage(lData);
        lClient->addDataIn(lChat);

        printf("---> (cpu)\n%s\n", lData.c_str());
        printf("===> (%s)\n> ", lConsole->getPseudo().c_str());
    }

    lReadyOn = true;
}
//===============================================
void CALLBACK GProcess::onSocketClientLoopWR(HWND hwnd, UINT uMsg, UINT_PTR timerId, DWORD dwTime) {
    GSocket* lClient = m_process->m_client;
    std::queue<std::string>& lDataIn = lClient->getDataIn();

    if(!lDataIn.empty()) {
        std::string lData = lDataIn.front();

        lDataIn.pop();

        lClient->writeData(lData);
    }
}
//===============================================
void CALLBACK GProcess::onSocketClientDispatcher(HWND hwnd, UINT uMsg, UINT_PTR timerId, DWORD dwTime) {
    GSocket* lClient = m_process->m_client;
    GConsole* lConsole = m_process->m_console;
    std::queue<std::string>& lDataAns = lClient->getDataAns();
    bool& lReadyOn = lConsole->getReadyOn();

    if(!lDataAns.empty()) {
        std::string lData = lDataAns.front();

        lDataAns.pop();

        printf("---> (cpu)\n%s\n", lData.c_str());
        printf("===> (%s)\n> ", lConsole->getPseudo().c_str());
    }

    lReadyOn = true;
}
//===============================================
void CALLBACK GProcess::onTimer(HWND hwnd, UINT uMsg, UINT_PTR timerId, DWORD dwTime) {
    printf("onTimer... %lu (ms)\n", dwTime);
}
//===============================================
void GProcess::onModuleChat(GSocket* _client) {
    GChat lChat;
    lChat.onModule(_client);
}
//===============================================
