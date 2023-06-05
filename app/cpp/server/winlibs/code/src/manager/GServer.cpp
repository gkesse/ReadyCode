//===============================================
#include "GServer.h"
#include "GSocket.h"
//===============================================
GServer::GServer()
: GManager() {

}
//===============================================
GServer::~GServer() {

}
//===============================================
void GServer::run(const GString& _data) {
    deserialize(_data);
    if(m_module == "") {
        m_logs.addError("Le module est obligatoire.");
    }
    else if(m_module == "logs") {
        m_logs.addData("Le module a été trouvé.");
    }
    else {
        m_logs.addError("Le module est inconnu.");
    }
}
//===============================================
void GServer::sendResponse(GSocket* _socket) {
    m_resp.loadData(m_logs.serialize());
    _socket->sendData(m_resp.toString());
}
//===============================================
