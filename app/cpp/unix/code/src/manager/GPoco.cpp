//===============================================
#include "GPoco.h"
#include "GPocoApp.h"
#include "GPocoServerApp.h"
#include "GPocoServerTcp.h"
#include "GLog.h"
#include "GFormat.h"
//===============================================
GPoco::GPoco()
: GObject() {
    m_app = new GPocoApp;
    m_serverApp = new GPocoServerApp;
    m_module = "";
    m_port = 0;
    m_format = "";
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
    m_app->setHostname(_hostname);
}
//===============================================
void GPoco::setFamily(int _family) {
    m_app->setFamily(_family);
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
void GPoco::setRepetitions(int _repetitions) {
    m_app->setRepetitions(_repetitions);
}
//===============================================
void GPoco::init(int _argc, char** _argv) {
    m_app->init(_argc, _argv);
}
//===============================================
void GPoco::run() {
    m_app->setModule(m_module);
    m_app->run();
}
//===============================================
void GPoco::run(int _argc, char** _argv) {
    m_serverApp->setModule(m_module);
    m_serverApp->run(_argc, _argv);
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
    Poco::Net::TCPServer lServer(new GPocoServerTcp::GFactory(), m_port);
    lServer.start();
    GLOGT(eGMSG, "[ INFO ] Démarrage du serveur...");
    lTerminator.wait();
}
//===============================================
