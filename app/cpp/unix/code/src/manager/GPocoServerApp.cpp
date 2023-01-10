//===============================================
#include "GPocoServerApp.h"
#include "GPocoRequestFactory.h"
#include "GPoco.h"
//===============================================
GPocoServerApp::GPocoServerApp(GPoco* _poco) {
    m_poco = _poco;
}
//===============================================
GPocoServerApp::~GPocoServerApp() {

}
//===============================================
const GLog& GPocoServerApp::getLogs() const {
    return m_logs;
}
//===============================================
int GPocoServerApp::main(const std::vector<std::string>& _args) {
    GString lProtocol = m_poco->getProtocol();
    if(lProtocol == "") {
        m_logs.addError("Erreur le protocol est obligatoire.");
    }
    else if(lProtocol == "http") {
        Poco::Net::HTTPServer lServer(new GPocoRequestFactory(m_poco), Poco::Net::ServerSocket(m_poco->getPort()), new Poco::Net::HTTPServerParams);
        std::cout << std::endl << m_poco->getStartMessage() << std::endl;
        lServer.start();
        waitForTerminationRequest();
        std::cout << std::endl << m_poco->getStopMessage() << std::endl;
        lServer.stop();
    }
    // https
    else if(lProtocol == "https") {
        m_poco->initSSL();
        Poco::Net::SecureServerSocket lSocket(m_poco->getPort());
        Poco::Net::HTTPServer lServer(new GPocoRequestFactory(m_poco), lSocket, new Poco::Net::HTTPServerParams);
        std::cout << std::endl << m_poco->getStartMessage() << std::endl;
        lServer.start();
        waitForTerminationRequest();
        std::cout << std::endl << m_poco->getStopMessage() << std::endl;
        lServer.stop();
    }
    else {
        m_logs.addError("Erreur le protocol est inconnu.");
    }
    m_poco->addLogs(m_logs);
    return Application::EXIT_OK;
}
//===============================================
