//===============================================
#include "GPoco.h"
#include "GPocoApp.h"
#include "GPocoServerTcp.h"
#include "GLog.h"
#include "GFormat.h"
//===============================================
GPoco::GPoco()
: GObject() {
    m_app = new GPocoApp;
    m_port = 0;
}
//===============================================
GPoco::~GPoco() {
    delete m_app;
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
void GPoco::setRepetitions(int _repetitions) {
    m_app->setRepetitions(_repetitions);
}
//===============================================
void GPoco::setKey(const std::string& _key) {
    m_app->setKey(_key);
}
//===============================================
void GPoco::init(int _argc, char** _argv) {
    m_app->init(_argc, _argv);
}
//===============================================
void GPoco::run() {
    m_app->run();
}
//===============================================
void GPoco::showLog(Poco::Exception& _exception) {
    m_app->logger().log(_exception);
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
