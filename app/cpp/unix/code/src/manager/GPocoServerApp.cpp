//===============================================
#include "GPocoServerApp.h"
#include "GPocoRequestFactory.h"
#include "GPoco.h"
#include "GLog.h"
//===============================================
GPocoServerApp::GPocoServerApp(GPoco* _poco) {
    m_poco = _poco;
}
//===============================================
GPocoServerApp::~GPocoServerApp() {

}
//===============================================
int GPocoServerApp::main(const std::vector<std::string>& _args) {
    GPoco::eGModule lModule = m_poco->getModule();
    if(lModule == GPoco::POCO_SERVER_HTTP) return mainHttp(_args);
    if(lModule == GPoco::POCO_SERVER_HTTPS) return mainHttps(_args);
    return mainHttp(_args);
}
//===============================================
int GPocoServerApp::mainHttp(const std::vector<std::string>& _args) {
    Poco::Net::HTTPServer lServer(new GPocoRequestFactory(m_poco), Poco::Net::ServerSocket(m_poco->getPort()), new Poco::Net::HTTPServerParams);
    std::cout << std::endl << m_poco->getMsgStarting() << std::endl;
    lServer.start();
    // wait for CTRL-C or kill
    waitForTerminationRequest();
    std::cout << std::endl << m_poco->getMsgShutdown() << std::endl;
    lServer.stop();
    return Application::EXIT_OK;
}
//===============================================
int GPocoServerApp::mainHttps(const std::vector<std::string>& _args) {
    m_poco->initSSL();
    Poco::Net::SecureServerSocket lSocket(m_poco->getPort());
    Poco::Net::HTTPServer lServer(new GPocoRequestFactory(m_poco), lSocket, new Poco::Net::HTTPServerParams);
    std::cout << std::endl << m_poco->getMsgStarting() << std::endl;
    lServer.start();
    // wait for CTRL-C or kill
    waitForTerminationRequest();
    std::cout << std::endl << m_poco->getMsgShutdown() << std::endl;
    lServer.stop();
    return Application::EXIT_OK;
}
//===============================================
