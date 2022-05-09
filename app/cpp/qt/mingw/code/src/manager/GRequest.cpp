//===============================================
#include "GRequest.h"
#include "GString.h"
#include "GXml.h"
//===============================================
GRequest* GRequest::m_instance = 0;
//===============================================
GRequest::GRequest() : GObject() {

}
//===============================================
GRequest::~GRequest() {

}
//===============================================
GRequest* GRequest::Instance() {
    if(m_instance == 0) {
        m_instance = new GRequest;
    }
    return m_instance;
}
//===============================================
void GRequest::createRequest() {
    initDom();
    m_dom->createNodePath("/rdv/request");
}
//===============================================
void GRequest::addRequest(GXml& _dom) {
    m_dom->queryXPath("/rdv/request");
    m_dom->getNodeXPath();
    m_dom->appendFromNodes(_dom);
}
//===============================================
void GRequest::addRequest(const std::string& _dom) {
    m_dom->queryXPath("/rdv/request");
    m_dom->getNodeXPath();
    m_dom->createNodeFromString(_dom);
}
//===============================================
std::vector<std::string> GRequest::loadXmlModules() const {
    std::vector<std::string> lModules;
    for(int i = 0; i < countXmlMessages(); i++) {
        std::string lName = getXmlName(i);
        std::string lModule = GString(lName).splitData('/').at(0);
        if(!std::binary_search(lModules.begin(), lModules.end(), lModule)) {
            lModules.push_back(lModule);
        }
    }
    return lModules;
}
//===============================================
std::vector<GRequest> GRequest::loadRequests(const std::string& _module) const {
    std::vector<GRequest> lReqs;
    int lCount = countXmlMessages(_module);
    for(int i = 0; i < lCount; i++) {
        GRequest lReq = loadRequests(_module, i);
        lReqs.push_back(lReq);
    }
    return lReqs;
}
//===============================================
GRequest GRequest::loadRequests(const std::string& _module, int _index) const {
    GRequest lReq;
    std::string lName = getXmlName(_module, _index);
    std::string lModule = GString(lName).splitData('/').at(0);
    std::string lMethod = GString(lName).splitData('/').at(1);
    lReq.m_id = getXmlId(_module, _index);
    lReq.m_module = lModule;
    lReq.m_method = lMethod;
    lReq.m_message = getXmlMessage(_module, _index);
    return lReq;
}
//===============================================
int GRequest::countXmlMessages() const {
    m_dom->queryXPath("/rdv/request/data");
    int lData = m_dom->countXPath();
    return lData;
}
//===============================================
int GRequest::countXmlMessages(const std::string& _module) const {
    m_dom->queryXPath(sformat("/rdv/request/data[name[contains(text(), '%s/')]]", _module.c_str()));
    int lData = m_dom->countXPath();
    return lData;
}
//===============================================
std::string GRequest::getXmlId(const std::string& _module, int _index) const {
    m_dom->queryXPath(sformat("/rdv/request/data[name[contains(text(), '%s/')]]/id", _module.c_str()));
    m_dom->getNodeItem(_index);
    std::string lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
std::string GRequest::getXmlName(const std::string& _module, int _index) const {
    m_dom->queryXPath(sformat("/rdv/request/data[name[contains(text(), '%s/')]]/name", _module.c_str()));
    m_dom->getNodeItem(_index);
    std::string lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
std::string GRequest::getXmlName(int _index) const {
    m_dom->queryXPath(sformat("/rdv/request/data/name"));
    m_dom->getNodeItem(_index);
    std::string lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
std::string GRequest::getXmlMessage(const std::string& _module, int _index) const {
    m_dom->queryXPath(sformat("/rdv/request/data[name[contains(text(), '%s/')]]/msg", _module.c_str()));
    m_dom->getNodeItem(_index);
    std::string lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
std::string GRequest::getId() const {
    return m_id;
}
//===============================================
std::string GRequest::getModule() const {
    return m_module;
}
//===============================================
std::string GRequest::getMethod() const {
    return m_method;
}
//===============================================
std::string GRequest::getMessage() const {
    return m_message;
}
//===============================================
void GRequest::setId(const std::string& _id) {
    m_id = _id;
}
void GRequest::setModule(const std::string& _module) {
    m_module = _module;
}
void GRequest::setMethod(const std::string& _method) {
    m_method = _method;
}
void GRequest::setMessage(const std::string& _message) {
    m_message = _message;
}
//===============================================
