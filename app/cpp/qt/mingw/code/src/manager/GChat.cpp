//===============================================
#include "GChat.h"
#include "GSocket.h"
#include "GXml.h"
//===============================================
GChat* GChat::m_instance = 0;
//===============================================
GChat::GChat() : GObject() {

}
//===============================================
GChat::~GChat() {

}
//===============================================
GChat* GChat::Instance() {
    if(m_instance == 0) {
        m_instance = new GChat;
    }
    return m_instance;
}
//===============================================
void GChat::createConnection() {
    initRequest("chat", "connect_client");
    m_dom->createNodePath("/rdv/client/id").setNodeValue(m_id);
    m_dom->createNodePath("/rdv/client/pseudo").setNodeValue(m_pseudo);
}
//===============================================
std::string GChat::readId() {
    m_dom->queryXPath("/rdv/client/id");
    m_dom->getNodeXPath();
    std::string lData = m_dom->getNodeValue();
    m_id = lData;
    return lData;
}
//===============================================
std::string GChat::readPseudo() {
    m_dom->queryXPath("/rdv/client/pseudo");
    m_dom->getNodeXPath();
    std::string lData = m_dom->getNodeValue();
    m_pseudo = lData;
    return lData;
}
//===============================================
void GChat::createChat() {
    initRequest("chat", "send_message_client");
    m_dom->createNodePath("/rdv/data/sender/id").setNodeValue(m_id);
    m_dom->createNodePath("/rdv/data/sender/pseudo").setNodeValue(m_pseudo);
    m_dom->createNodePath("/rdv/data/sender/msg").setNodeValue("Bonjour tout le monde");
    m_dom->createNodePath("/rdv/data/receiver/id").setNodeValue("2");
    m_dom->createNodePath("/rdv/data/receiver/name").setNodeValue("Bryan");
}
//===============================================
void GChat::setId(const std::string& _id) {
    m_id = _id;
}
//===============================================
void GChat::setPseudo(const std::string& _pseudo) {
    m_pseudo = _pseudo;
}
//===============================================
void GChat::onModule(GSocket* _client) {
    GChat lRequest;
    lRequest.loadDom(_client->getRequest());
    std::string lMethod = lRequest.getMethod();

    GSocket* lServer = _client->getServer();

    if(lMethod == "connect_client") {
        onConnectClient(_client);
        std::string lId = lRequest.readId();
        lServer->addClient(lId, _client);
    }
    else if(lMethod == "send_message_client") {
        onSendMessageClient(_client);
    }
}
//===============================================
void GChat::onConnectClient(GSocket* _client) {
    GChat lRequest;
    lRequest.loadDom(_client->getRequest());
    std::string lId = lRequest.readId();
    std::string lPseudo = lRequest.readPseudo();
}
//===============================================
void GChat::onSendMessageClient(GSocket* _client) {

}
//===============================================
