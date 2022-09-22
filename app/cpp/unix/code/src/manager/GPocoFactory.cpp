//===============================================
#include "GPocoFactory.h"
#include "GPocoServerTcp.h"
#include "GLog.h"
//===============================================
GPocoFactory::GPocoFactory()
: Poco::Net::TCPServerConnectionFactory() {
    m_format = "";
}
//===============================================
GPocoFactory::~GPocoFactory() {

}
//===============================================
void GPocoFactory::setModule(const std::string& _module) {
    m_module = _module;
}
//===============================================
void GPocoFactory::setFormat(const std::string& _format) {
    m_format = _format;
}
//===============================================
Poco::Net::TCPServerConnection* GPocoFactory::onCreateConnectionTcp(const Poco::Net::StreamSocket& _socket) {
    GPocoServerTcp* lSocket = new GPocoServerTcp(_socket);
    lSocket->setModule(m_module);
    return lSocket;
}
//===============================================
Poco::Net::TCPServerConnection* GPocoFactory::onCreateConnectionTime(const Poco::Net::StreamSocket& _socket) {
    GPocoServerTcp* lSocket = new GPocoServerTcp(_socket);
    lSocket->setModule(m_module);
    lSocket->setFormat(m_format);
    return lSocket;
}
//===============================================
Poco::Net::TCPServerConnection* GPocoFactory::createConnection(const Poco::Net::StreamSocket& _socket) {
    if(m_module == "tcp") {
        return onCreateConnectionTcp(_socket);
    }
    else if(m_module == "time") {
        return onCreateConnectionTime(_socket);
    }
    return 0;
}
//===============================================
