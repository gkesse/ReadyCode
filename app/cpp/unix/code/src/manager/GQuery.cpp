//===============================================
#include "GQuery.h"
#include "GMySQL.h"
#include "GSocket.h"
#include "GCode.h"
//===============================================
GQuery::GQuery(const GString& _code)
: GSearch(_code) {

}
//===============================================
GQuery::~GQuery() {

}
//===============================================
GObject* GQuery::clone() const {
    return new GQuery;
}
//===============================================
GString GQuery::serialize(const GString& _code) const {
    GCode lDom;
    lDom.createDoc();
    lDom.addData(_code, "emission", m_emission, true);
    lDom.addData(_code, "reception", m_reception, true);
    lDom.addData(GSearch::serialize());
    return lDom.toString();
}
//===============================================
bool GQuery::deserialize(const GString& _data, const GString& _code) {
    GSearch::deserialize(_data);
    GCode lDom;
    lDom.loadXml(_data);
    m_emission = lDom.getData(_code, "emission").fromBase64();
    m_reception = lDom.getData(_code, "reception").fromBase64();
    return true;
}
//===============================================
bool GQuery::onModule() {
    deserialize(m_server->getRequest());
    if(m_methodName == "") {
        GMETHOD_REQUIRED();
    }
    else if(m_methodName == "send_query") {
        onSendQuery();
    }
    else {
        GMETHOD_UNKNOWN();
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
    m_reception = lServer->getResponse();
    m_emission = m_emission.toBase64();
    m_reception = m_reception.toBase64();
    delete lServer;
    return true;
}
//===============================================
