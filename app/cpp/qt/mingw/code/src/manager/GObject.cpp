//===============================================
#include "GObject.h"
#include "GLog.h"
#include "GXml.h"
//===============================================
GObject* GObject::m_instance = 0;
//===============================================
GObject::GObject() {

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
void GObject::initDom(const std::string& _module, const std::string& _method) {
    initDom();
    addModule(_module);
    addMethod(_method);
}
//===============================================
void GObject::initResult() {
    initDom();
    addResult();
}
//===============================================
void GObject::initResultOk() {
    initResult();
    addResult("ok");
}
//===============================================
void GObject::initError() {
    initDom();
    addError();
}
//===============================================
void GObject::loadDom(const std::string& _data) {
    m_dom.reset(new GXml);
    m_dom->loadXmlData(_data);
    m_dom->createXPath();
}
//===============================================
void GObject::addResult() {
    m_dom->queryXPath("/rdv");
    m_dom->getNodeXPath();
    m_dom->appendNode("results");
}
//===============================================
void GObject::addResult(const std::string& _msg) {
    m_dom->queryXPath("/rdv/results");
    m_dom->getNodeXPath();
    m_dom->appendNode("msg", _msg);
}
//===============================================
void GObject::addError() {
    m_dom->queryXPath("/rdv");
    m_dom->getNodeXPath();
    m_dom->appendNode("errors");
}
//===============================================
void GObject::addError(const std::string& _msg) {
    m_dom->queryXPath("/rdv/errors");
    m_dom->getNodeXPath();
    m_dom->appendNode("msg", _msg);
}
//===============================================
void GObject::addModule(const std::string& _module) {
    m_dom->queryXPath("/rdv");
    m_dom->getNodeXPath();
    m_dom->appendNode("module", _module);
}
//===============================================
void GObject::addMethod(const std::string& _method) {
    m_dom->queryXPath("/rdv");
    m_dom->getNodeXPath();
    m_dom->appendNode("method", _method);
}
//===============================================
std::string GObject::toString() const {
    return m_dom->toString();
}
//===============================================
std::string GObject::toString(const std::string& _encoding, int _format) const {
    return m_dom->toString(_encoding, _format);
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
    m_dom->queryXPath("/rdv/errors/msg[position()=%d]", _index + 1);
    m_dom->getNodeXPath();
    std::string lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
