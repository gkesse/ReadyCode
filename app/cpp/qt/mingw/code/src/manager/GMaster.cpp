//===============================================
#include "GMaster.h"
#include "GSocket.h"
#include "GThread.h"
#include "GTimer.h"
#include "GXml.h"
#include "GOpenCV.h"
#include "GRequest.h"
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
void GMaster::insertXmlMessage(const std::string& _request) const {
    GObject lRequest;
    lRequest.loadDom(_request);
    std::string lRequestName = lRequest.getRequestName();
    std::string lMessage = lRequest.toString();
    //
    incMessageId();
    int lMessageId = getMessageId();
    //
    m_domData->queryXPath("/rdv/datas/data[code='master/xml/messages']/map");
    m_domData->getNodeXPath();
    GXml lNode;
    lNode.createNode("data");
    lNode.appendNode("id", std::to_string(lMessageId));
    lNode.appendNode("name", lRequestName);
    lNode.appendCData("msg", lMessage);
    m_domData->appendNode(lNode);
    m_domData->saveXmlFile();
}
//===============================================
void GMaster::updateXmlMessage(const std::string& _request) const {
    GObject lRequest;
    lRequest.loadDom(_request);
    std::string lRequestName = lRequest.getRequestName();
    std::string lMessage = lRequest.toString();
    //
    m_domData->queryXPath(sformat("/rdv/datas/data[code='master/xml/messages']/map/data[name='%s']/msg", lRequestName.c_str()));
    m_domData->getNodeXPath();
    m_domData->setNodeCData(lMessage);
    m_domData->saveXmlFile();
}
//===============================================
int GMaster::countXmlMessage(const std::string& _request) const {
    GObject lRequest;
    lRequest.loadDom(_request);
    std::string lRequestName = lRequest.getRequestName();
    //
    m_domData->queryXPath(sformat("/rdv/datas/data[code='master/xml/messages']/map/data[name='%s']", lRequestName.c_str()));
    int lData = m_domData->countXPath();
    return lData;
}
//===============================================
void GMaster::clearXmlMessage() const {
    m_domData->queryXPath("/rdv/datas/data[code='master/xml/messages']/map/data");
    m_domData->getNodeXPath();
    m_domData->clearNodeXPath();
    m_domData->saveXmlFile();
}
//===============================================
void GMaster::loadXmlMessageModule(GSocket* _client) const {
    m_domData->queryXPath("/rdv/datas/data[code='master/xml/messages']/map/data");
    m_domData->getNodeXPath();
    GRequest lDom;
    lDom.createRequest();
    lDom.addRequest(m_domData->getNodeString());
    _client->addDataOut(lDom.toString());
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
void GMaster::incMessageId() const {
    int lMessageId = getMessageId();
    lMessageId++;
    saveMessageId(lMessageId);
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
        std::string lRequestIn = m_dataIn.front();
        GSocket* lClient = m_clientIn.front();

        m_dataIn.pop();
        m_clientIn.pop();

        m_server->showMessage(lRequestIn);

        GObject lRequest;
        lRequest.loadDom(lRequestIn);
        std::string lModule = lRequest.getModule();

        if(lModule == "master") {
            onModuleMaster(lRequestIn, lClient);
        }
        else if(lModule == "opencv") {
            onModuleOpenCV(lRequestIn, lClient);
        }
        else {
            onUnknownModule(lRequestIn, lClient);
        }

        onSaveXmlMessages(lRequestIn, lClient);

        GObject lResultOk;
        lResultOk.createResult();
        lResultOk.addResultMsg("ok");
        lClient->addResultOk(lResultOk);

        lClient->sendResponse();

        delete lClient;
    }
}
//===============================================
void GMaster::onModuleMaster(const std::string& _request, GSocket* _client) {
    GObject lRequest;
    lRequest.loadDom(_request);
    std::string lMethod = lRequest.getMethod();

    if(lMethod == "stop_server") {
        onStopServer(_request, _client);
    }
    else if(lMethod == "clear_xml_messages") {
        onClearXmlMessages(_request, _client);
    }
    else if(lMethod == "load_xml_messages") {
        onLoadXmlMessages(_request, _client);
    }
    else {
        onUnknownMethod(_request, _client);
    }
}
//===============================================
void GMaster::onStopServer(const std::string& _request, GSocket* _client) {
    m_server->stopServer();
    m_timer->stopTimer();
}
//===============================================
void GMaster::onSaveXmlMessages(const std::string& _request, GSocket* _client) {
    GMaster lDom;
    if(!lDom.countXmlMessage(_request)) {
        lDom.insertXmlMessage(_request);
    }
    else {
        lDom.updateXmlMessage(_request);
    }
}
//===============================================
void GMaster::onClearXmlMessages(const std::string& _request, GSocket* _client) {
    GMaster lDom;
    lDom.clearXmlMessage();
}
//===============================================
void GMaster::onLoadXmlMessages(const std::string& _request, GSocket* _client) {
    GMaster lDom;
    lDom.loadXmlMessageModule(_client);
}
//===============================================
void GMaster::onModuleOpenCV(const std::string& _request, GSocket* _client) {
    GOpenCV lOpenCV;
    lOpenCV.onModule(_request, _client);
}
//===============================================
