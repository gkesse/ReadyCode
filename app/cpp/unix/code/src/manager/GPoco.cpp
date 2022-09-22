//===============================================
#include "GPoco.h"
#include "GPocoApp.h"
#include "GPocoServerApp.h"
#include "GPocoServerTcp.h"
#include "GPocoFactory.h"
#include "GLog.h"
//===============================================
GPoco::GPoco()
: GObject() {
    m_app = 0;
    m_serverApp = 0;
    m_module = "";
    m_port = 0;
    m_format = "";
    m_hostname = "";
    m_family = 0;
    m_request = "";
    m_response = "";
}
//===============================================
GPoco::~GPoco() {
    delete m_app;
    delete m_serverApp;
}
//===============================================
void GPoco::setModule(const std::string& _module) {
    m_module = _module;
}
//===============================================
void GPoco::setHostname(const std::string& _hostname) {
    m_hostname = _hostname;
}
//===============================================
void GPoco::setFamily(int _family) {
    m_family = _family;
}
//===============================================
void GPoco::setPort(int _port) {
    m_port = _port;
}
//===============================================
void GPoco::setFormat(const std::string& _format) {
    m_format = _format;
}
//===============================================
void GPoco::setRequest(const std::string& _request) {
    m_request = _request;
}
//===============================================
void GPoco::setResponse(const std::string& _response) {
    m_response = _response;
}
//===============================================
void GPoco::setRepetitions(int _repetitions) {
    m_app->setRepetitions(_repetitions);
}
//===============================================
void GPoco::onRunTime(int _argc, char** _argv) {
    m_serverApp = new GPocoServerApp;
    m_serverApp->setModule(m_module);
    m_serverApp->setFormat(m_format);
    m_serverApp->setPort(m_port);
    m_serverApp->run(_argc, _argv);
}
//===============================================
void GPoco::onRunEcho(int _argc, char** _argv) {
    m_serverApp = new GPocoServerApp;
    m_serverApp->setModule(m_module);
    m_serverApp->setPort(m_port);
    m_serverApp->run(_argc, _argv);
}
//===============================================
void GPoco::onRunDns(int _argc, char** _argv) {
    const Poco::Net::HostEntry& entry = Poco::Net::DNS::hostByName(m_hostname);
    std::cout << "Canonical Name: " << entry.name() << std::endl;

    const Poco::Net::HostEntry::AliasList& aliases = entry.aliases();
    Poco::Net::HostEntry::AliasList::const_iterator itAlias = aliases.begin();
    for (; itAlias != aliases.end(); ++itAlias) {
        std::cout << "Alias: " << *itAlias << std::endl;
    }

    const Poco::Net::HostEntry::AddressList& addrs = entry.addresses();
    Poco::Net::HostEntry::AddressList::const_iterator itAddress = addrs.begin();
    for (; itAddress != addrs.end(); ++itAddress) {
        std::cout << "Address: " << itAddress->toString() << std::endl;
    }
}
//===============================================
void GPoco::onRunStream(int _argc, char** _argv) {
    Poco::Net::SocketAddress sa(m_hostname, m_port);
    Poco::Net::StreamSocket socket(sa);
    Poco::Net::SocketStream str(socket);
    str << m_request;
    str.flush();
    Poco::StreamCopier::copyStream(str, std::cout);
}
//===============================================
void GPoco::onRunStreamHttp(int _argc, char** _argv) {
    Poco::Net::ServerSocket srv(m_port);
    for (;;) {
        Poco::Net::StreamSocket ss = srv.acceptConnection();
        Poco::Net::SocketStream str(ss);
        str << m_response << std::flush;
    }
}
//===============================================
void GPoco::init(int _argc, char** _argv) {
    m_app->init(_argc, _argv);
}
//===============================================
void GPoco::run() {
    m_app = new GPocoApp;
    m_app->setModule(m_module);
    m_app->setHostname(m_hostname);
    m_app->setFamily(m_family);
    m_app->run();
}
//===============================================
void GPoco::run(int _argc, char** _argv) {
    if(m_module == "time") {
        onRunTime(_argc, _argv);
    }
    else if(m_module == "echo") {
        onRunEcho(_argc, _argv);
    }
    else if(m_module == "dns") {
        onRunDns(_argc, _argv);
    }
    else if(m_module == "stream") {
        onRunStream(_argc, _argv);
    }
    else if(m_module == "stream/http") {
        onRunStreamHttp(_argc, _argv);
    }
}
//===============================================
void GPoco::showLog(Poco::Exception& _exception) {
    m_app->logger().log(_exception);
}
//===============================================
void GPoco::startServer() {
    if(m_module == "tcp") {
        startServerTcp();
    }
}
//===============================================
void GPoco::startServerTcp() {
    Poco::Event lTerminator;
    GPocoFactory* lFactory = new GPocoFactory;
    lFactory->setModule(m_module);
    Poco::Net::TCPServer lServer(lFactory, m_port);
    lServer.start();
    GLOGT(eGMSG, "[ INFO ] Démarrage du serveur...");
    lTerminator.wait();
}
//===============================================
