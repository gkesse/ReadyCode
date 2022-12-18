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
    lServer.start();
    std::cout << std::endl << m_poco->getMsgStarting() << std::endl;
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
    lServer.start();
    // wait for CTRL-C or kill
    waitForTerminationRequest();
    lServer.stop();
    return Application::EXIT_OK;
}
//===============================================
{
    try {
        Poco::Net::initializeSSL();
        // Socket server
        Poco::Net::Context::Ptr ptrContext =
                new Poco::Net::Context(Poco::Net::Context::SERVER_USE,
                        "./server.key",
                        "./server.crt",
                        "./ca.pem",
                        Poco::Net::Context::VERIFY_STRICT,
                        9,
                        false,
                        "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH");

        Poco::SharedPtr<Poco::Net::InvalidCertificateHandler> ptrCert = new Poco::Net::AcceptCertificateHandler(true);

        Poco::SharedPtr<Poco::Net::PrivateKeyPassphraseHandler> ptrPrivateKeyPassphraseHandler;
        ptrPrivateKeyPassphraseHandler = new Poco::Net::KeyConsoleHandler(true);

        Poco::Net::SSLManager::instance().initializeServer(ptrPrivateKeyPassphraseHandler, ptrCert, ptrContext);

        Poco::Net::SocketAddress serverAddress("0.0.0.0", 8085);
        Poco::Net::SecureServerSocket serverSecureSocket(serverAddress);
        Poco::Net::TCPServer srv(new Poco::Net::TCPServerConnectionFactoryImpl<EchoConnection>(), serverSecureSocket);
        srv.start();

        Poco::Net::Context::Ptr ptrContext2 =
                new Poco::Net::Context(Poco::Net::Context::CLIENT_USE,
                        "./client.key",
                        "./client.crt",
                        "./ca.pem",
                        Poco::Net::Context::VERIFY_STRICT,
                        9,
                        true,
                        "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH");

        Poco::SharedPtr<Poco::Net::InvalidCertificateHandler> ptrCert2 = new Poco::Net::AcceptCertificateHandler(true);

        Poco::SharedPtr<Poco::Net::PrivateKeyPassphraseHandler>ptrPrivateKeyPassphraseHandler2(new Poco::Net::KeyConsoleHandler(false));

        Poco::Net::SSLManager::instance().initializeClient(ptrPrivateKeyPassphraseHandler2, ptrCert2, ptrContext2);

        Poco::Net::SocketAddress sa("127.0.0.1", 8085);
        Poco::Net::SecureStreamSocket ss1(sa);
        std::string data("TEST");
        int retSend = ss1.sendBytes(data.data(), (int) data.size());
        if (retSend>0)
        {
            char buffer[1024];
            memset(buffer, '\0', 1024);
            int retRecv = ss1.receiveBytes(buffer, sizeof(buffer));
            if (retRecv > 0)
            {
                std::cout << "buffer <-: " << buffer << std::endl;
            }
            else
            {
                std::cout << "ERROR: " << retRecv << std::endl;
            }
        }
        ss1.close();
    }
    catch (Poco::Exception& ex)
    {
        std::cout << ex.displayText() << std::endl;
    }
