//===============================================
#include "GObject.h"
#include "GSocket.h"
#include "GXml.h"
#include "GLog.h"
//===============================================
GObject* GObject::m_instance = 0;
//===============================================
GObject::GObject() {
    m_client = 0;
}
//===============================================
GObject::~GObject() {

}
//===============================================
GObject* GObject::Instance() {
    if(m_instance == 0) {
        m_instance = new GObject;
    }
    return m_instance;
}
//===============================================
std::string GObject::getDataPath() const {
    std::string lPath = "C:/Users/Admin/Downloads/Programs/ReadyData/data";
    return lPath;
}
//===============================================
std::string GObject::getResourcePath(const std::string& _resource, const std::string& _filename) const {
    std::string lPath = _filename;
    if(_resource != "") {
        lPath = _resource + "/" + lPath;
    }
    if(getDataPath() != "") {
        lPath = getDataPath() + "/" + lPath;
    }
    return lPath;
}
//===============================================
void GObject::showArgs(int _argc, char** _argv) {
    for(int i = 0; i < _argc; i++) {
        printf("argument[%d] : %s\n", i, _argv[i]);
    }
}
//===============================================
void GObject::initDom() {
    m_dom.reset(new GXml);
    m_dom->createDoc("1.0");
    m_dom->createRoot("rdv");
    m_dom->createXPath();
}
//===============================================
void GObject::loadDom(const std::string& _data) {
    m_dom.reset(new GXml);
    m_dom->loadXmlData(_data);
    m_dom->createXPath();
}
//===============================================
void GObject::createResult() {
    initDom();
    m_dom->queryXPath("/rdv");
    m_dom->getNodeXPath();
    m_dom->appendNode("results");
}
//===============================================
void GObject::addResultMsg(const std::string& _msg) {
    m_dom->queryXPath("/rdv/results");
    m_dom->getNodeXPath();
    m_dom->appendNode("msg", _msg);
}
//===============================================
void GObject::createError() {
    initDom();
    m_dom->queryXPath("/rdv");
    m_dom->getNodeXPath();
    m_dom->appendNode("errors");
}
//===============================================
void GObject::addErrorMsg(const std::string& _msg) {
    m_dom->queryXPath("/rdv/errors");
    m_dom->getNodeXPath();
    m_dom->appendNode("msg", _msg);
}
//===============================================
int GObject::countErrors() const {
    m_dom->queryXPath("/rdv/errors/msg");
    int lData = m_dom->countXPath();
    return lData;
}
//===============================================
bool GObject::hasErrors() const {
    return (countErrors() != 0);
}
//===============================================
std::string GObject::getErrors(int _index) const {
    m_dom->queryXPath(sformat("/rdv/errors/msg[position()=%d]", _index + 1));
    m_dom->getNodeXPath();
    std::string lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
void GObject::createRequest(const std::string& _module, const std::string& _method) {
    initDom();
    m_dom->queryXPath("/rdv");
    m_dom->getNodeXPath();
    m_dom->appendNode("module", _module);
    m_dom->appendNode("method", _method);
}
//===============================================
std::string GObject::getModule() const {
    m_dom->queryXPath("/rdv/module");
    m_dom->getNodeXPath();
    std::string lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
std::string GObject::getMethod() const {
    m_dom->queryXPath("/rdv/method");
    m_dom->getNodeXPath();
    std::string lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
std::string GObject::getRequestName() const {
    std::string lModule = getModule();
    std::string lMethod = getMethod();
    std::string lName = sformat("%s/%s", lModule.c_str(), lMethod.c_str());
    return lName;
}
//===============================================
void GObject::onUnknownModule(const std::string& _request, GSocket* _client) {
    GObject lRequest;
    lRequest.loadDom(_request);
    std::string lModule = lRequest.getModule();
    GObject lDom;
    lDom.createError();
    lDom.addErrorMsg(lDom.sformat("Erreur le module (%s) n'existe pas.", lModule.c_str()));
    _client->addDataOut(lDom);
}
//===============================================
void GObject::onUnknownMethod(const std::string& _request, GSocket* _client) {
    GObject lRequest;
    lRequest.loadDom(_request);
    std::string lModule = lRequest.getModule();
    std::string lMethod = lRequest.getMethod();
    GObject lDom;
    lDom.createError();
    lDom.addErrorMsg(GOBJECT->sformat("Erreur la methode (%s) \ndu module (%s) n'existe pas.", lMethod.c_str(), lModule.c_str()));
    _client->addDataOut(lDom);
}
//===============================================
std::string GObject::toString(const std::string& _encoding, int _format) const {
    return m_dom->toString(_encoding, _format);
}
//===============================================
std::string GObject::sformat(const char* _format, ...) const {
    va_list lArgs;
    va_start (lArgs, _format);
    int lSize = vsnprintf(0, 0, _format, lArgs);
    std::vector<char> lData(lSize + 1);
    vsnprintf(lData.data(), lData.size(), _format, lArgs);
    va_end(lArgs);
    return lData.data();
}
//===============================================
