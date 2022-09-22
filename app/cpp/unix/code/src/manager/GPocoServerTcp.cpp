//===============================================
#include "GPocoServerTcp.h"
#include "GLog.h"
//===============================================
GPocoServerTcp::GPocoServerTcp(const Poco::Net::StreamSocket& _socket)
: Poco::Net::TCPServerConnection(_socket) {
    m_module = "";
    m_format = "";
}
//===============================================
GPocoServerTcp::~GPocoServerTcp() {

}
//===============================================
void GPocoServerTcp::setModule(const std::string& _module) {
    m_module = _module;
}
//===============================================
void GPocoServerTcp::setFormat(const std::string& _format) {
    m_format = _format;
}
//===============================================
void GPocoServerTcp::onRunTcp() {
    Poco::Net::StreamSocket& lSocket = socket();
    char lBuffer[BUFFER_SIZE + 1];
    int lBytes = lSocket.receiveBytes(lBuffer, BUFFER_SIZE);

    while (lBytes > 0) {
        lBuffer[lBytes] = 0;
        printf("[ INFO ] %s\n", lBuffer);
        lBytes = lSocket.receiveBytes(lBuffer, BUFFER_SIZE);
    }
}
//===============================================
void GPocoServerTcp::onRunTime() {
    m_hostname = this->socket().peerAddress().toString();
    Poco::Util::Application& lApp = Poco::Util::Application::instance();
    lApp.logger().information("Request from " + m_hostname);
    try {
        Poco::Timestamp lNow;
        std::string lTime(Poco::DateTimeFormatter::format(lNow, m_format));
        lTime.append("\r\n");
        socket().sendBytes(lTime.data(), (int)lTime.length());
    }
    catch (Poco::Exception& exc)
    {
        lApp.logger().log(exc);
    }
}
//===============================================
void GPocoServerTcp::run() {
    if(m_module == "tcp") {
        onRunTcp();
    }
    else if(m_module == "time") {
        onRunTime();
    }
}
//===============================================
