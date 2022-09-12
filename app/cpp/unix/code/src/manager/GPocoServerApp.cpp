//===============================================
#include "GPocoServerApp.h"
#include "GPocoFactory.h"
#include "GLog.h"
#include "GFormat.h"
//===============================================
GPocoServerApp::GPocoServerApp()
: Poco::Util::ServerApplication() {
    m_module = "";
    m_port = 0;
    m_format = "";
}
//===============================================
GPocoServerApp::~GPocoServerApp() {

}
//===============================================
void GPocoServerApp::setModule(const std::string& _module) {
    m_module = _module;
}
//===============================================
void GPocoServerApp::setFormat(const std::string& _format) {
    m_format = _format;
}
//===============================================
void GPocoServerApp::setPort(int _port) {
    m_port = _port;
}
//===============================================
void GPocoServerApp::onMainTime(const std::vector<std::string>& _args) {
    GPocoFactory* lFactory = new GPocoFactory;
    lFactory->setFormat(m_format);
    Poco::Net::ServerSocket lSocket(m_port);
    Poco::Net::TCPServer lServer(lFactory, lSocket);
    lServer.start();
    waitForTerminationRequest();
    lServer.stop();
}
//===============================================
void GPocoServerApp::initialize(Poco::Util::Application& _app) {
    loadConfiguration();
    Poco::Util::ServerApplication::initialize(_app);
}
//===============================================
void GPocoServerApp::uninitialize() {
    Poco::Util::ServerApplication::uninitialize();
}
//===============================================
int GPocoServerApp::main(const std::vector<std::string>& _args) {
    if(m_module == "time") {
        onMainTime(_args);
    }
    return 0;
}
//===============================================
