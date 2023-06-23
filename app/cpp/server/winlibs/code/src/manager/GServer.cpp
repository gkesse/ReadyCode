//===============================================
#include "GServer.h"
#include "GSocket.h"
#include "GCalculator.h"
//===============================================
GServer::GServer()
: GManager() {

}
//===============================================
GServer::~GServer() {

}
//===============================================
void GServer::sendResponse(GSocket* _socket) {
    m_resp.loadData(m_logs.serialize());
    _socket->sendData(m_resp.toString());
}
//===============================================
void GServer::run(const GString& _data) {
    deserialize(_data);
    if(m_facade == "") {
        m_logs.addError("La facade est obligatoire.");
    }
    else if(m_facade == "server_c") {
        runFacade(_data);
    }
    else if(m_facade == "server_cpp") {
        runMaster(_data);
    }
    else if(m_facade == "server_python") {
        runFacade(_data);
    }
    else {
        m_logs.addError("La facade est inconnue.");
    }
}
//===============================================
void GServer::runFacade(const GString& _data) {
    GSocket lClient;
    GString lData = lClient.callServer(_data, m_facade);
    m_logs.addLogs(lClient.getLogs());
    m_resp.loadData(lData);
}
//===============================================
void GServer::runMaster(const GString& _data) {
    if(m_module == "") {
        m_logs.addError("Le module est obligatoire.");
    }
    else if(m_module == "calculator") {
        runCalculator(_data);
    }
    else {
        m_logs.addError("Le module est inconnu.");
    }
}
//===============================================
void GServer::runCalculator(const GString& _data) {
    GCalculator lObj;
    lObj.run(_data);
    m_logs.addLogs(lObj.getLogs());
    m_resp.loadData(lObj.serialize());
}
//===============================================
