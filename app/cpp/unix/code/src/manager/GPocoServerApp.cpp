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
    GLOGT(eGFUN, "");
    Poco::Net::HTTPServer lServer(new GPocoRequestFactory(m_poco), Poco::Net::ServerSocket(m_poco->getPort()), new Poco::Net::HTTPServerParams);
    lServer.start();
    std::cout << std::endl << m_poco->getMsgStarting() << std::endl;
    waitForTerminationRequest(); // wait for CTRL-C or kill
    std::cout << std::endl << m_poco->getMsgShutdown() << std::endl;
    lServer.stop();
    return Application::EXIT_OK;
}
//===============================================
