//===============================================
#include "GServer.h"
#include "GSocket.h"
#include "GCalculator.h"
//===============================================
GServer::GServer()
: GManager() {
    m_isHttp = false;
}
//===============================================
GServer::~GServer() {

}
//===============================================
bool GServer::isValid(GString& _data) {
    if(_data.isEmpty()) {
        m_dataLogs.addError("La requête est vide.");
        return false;
    }

    isHttp(_data);

    GCode lDom;
    if(!lDom.loadXml(_data)) {
        m_dataLogs.addError("La requête n'est pas un XML valide.");
        return false;
    }
    if(!lDom.hasDatas()) {
        m_dataLogs.addError("La requête n'est pas dans un format XML valide.");
        return false;
    }
    return true;
}
//===============================================
bool GServer::isHttp(GString& _data) {
    httpparser::Request lRequest;
    httpparser::HttpRequestParser lParser;
    httpparser::HttpRequestParser::ParseResult lResult = lParser.parse(lRequest, _data.c_str(), _data.c_str() + _data.size());
    if(lResult != httpparser::HttpRequestParser::ParsingCompleted) return false;
    _data = lRequest.content;
    m_isHttp = true;
    return true;
}
//===============================================
GString GServer::toHttp(const GString& _data, const GHttp::eGStatus& _status) {
    if(!m_isHttp) return _data;
    GHttp lHttp;
    lHttp.setStatus(_status);
    lHttp.setData(_data);
    GString lData = lHttp.toResponse();
    return lData;
}
//===============================================
void GServer::sendResponse(GSocket* _socket) {
    m_dataLogs.addLogs(_socket->getDataLogs());
    if(!m_dataLogs.hasErrors()) {
        m_resp.loadData(m_logs.serialize());
        GString lData = m_resp.toString();
        lData = toHttp(lData, GHttp::eGStatus::Ok);
        _socket->sendData(lData);
    }
    else {
        GString lData = "La connexion au serveur a échoué.";
        lData = toHttp(lData, GHttp::eGStatus::BadRequest);
        _socket->sendData(lData);
    }
}
//===============================================
void GServer::run(GString& _data) {
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
    else if(m_facade == "server_java") {
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
