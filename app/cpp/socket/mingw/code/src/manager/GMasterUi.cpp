//===============================================
#include "GMasterUi.h"
#include "GStruct.h"
#include "GManager.h"
#include "GConsole.h"
#include "GThread.h"
#include "GSignal.h"
//===============================================
sGMaster GMasterUi::m_params;
//===============================================
GMasterUi::GMasterUi() {

}
//===============================================
GMasterUi::~GMasterUi() {

}
//===============================================
GMasterUi* GMasterUi::Create(const std::string& key) {
    if(key == "default") {return new GMasterUi;}
    return new GMasterUi;
}
//===============================================
void GMasterUi::run(int _argc, char** _argv) {
    GThread lServer; GSignal lSignal;
    lServer.createThread(onServer, 0);
    lSignal.setSignal(SIGINT, onSignal);

    while(m_params.run) {
        onMessage(m_params.data_in);
    }
}
//===============================================
DWORD WINAPI GMasterUi::onServer(LPVOID _params) {
    GManager lMgr;
    sGSocket lSocket;
    lSocket.on_start = (void*)onStart;
    lMgr.startServer(lSocket);
    return 0;
}
//===============================================
DWORD WINAPI GMasterUi::onStart(LPVOID _params) {
    GManager lMgr;
    lMgr.onStartServer(_params, m_params.data_in);
    return 0;
}
//===============================================
void GMasterUi::onSignal(int _signal) {
    GConsole lConsole;
    m_params.run = false;
    exit(_signal);
}
//===============================================
void GMasterUi::onMessage(std::queue<std::string>& _dataIn) {
    if(_dataIn.empty()) return;
    GManager lMgr; std::string lModule, lMethod; GConsole lConsole;
    std::string lDataIn = _dataIn.front();
    lMgr.getModule(lDataIn, lModule);
    lMgr.getMethod(lDataIn, lMethod);

    lConsole.showData(_dataIn.size());

    _dataIn.pop();
}
//===============================================
