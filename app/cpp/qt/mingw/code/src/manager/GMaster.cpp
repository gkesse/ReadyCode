//===============================================
#include "GMaster.h"
#include "GSocket.h"
#include "GThread.h"
#include "GTimer.h"
#include "GXml.h"
//===============================================
GMaster* GMaster::m_instance = 0;
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
}
//===============================================
int GMaster::getTimer() const {
    m_dom->queryXPath("/rdv/master/timer");
    m_dom->getNodeXPath();
    std::string lData = m_dom->getNodeValue();
    return std::stoi(lData);
}
//===============================================
void GMaster::run(int _argc, char** _argv) {
    GTHREAD->createThread(onThread, GSOCKET);
    GTIMER->setTimer(onTimer, getTimer());
    GTIMER->pause();
}
//===============================================
DWORD WINAPI GMaster::onThread(LPVOID _params) {
    GSocket* lServer = (GSocket*)_params;
    lServer->startServerTcp();
    return 0;
}
//===============================================
void CALLBACK GMaster::onTimer(HWND hwnd, UINT uMsg, UINT_PTR timerId, DWORD dwTime) {
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
