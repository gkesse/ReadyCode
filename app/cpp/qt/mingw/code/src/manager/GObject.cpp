//===============================================
#include "GObject.h"
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
}
//===============================================
void GObject::initDom(const std::string& _module, const std::string& _method) {
    initDom();
    setModule(_module);
    setMethod(_method);
}
//===============================================
void GObject::loadDom(const std::string& _data) {
    m_dom.reset(new GXml);
    m_dom->loadXmlData(_data);
    m_dom->createXPath();
}
//===============================================
std::string GObject::getDom(const std::string& _encoding, int _format) const {
    return m_dom->toString(_encoding, _format);
}
//===============================================
void GObject::setModule(const std::string& _module) {
    GXml lNode;
    lNode.createNodeValue("module", _module);
    m_dom->appendNode(lNode);
}
//===============================================
std::string GObject::getModule() const {
    m_dom->queryXPath("/rdv/module");
    m_dom->getNodeXPath();
    std::string lData = m_dom->getNodeValue();
    return lData;

}
//===============================================
void GObject::setMethod(const std::string& _method) {
    GXml lNode;
    lNode.createNodeValue("method", _method);
    m_dom->appendNode(lNode);
}
//===============================================
std::string GObject::getMethod() const {
    m_dom->queryXPath("/rdv/method");
    m_dom->getNodeXPath();
    std::string lData = m_dom->getNodeValue();
    return lData;

}
//===============================================

