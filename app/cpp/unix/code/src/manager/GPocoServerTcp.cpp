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
void GPocoServerTcp::setModule(const GString& _module) {
    m_module = _module;
}
//===============================================
void GPocoServerTcp::setFormat(const GString& _format) {
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
    lApp.logger().information("Request from " + m_hostname.c_str());
    try {
        Poco::Timestamp lNow;
        GString lTime(Poco::DateTimeFormatter::format(lNow, m_format.c_str()));
        lTime += "\r\n";
        socket().sendBytes(lTime.data(), (int)lTime.size());
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
