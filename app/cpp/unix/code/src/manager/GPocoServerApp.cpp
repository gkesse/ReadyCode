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
int GPocoServerApp::main(const std::vector<std::string>& _args) {
    GString lProtocol = m_poco->getProtocol();
    // http
    if(lProtocol == "http") {
        Poco::Net::HTTPServer lServer(new GPocoRequestFactory(m_poco), Poco::Net::ServerSocket(m_poco->getPort()), new Poco::Net::HTTPServerParams);
        std::cout << std::endl << m_poco->getStartMessage() << std::endl;
        lServer.start();
        // wait for CTRL-C or kill
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
        // wait for CTRL-C or kill
        waitForTerminationRequest();
        std::cout << std::endl << m_poco->getStopMessage() << std::endl;
        lServer.stop();
    }
    // unknown protocol
    else {
        m_logs.addError("Erreur le protocol n'est pas pris en charge.");
    }
    m_poco->m_logs.add(m_logs);
    return Application::EXIT_OK;
}
//===============================================
