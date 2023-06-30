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
bool GServer::isValid(const GString& _data) {
    if(_data.isEmpty()) {
        m_srvLogs.addError("La requête est vide.");
        return false;
    }
    GCode lDom;
    if(!lDom.loadXml(_data)) {
        m_srvLogs.addError("La requête n'est pas un XML valide.");
        return false;
    }
    if(!lDom.hasDatas()) {
        m_srvLogs.addError("La requête n'est pas dans un format XML valide.");
        return false;
    }
    return true;
}
//===============================================
void GServer::sendResponse(GSocket* _socket) {
    m_srvLogs.addLogs(_socket->getSrvLogs());
    if(!m_srvLogs.hasErrors()) {
        m_resp.loadData(m_logs.serialize());
        _socket->sendData(m_resp.toString());
    }
    else {
        _socket->sendData("La connexion au serveur a échoué.");
    }
}
//===============================================
void GServer::run(const GString& _data) {
    if(!isValid(_data)) return;
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
