//===============================================
#include "GMaster.h"
#include "GSocket.h"
#include "GThread.h"
#include "GTimer.h"
#include "GXml.h"
#include "GOpenCV.h"
//===============================================
GMaster* GMaster::m_instance = 0;
//===============================================
GSocket* GMaster::m_server = 0;
GTimer* GMaster::m_timer = 0;
//===============================================
std::queue<std::string> GMaster::m_dataIn;
std::queue<GSocket*> GMaster::m_clientIn;
//===============================================
GMaster::GMaster() : GObject() {
    createDoms();
}
//===============================================
GMaster::~GMaster() {

}
//===============================================
GMaster* GMaster::Instance() {
    if(m_instance == 0) {
        m_instance = new GMaster;
    }
    return m_instance;
}
//===============================================
void GMaster::createDoms() {
    m_dom.reset(new GXml);
    m_dom->loadXmlFile(GRES("cpp/xml", "master.xml"));
    m_dom->createXPath();
    m_domData.reset(new GXml);
    m_domData->loadXmlFile(GRES("cpp/xml", "master_data.xml"));
    m_domData->createXPath();
}
//===============================================
int GMaster::getTimer() const {
    m_dom->queryXPath("/rdv/master/timer");
    m_dom->getNodeXPath();
    std::string lData = m_dom->getNodeValue();
    return std::stoi(lData);
}
//===============================================
void GMaster::saveXmlMessage(GObject* _request) {
    std::string lRequestName = _request->getRequestName();
    std::string lMessage = _request->toString();
    int lMessageId = getMessageId();
    m_domData->queryXPath("/rdv/datas/data[code='master/xml/messages']/map");
    m_domData->getNodeXPath();
    GXml lNode;
    lNode.createNode("data");
    lNode.appendNode("id", std::to_string(lMessageId));
    lNode.appendNode("name", lRequestName);
    lNode.appendCData("msg", lMessage);
    m_domData->appendNode(lNode);
    m_domData->saveXmlFile();
    saveMessageId(++lMessageId);
}
//===============================================
int GMaster::getMessageId() const {
    m_domData->queryXPath("/rdv/datas/data[code='master/xml/messages']/id");
    m_domData->getNodeXPath();
    std::string lData = m_domData->getNodeValue();
    return std::stoi(lData);
}
//===============================================
void GMaster::saveMessageId(int _id) const {
    m_domData->queryXPath("/rdv/datas/data[code='master/xml/messages']/id");
    m_domData->getNodeXPath();
    m_domData->setNodeValue(std::to_string(_id));
    m_domData->saveXmlFile();
}
//===============================================
void GMaster::run(int _argc, char** _argv) {
    GThread lThread;
    m_server = new GSocket;
    m_timer = new GTimer;
    lThread.createThread(onThread, m_server);
    m_timer->setTimer(onTimer, getTimer());
    m_timer->pauseTimer();
}
//===============================================
DWORD WINAPI GMaster::onThread(LPVOID _params) {
    GSocket* lServer = (GSocket*)_params;
    lServer->setOnServerTcp(onServerTcp);
    lServer->startServerTcp();
    delete lServer;
    return 0;
}
//===============================================
DWORD WINAPI GMaster::onServerTcp(LPVOID _params) {
    GSocket* lClient = (GSocket*)_params;
    std::string lDataIn;

    lClient->readData(lDataIn);
    lClient->shutdownRD();

    m_dataIn.push(lDataIn);
    m_clientIn.push(lClient);

    return 0;
}
//===============================================
void CALLBACK GMaster::onTimer(HWND hwnd, UINT uMsg, UINT_PTR timerId, DWORD dwTime) {
    if(!m_dataIn.empty()) {
        std::string lData = m_dataIn.front();
        GSocket* lClient = m_clientIn.front();

        m_dataIn.pop();
        m_clientIn.pop();

        m_server->showMessage(lData);

        m_requestDom.reset(new GObject);
        m_requestDom->loadDom(lData);
        std::string lModule = m_requestDom->getModule();

        bool lMethodExist = true;

        if(lModule == "server") {
            onModuleServer(m_requestDom.get(), lClient);
        }
        else if(lModule == "opencv") {
            onModuleOpenCV(m_requestDom.get(), lClient);
        }
        else {
            onUnknownModule(m_requestDom.get(), lClient);
            lMethodExist = false;
        }

        if(lMethodExist) {
            GMaster lMaster;
            lMaster.saveXmlMessage(m_requestDom.get());
        }

        m_resultOkDom.reset(new GObject);
        m_resultOkDom->createResult();
        m_resultOkDom->addResultMsg("ok");
        lClient->addResultOk(m_resultOkDom);

        lClient->sendResponse();

        delete lClient;
    }
}
//===============================================
void GMaster::onModuleServer(GObject* _request, GSocket* _client) {
    std::string lMethod = _request->getMethod();

    if(lMethod == "stop_server") {
        onStopServer(_request, _client);
    }
}
//===============================================
void GMaster::onStopServer(GObject* _request, GSocket* _client) {
    m_server->stopServer();
    m_timer->stopTimer();
}
//===============================================
void GMaster::onModuleOpenCV(GObject* _request, GSocket* _client) {
    GOPENCV->onModule(_request, _client);
}
//===============================================
