//===============================================
#include "GQuery.h"
#include "GMySQL.h"
#include "GSocket.h"
#include "GCode.h"
//===============================================
GQuery::GQuery()
: GSearch() {

}
//===============================================
GQuery::~GQuery() {

}
//===============================================
GObject* GQuery::clone() const {
    return new GQuery;
}
//===============================================
GString GQuery::serialize(const GString& _code)  {
    GCode lDom;
    lDom.createDoc();
    lDom.addData(_code, "emission", m_emission, true);
    lDom.addData(_code, "reception", m_reception, true);
    lDom.addData(GSearch::serialize());
    return lDom.toString();
}
//===============================================
void GQuery::deserialize(const GString& _data, const GString& _code) {
    GSearch::deserialize(_data);
    GCode lDom;
    lDom.loadXml(_data);
    m_emission = lDom.getData(_code, "emission").fromBase64();
    m_reception = lDom.getData(_code, "reception").fromBase64();
}
//===============================================
bool GQuery::onModule() {
    deserialize(m_server->getRequest());
    if(m_methodName == "") {
        m_logs.addError("Erreur la méthode est obligatoire.");
    }
    else if(m_methodName == "send_query") {
        onSendQuery();
    }
    else {
        m_logs.addError("Erreur la méthode est inconnue.");
    }
    m_server->addResponse(serialize());
    return true;
}
//===============================================
bool GQuery::onSendQuery() {
    if(m_emission == "") {GERROR_ADD(eGERR, "La requête est obligatoire."); return false;}
    GSocket* lServer = m_server->createSocket();
    lServer->setRequest(m_emission);
    GManager lManager;
    lManager.setServer(lServer);
    lManager.onManager();
    lServer->createResponse();
    m_reception = lServer->toResponse();
    m_emission = m_emission.toBase64();
    m_reception = m_reception.toBase64();
    delete lServer;
    return true;
}
//===============================================
