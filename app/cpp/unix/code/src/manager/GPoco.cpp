//===============================================
#include "GPoco.h"
#include "GPocoApp.h"
#include "GLog.h"
#include "GFormat.h"
//===============================================
GPoco::GPoco()
: GObject() {
    m_app = new GPocoApp;
}
//===============================================
GPoco::~GPoco() {
    delete m_app;
}
//===============================================
void GPoco::setHostname(const std::string& _hostname) {
    m_hostname = _hostname;
}
//===============================================
void GPoco::setFamily(int _family) {
    m_app->setFamily(_family);
}
//===============================================
void GPoco::setRepetition(int _repetition) {
    m_app->setRepetition(_repetition);
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
void GPoco::showLogApp(Poco::Exception& _exception) {
    m_app->logger().log(_exception);
}
//===============================================
